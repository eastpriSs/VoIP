#include "module_sip.h"

using namespace sip;

void ModuleSIP::onAccountRegStateChanged(int code)
{
    emit registrationStateChanged(code);
}

ModuleSIP::ModuleSIP()
    : acc(new MyAccount()), isEndpointInit(false)
{
    connect(acc.get(), &MyAccount::regStateChanged, this, &ModuleSIP::onAccountRegStateChanged);
}

ModuleSIP::~ModuleSIP()
{
    if (isEndpointInit)
        ep.libDestroy();
}

int ModuleSIP::doRegister(const AuthCredits& authCredits)
{
    constexpr int OK = 200;
    ep.libCreate();

    // Initialize endpoint
    EpConfig ep_cfg;
    ep.libInit( ep_cfg );
    isEndpointInit = true;

    // Create SIP transport. Error handling sample is shown
    TransportConfig tcfg;
    tcfg.port = authCredits.getPort();
    try {
        ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
    } catch (Error &err) {
        return err.status;
    }

    ep.libStart();
    qInfo() << "*** PJSUA2 STARTED ***" << '\n';

    // Configure an AccountConfig
    QString idUri = authCredits.getIDUri();
    AccountConfig acfg;
    acfg.idUri = idUri.toStdString();
    acfg.regConfig.registrarUri = authCredits.getRegistrarUri().toStdString();
    AuthCredInfo cred("digest", "*", authCredits.getLogin().toStdString(), 0, authCredits.getPassword().toStdString());
    acfg.sipConfig.authCreds.push_back( cred );

    qInfo() << "ID Uri : " << acfg.idUri << '\n';
    qInfo() << "ID Reg Uri : " << acfg.regConfig.registrarUri  << '\n';

    try {
        acc->create(acfg);
        qInfo() << "sent create "<<'\n';
        acc->setIsCreated(true);
    } catch (Error& err) {
        qInfo() << "status: " << err.status  << '\n';
        return err.status;
    }
    return OK;
}

MyAccount::MyAccount()
    : isCreated(false)
{
}

void MyAccount::onRegState(OnRegStateParam &prm)
{
    AccountInfo ai = getInfo();
    qInfo() << (ai.regIsActive? "*** Register:" : "*** Unregister:")
            << " code=" << prm.code << '\n';
    emit regStateChanged(prm.code);
}

MyAccount::~MyAccount()
{
    if (isCreated)
        shutdown();
}


void MyAccount::setIsCreated(bool newIsCreated)
{
    isCreated = newIsCreated;
}
