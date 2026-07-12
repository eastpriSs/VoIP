#include "call_repository_impl.h"
#include <QDebug>

namespace {

QString extractPureSipUri(const QString& rawUri)
{
    QString trimmed = rawUri.trimmed();
    int start = trimmed.indexOf('<');
    int end = trimmed.lastIndexOf('>');

    if (start != -1 && end != -1 && end > start) {
        return trimmed.mid(start + 1, end - start - 1).trimmed();
    }
    return trimmed;
}

CallState mapPjsipStateToDomain(int pjsip_state)
{
    switch (pjsip_state) {
    case 0: // PJSIP_INV_STATE_NULL (До создания вызова)
        return CallState::None;

    case 1: // PJSIP_INV_STATE_CALLING (Отправлен INVITE)
        return CallState::Calling;

    case 2: // PJSIP_INV_STATE_INCOMING (Получен INVITE)
        return CallState::Incoming;

    case 3: // PJSIP_INV_STATE_EARLY (Предварительный ответ, например 180 Ringing)
        return CallState::Early;

    case 4: // PJSIP_INV_STATE_CONNECTING (Получен/отправлен ответ 200 OK)
        return CallState::Connecting;

    case 5: // PJSIP_INV_STATE_CONFIRMED (Вызов успешно установлен, идет разговор)
        return CallState::Active;

    case 6: // PJSIP_INV_STATE_DISCONNECTED (Вызов завершен или отклонен)
        return CallState::Disconnected;

    default:
        throw std::runtime_error("Получен неясный код звонка.");
        return CallState::None;
    }
}

} // namespace

CallRepositoryImpl::CallRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService)
    : sipService(sipService)
{
    connect(sipService.get(), &sip::ModuleSIP::incomingCallReceived, this, &CallRepositoryImpl::onIncomingCall);
    connect(sipService.get(), &sip::ModuleSIP::callStateChanged, this, &CallRepositoryImpl::onCallStateChanged);
}

void CallRepositoryImpl::callSipAccount(const SipUri &distUri)
{
    int code = sipService->doCall(distUri);
    if (code != sip::OK) {
        throw std::runtime_error(sipService->getTextError(code).toStdString());
    }
}

void CallRepositoryImpl::acceptSipCall()
{
    sipService->doAcceptCall();
}

void CallRepositoryImpl::rejectSipCall()
{
    sipService->doRejectCall();
}

void CallRepositoryImpl::hangupSipCall()
{
    sipService->doHangUpCall();
}

void CallRepositoryImpl::holdSipCall()
{
    sipService->doHoldCall();
}

void CallRepositoryImpl::unHoldSipCall()
{
    sipService->doUnHoldCall();
}

void CallRepositoryImpl::onIncomingCall(QString remoteUri, int callID)
{
    emit incomingCall(SipUri(extractPureSipUri(std::move(remoteUri))), callID);
}

void CallRepositoryImpl::onCallStateChanged(int callId, int pjsip_state, const QString &stateText)
{
    Q_UNUSED(callId);

    CallState domainState = mapPjsipStateToDomain(pjsip_state);
    emit callStateChanged(domainState, stateText);
}
