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

enum PjsipInvState {
    PjsipStateNull         = 0, // PJSIP_INV_STATE_NULL
    PjsipStateCalling      = 1, // PJSIP_INV_STATE_CALLING
    PjsipStateIncoming     = 2, // PJSIP_INV_STATE_INCOMING
    PjsipStateEarly        = 3, // PJSIP_INV_STATE_EARLY
    PjsipStateConnecting   = 4, // PJSIP_INV_STATE_CONNECTING
    PjsipStateConfirmed    = 5, // PJSIP_INV_STATE_CONFIRMED
    PjsipStateDisconnected = 6  // PJSIP_INV_STATE_DISCONNECTED
};

CallState mapPjsipStateToDomain(int pjsip_state)
{
    switch (pjsip_state) {
    case PjsipStateNull:
        return CallState::None;

    case PjsipStateCalling:
        return CallState::Calling;

    case PjsipStateIncoming:
        return CallState::Incoming;

    case PjsipStateEarly:
        return CallState::Early;

    case PjsipStateConnecting:
        return CallState::Connecting;

    case PjsipStateConfirmed:
        return CallState::Active;

    case PjsipStateDisconnected:
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
