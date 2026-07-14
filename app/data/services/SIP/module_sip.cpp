#include <QDebug>

#include "returning_states.h"
#include "module_sip.h"


using namespace pj;

namespace sip {

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
            [this](int code)
            {
                emit registrationStateChanged(code);
            },

            [this](QString remoteUri, int callId)
            {
                emit incomingCallReceived(std::move(remoteUri), callId);
            },

            [this](int callId, int pjsip_state, const QString& stateText)
            {
                if (pjsip_state == PJSIP_INV_STATE_DISCONNECTED)
                    acc->call.reset(nullptr);
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
