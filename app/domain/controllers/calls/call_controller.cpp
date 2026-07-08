#include "call_controller.h"
#include "call_session.h"

CallController::CallController(std::shared_ptr<ICallRepository> rep, QObject *parent)
    : repo(rep), QObject{parent}
{}

void CallController::callNumber(QString number)
{
    CallSession callSession = CallSession(SipUri(number));
    repo->callSipAccount(callSession.getDist());
}
