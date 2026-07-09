#include "call_controller.h"
#include "call_session.h"

CallController::CallController(std::shared_ptr<ICallRepository> rep, QObject *parent)
    : repo(rep), QObject{parent}
{
    connect(repo.get(), &ICallRepository::incomingCall, this, &CallController::onIncomingCall);
}

void CallController::callNumber(QString number)
{
    emit incomingCall("test");
    return;

    try {
        CallSession callSession = CallSession(SipUri(number));
        emit validationDataCompleted();
        repo->callSipAccount(callSession.getDist());
        emit callNumberSuccess();
    } catch (const std::invalid_argument& e) {
        emit validationDataCompleted(false);
    } catch (const std::runtime_error& e) {
        emit callNumberFailed(e.what());
    }
}

void CallController::acceptCall()
{
    repo->acceptSipCall();
}

void CallController::rejectCall()
{
    repo->rejectSipCall();
}

void CallController::onIncomingCall(SipUri remoteUri, int callID)
{
    emit incomingCall(remoteUri.toString());
}

