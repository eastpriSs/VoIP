#include "returning_states.h"
#include "call_repository_impl.h"
#include <pjsua2.hpp>
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
    case PJSIP_INV_STATE_NULL:
        return CallState::None;

    case PJSIP_INV_STATE_CALLING:
        return CallState::Calling;

    case PJSIP_INV_STATE_INCOMING:
        return CallState::Incoming;

    case PJSIP_INV_STATE_EARLY:
        return CallState::Early;

    case PJSIP_INV_STATE_CONNECTING:
        return CallState::Connecting;

    case PJSIP_INV_STATE_CONFIRMED:
        return CallState::Active;

    case PJSIP_INV_STATE_DISCONNECTED:
        return CallState::Disconnected;

    default:
        throw std::runtime_error("Получен неясный код звонка.");
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

void CallRepositoryImpl::muteSipCall()
{
    sipService->doMute();
}

void CallRepositoryImpl::unMuteSipCall()
{
    sipService->doUnMute();
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
