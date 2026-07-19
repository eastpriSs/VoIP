#include "call_controller.h"
#include "call_session.h"
#include <QDebug>
#include <stdexcept>

CallController::CallController(std::shared_ptr<ICallRepository> rep, QObject *parent)
    : QObject{parent}, repo(rep)
{
    connect(repo.get(), &ICallRepository::incomingCall, this, &CallController::onIncomingCall);
    connect(repo.get(), &ICallRepository::callStateChanged, this, &CallController::onCallStateChanged);
}

void CallController::initiateCall(const QString& number, const QString& serverDomain)
{
    try {
        CallSession callSession = CallSession(SipUri(number, serverDomain));

        emit validationDataCompleted(true);
        repo->callSipAccount(callSession.getDist());
        emit callNumberSuccess();

    } catch (const std::invalid_argument& e) {
        emit validationDataCompleted(false);
        emit callNumberFailed(e.what());
    } catch (const std::runtime_error& e) {
        emit callNumberFailed(e.what());
    }
}

void CallController::initiateCall(const QString& number)
{
    initiateCall(number, "");
}

void CallController::hangUpCall()
{
    repo->hangupSipCall();
}

void CallController::acceptCall()
{
    repo->acceptSipCall();
}

void CallController::rejectCall()
{
    repo->rejectSipCall();
}

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
