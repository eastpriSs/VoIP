#include "module_sip.h"
#include <QDebug>

using namespace pj;

namespace sip_private {

// ----------------------------------- MyCall

MyCall::MyCall(Account &acc, int call_id, StateCallback cb)
    : Call(acc, call_id), stateCallback(std::move(cb)), muteVoice(false) {}

void MyCall::onCallState(OnCallStateParam &prm) {
    CallInfo ci = getInfo();
    qInfo() << "call state:" << ci.stateText;
    if (stateCallback) {
        stateCallback(ci.id, ci.state, QString::fromStdString(ci.stateText));
    }
    if (ci.state == PJSIP_INV_STATE_DISCONNECTED)
        delete this;
}

void MyCall::onCallMediaState(OnCallMediaStateParam &prm) {
    CallInfo ci = getInfo();
    for (unsigned i = 0; i < ci.media.size(); i++) {
        if (ci.media[i].type == PJMEDIA_TYPE_AUDIO) {
            try {
                AudioMedia aud_med = getAudioMedia(i);
                AudDevManager& mgr = Endpoint::instance().audDevManager();

                if (ci.media[i].status == PJSUA_CALL_MEDIA_ACTIVE ||
                    ci.media[i].status == PJSUA_CALL_MEDIA_REMOTE_HOLD) {

                    aud_med.startTransmit(mgr.getPlaybackDevMedia());
                    mgr.getCaptureDevMedia().startTransmit(aud_med);
                    aud_med.adjustTxLevel(muteVoice ? 0.0f : 1.0f);

                } else {
                    aud_med.stopTransmit(mgr.getPlaybackDevMedia());
                    mgr.getCaptureDevMedia().stopTransmit(aud_med);
                }
            }
            catch(const Error &e) {
            }
        }
    }
}

void MyCall::setMuteVoice(bool v) {
    muteVoice = v;
    applyMute();
}

void MyCall::applyMute() {
    try {
        CallInfo ci = getInfo();
        for (unsigned i = 0; i < ci.media.size(); i++) {
            if (ci.media[i].type == PJMEDIA_TYPE_AUDIO &&
                ci.media[i].status == PJSUA_CALL_MEDIA_ACTIVE) {

                AudioMedia aud_med = getAudioMedia(i);
                aud_med.adjustTxLevel(muteVoice ? 0.0f : 1.0f);
            }
        }
    } catch (const Error &e) {
        // todo: сделать вывод ошибки понятный для пользователя
        qInfo() << "Mute не сработал.";
    }
}


// ----------------------------------- MyAccount

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

    call.reset();
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

} // namespace sip_private


namespace sip {

// ----------------------------------- ModuleSIP


ModuleSIP::ModuleSIP(QObject* parent)
    : QObject(parent), isEndpointInit(false)
{}

ModuleSIP::~ModuleSIP() {
    if (isEndpointInit) {
        ep.libDestroy();
    }
}

int ModuleSIP::checkAccountAndCall() const {
    if (!acc) return ACCOUNT_UNREGISTRED;
    if (!acc->call) return PJSIP_SC_NOT_FOUND;
    return OK;
}

int ModuleSIP::doRegister(const AuthCredits& authCredits)
{
    using sip_private::MyAccount;

    if (!isEndpointInit) {
        ep.libCreate();
        EpConfig ep_cfg;
        ep.libInit(ep_cfg);

        TransportConfig tcfg;
        tcfg.port = 0;
        try {
            ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
        } catch (Error &err) {
            qInfo() << "Transport create failed:" << err.status;
            return err.status;
        }

        ep.libStart();
        isEndpointInit = true;
        qInfo() << "*** PJSUA2 STARTED ***";
    }

    if (acc) {
        try {
            acc->shutdown();
        } catch (const Error& err) {
            qInfo() << "Account shutdown failed:" << err.status;
        }
        acc.reset();
    }

    AccountConfig acfg;
    acfg.idUri = authCredits.getIDUri().toStdString();
    acfg.regConfig.registrarUri = authCredits.getRegistrarUri().toStdString();
    AuthCredInfo cred("digest", "*", authCredits.getLogin().toStdString(),
                      0, authCredits.getPassword().toStdString());
    acfg.sipConfig.authCreds.push_back(cred);

    qInfo() << "ID Uri : " << QString::fromStdString(acfg.idUri);
    qInfo() << "ID Reg Uri : " << QString::fromStdString(acfg.regConfig.registrarUri);

    try {
        acc = std::make_unique<MyAccount>(
            [this](int code) {
                emit registrationStateChanged(code);
            },
            [this](QString remoteUri, int callId) {
                emit incomingCallReceived(std::move(remoteUri), callId);
            },
            [this](int callId, int pjsip_state, const QString& stateText) {
                emit callStateChanged(callId, pjsip_state, stateText);
            });

        acc->create(acfg);
        acc->setIsCreated(true);
    } catch (const Error& err) {
        qInfo() << "Account create failed, status:" << err.status;
        return err.status;
    }

    return OK;
}

int ModuleSIP::doCall(const SipUri &dist)
{
    using sip_private::MyCall;
    if (!acc)
        return ACCOUNT_UNREGISTRED;

    if (acc->call) {
        if (acc->call->isActive()) {
            return PJSIP_SC_BUSY_HERE;
        }
        acc->call.reset(nullptr);
    }

    acc->call = std::make_unique<MyCall>(*acc, PJSUA_INVALID_ID, acc->stateCallback);

    CallOpParam prm(true);
    try {
        acc->call->makeCall(dist.toString().toStdString(), prm);
    } catch(const Error& err) {
        acc->call.reset(nullptr);
        return err.status;
    }
    return OK;
}

int ModuleSIP::doAcceptCall()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        acc->answerCall();
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

int ModuleSIP::doRejectCall()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        acc->rejectCall();
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

int ModuleSIP::doHangUpCall()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        CallOpParam prm;
        acc->call->hangup(prm);
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

int ModuleSIP::doHoldCall()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        CallOpParam prm(true);
        acc->call->setHold(prm);
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

int ModuleSIP::doUnHoldCall()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        CallOpParam prm(true);
        prm.opt.flag = PJSUA_CALL_UNHOLD;
        acc->call->reinvite(prm);
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

int ModuleSIP::doMute()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        acc->call->setMuteVoice(true);
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

int ModuleSIP::doUnMute()
{
    if (int status = checkAccountAndCall(); status != OK)
        return status;

    try {
        acc->call->setMuteVoice(false);
    } catch (const Error& err) {
        return err.status;
    }
    return OK;
}

QString ModuleSIP::getTextError(int code)
{
    if (code == ACCOUNT_UNREGISTRED)
        return QString("Аккаунт не создан. Требуется авторизация.");

    char buf[128];
    pj_strerror(code, buf, sizeof(buf));
    return QString::fromUtf8(buf);
}

} // namespace sip
