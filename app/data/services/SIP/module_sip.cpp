#include "module_sip.h"
#include <pjsua2.hpp>
#include <QDebug>
#include <functional>
#include <memory>

using namespace pj;

namespace sip_private {

class MyCall : public Call {
public:
    using StateCallback = std::function<void(int callId, int stateCode, const QString& stateText)>;

    explicit MyCall(Account &acc, int call_id = PJSUA_INVALID_ID, StateCallback cb = nullptr)
        : Call(acc, call_id), stateCallback(std::move(cb)) {}

    ~MyCall() override = default;

    void onCallState(OnCallStateParam &prm) override {
        CallInfo ci = getInfo();
        qInfo() << "call state:" << ci.stateText;
        if (stateCallback) {
            stateCallback(ci.id, ci.state, QString::fromStdString(ci.stateText));
        }
    }
private:
    StateCallback stateCallback;
};

class MyAccount : public Account {
public:
    using RegCallback = std::function<void(int)>;
    using IncomingCallCallback = std::function<void(QString remoteUri, int callId)>;

    explicit MyAccount(RegCallback cb, IncomingCallCallback icb)
        : regCallback(std::move(cb)), inCallback(icb), call(nullptr), isCreated(false) {}

    ~MyAccount() override {
        if (isCreated) shutdown();
    }

    void onRegState(OnRegStateParam &prm) override {
        AccountInfo ai = getInfo();
        qInfo() << (ai.regIsActive ? "*** Register:" : "*** Unregister:")
                << " code=" << prm.code;

        if (regCallback) {
            regCallback(prm.code);
        }
    }

    void onIncomingCall(OnIncomingCallParam &iprm) override
    {
        // TODO handle call is active
        // if (call && call->isActive())

        // if (call)
        //     delete call;

        call = new MyCall(*this, iprm.callId);
        CallInfo ci = call->getInfo();

        if (inCallback)
            inCallback(QString::fromStdString(ci.remoteUri), iprm.callId);
    }

    void setIsCreated(bool v) { isCreated = v; }
    void answerCall();
    void rejectCall();

private:
    RegCallback regCallback;
    IncomingCallCallback inCallback;
    Call* call;
    CallOpParam prm;
    bool isCreated;
};

class SIPImpl {
public:
    SIPImpl();
    ~SIPImpl();
    int doRegister(const AuthCredits& authCredits, sip::ModuleSIP* owner);
    int doCall(const SipUri& sipUri);
    int acceptCall();
    int rejectCall();

private:
    Endpoint ep;
    std::unique_ptr<MyAccount> acc;
    bool isEndpointInit = false;
};

SIPImpl::SIPImpl() = default;

SIPImpl::~SIPImpl() {
    if (isEndpointInit) {
        ep.libDestroy();
    }
}


int SIPImpl::doRegister(const AuthCredits& authCredits, sip::ModuleSIP* owner)
{
    if (!isEndpointInit) {
        ep.libCreate();
        EpConfig ep_cfg;
        ep.libInit(ep_cfg);

        TransportConfig tcfg;
        tcfg.port = 0;
        try {
            ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
        } catch (Error &err) {
            qWarning() << "Transport create failed:" << err.status;
            return err.status;
        }

        ep.libStart();
        isEndpointInit = true;
        qInfo() << "*** PJSUA2 STARTED ***";
    }

    if (acc) {
        try {
            acc->shutdown();
        } catch (Error& err) {
            qWarning() << "Account shutdown failed:" << err.status;
        }
        acc.reset();
    }

    AccountConfig acfg;
    acfg.idUri = authCredits.getIDUri().toStdString();
    acfg.regConfig.registrarUri = authCredits.getRegistrarUri().toStdString();
    AuthCredInfo cred("digest", "*", authCredits.getLogin().toStdString(), 0, authCredits.getPassword().toStdString());
    acfg.sipConfig.authCreds.push_back(cred);

    qInfo() << "ID Uri : " << QString::fromStdString(acfg.idUri);
    qInfo() << "ID Reg Uri : " << QString::fromStdString(acfg.regConfig.registrarUri);

    try {
        acc = std::make_unique<MyAccount>(
            // InRegState callback
          [owner](int code) {
            emit owner->registrationStateChanged(code);
        },
            // InComingCall callback
          [owner](QString remoteUri, int callId) {
              emit owner->incomingCallReceived(std::move(remoteUri), callId);
          });
        acc->create(acfg);
        acc->setIsCreated(true);
    } catch (Error& err) {
        qWarning() << "Account create failed, status:" << err.status;
        return err.status;
    }

    return sip::OK;
}

int SIPImpl::doCall(const SipUri &sipUri)
{
    Call *call;
    if (acc)
        call = new MyCall(*acc);
    else
        return sip::ACCOUNT_UNREGISTRED;

    CallOpParam prm(true);
    try {
        call->makeCall(sipUri.toString().toStdString(), prm);
    } catch(Error& err) {
        return err.status;
    }
    return sip::OK;
}

int SIPImpl::acceptCall()
{
    acc->answerCall();
    return sip::OK;
}

int SIPImpl::rejectCall()
{
    acc->rejectCall();
    return sip::OK;
}

void MyAccount::answerCall()
{
    prm.statusCode = PJSIP_SC_OK;
    call->answer(prm);
}

void MyAccount::rejectCall()
{
    prm.statusCode = PJSIP_SC_DECLINE;
    call->answer(prm);
}

} // namespace sip_private

namespace sip {

ModuleSIP::ModuleSIP(QObject* parent)
    : QObject(parent), impl(std::make_unique<sip_private::SIPImpl>())
{}

ModuleSIP::~ModuleSIP() = default;

int ModuleSIP::doRegister(const AuthCredits& authCredits) {
    return impl->doRegister(authCredits, this);
}

int ModuleSIP::doCall(const SipUri &dist)
{
    return impl->doCall(dist);
}

int ModuleSIP::doAcceptCall()
{
    return impl->acceptCall();
}

int ModuleSIP::doRejectCall()
{
    return impl->rejectCall();
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
