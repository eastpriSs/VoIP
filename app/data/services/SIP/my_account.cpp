#include "my_account.h"
#include <QDebug>

using namespace pj;

namespace sip_private {

MyAccount::MyAccount(RegCallback cb, IncomingCallCallback icb, MyCall::StateCallback stcb)
    : regCallback(std::move(cb)), inCallback(icb), stateCallback(stcb), call(nullptr), isCreated(false) {}

MyAccount::~MyAccount() {
    if (isCreated) shutdown();
}

void MyAccount::onRegState(OnRegStateParam &prm) {
    AccountInfo ai = getInfo();
    qInfo() << (ai.regIsActive ? "*** Register:" : "*** Unregister:")
            << " code=" << prm.code;

    if (regCallback) {
        regCallback(prm.code);
    }
}

void MyAccount::onIncomingCall(OnIncomingCallParam &iprm)
{
    if (call && call->isActive()) {
        pj_status_t status = pjsua_call_answer(iprm.callId, PJSIP_SC_BUSY_HERE, NULL, NULL);

        if (status != PJ_SUCCESS) {
            char errMessage[PJ_ERR_MSG_SIZE];
            pj_strerror(status, errMessage, sizeof(errMessage));
            qInfo() << "Ошибка при отправке BUSY для callId" << iprm.callId
                    << "Код:" << status << "-" << QString::fromUtf8(errMessage);
        } else {
            qInfo() << "Входящий звонок отклонен (BUSY), так как линия занята.";
        }
        return;
    }

    call = std::make_unique<MyCall>(*this, iprm.callId, stateCallback);
    CallInfo ci = call->getInfo();

    if (inCallback)
        inCallback(QString::fromStdString(ci.remoteUri), iprm.callId);
}

void MyAccount::setIsCreated(bool v) { isCreated = v; }

void MyAccount::answerCall() {
    if (!call) return;
    CallOpParam prm;
    prm.statusCode = PJSIP_SC_OK;
    call->answer(prm);
}

void MyAccount::rejectCall() {
    if (!call) return;
    CallOpParam prm;
    prm.statusCode = PJSIP_SC_DECLINE;
    call->answer(prm);
}
}
