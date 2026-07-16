#include "call_controller.h"
#include "call_session.h"
#include <QDebug>

CallController::CallController(std::shared_ptr<ICallRepository> rep, QObject *parent)
    : repo(rep), QObject{parent}
{
    connect(repo.get(), &ICallRepository::incomingCall, this, &CallController::onIncomingCall);
    connect(repo.get(), &ICallRepository::callStateChanged, this, &CallController::onCallStateChanged);
}

void CallController::callNumber(QString number)
{
    try {
        CallSession callSession = CallSession(SipUri(number));
        emit validationDataCompleted();
        repo->callSipAccount(callSession.getDist());
        emit callNumberSuccess();
        emit outComingCall(number);
    } catch (const std::invalid_argument& e) {
        emit validationDataCompleted(false);
    } catch (const std::runtime_error& e) {
        emit callNumberFailed(e.what());
    }
}

void CallController::hangUpCall()
{
    repo->hangupSipCall();
}

void CallController::acceptCall() { repo->acceptSipCall(); }
void CallController::rejectCall() { repo->rejectSipCall(); }

void CallController::holdCall()
{
    repo->holdSipCall();
}

void CallController::unHoldCall()
{
    repo->unHoldSipCall();
}

void CallController::mute()
{
    repo->muteSipCall();
}

void CallController::unMute()
{
    repo->unMuteSipCall();
}

void CallController::onIncomingCall(SipUri remoteUri, int callID)
{
    Q_UNUSED(callID);
    emit incomingCall(remoteUri.toString());
}

void CallController::onCallStateChanged(CallState state, const QString& stateText)
{
    switch (state) {

    case CallState::Calling:
        emit callingCall();
        break;

    case CallState::Early:
        emit earlyMediaCall();
        break;

    case CallState::Connecting:
        emit connectingCall();
        break;

    case CallState::Active:
        emit activeCall();
        break;

    case CallState::Disconnected:
        emit disconnectedCall(stateText);
        break;

    case CallState::Incoming:
    case CallState::None:
        break;
    }
}
