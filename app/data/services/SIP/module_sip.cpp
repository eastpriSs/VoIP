#include "module_sip.h"
#include <pjsua2.hpp>
#include <QDebug>
#include <functional>
#include <memory>

using namespace pj;

namespace sip_private {

class MyAccount : public Account {
public:
    using RegCallback = std::function<void(int)>;

    explicit MyAccount(RegCallback cb) : regCallback(std::move(cb)), isCreated(false) {}
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

    void setIsCreated(bool v) { isCreated = v; }

private:
    RegCallback regCallback;
    bool isCreated;
};

class SIPImpl {
public:
    SIPImpl();
    ~SIPImpl();
    int doRegister(const AuthCredits& authCredits, sip::ModuleSIP* owner);

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
        tcfg.port = authCredits.getPort();
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
        acc = std::make_unique<MyAccount>([owner](int code) {
            emit owner->registrationStateChanged(code);
        });
        acc->create(acfg);
        acc->setIsCreated(true);
    } catch (Error& err) {
        qWarning() << "Account create failed, status:" << err.status;
        return err.status;
    }

    return sip::OK;
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

QString ModuleSIP::getTextError(int code)
{
    char buf[128];
    pj_strerror(code, buf, sizeof(buf));
    return QString::fromUtf8(buf);
}

} // namespace sip
