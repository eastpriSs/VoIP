#include "modulesip.h"

sip::ModuleSIP::ModuleSIP()
    : acc(new MyAccount())
{
}

sip::ModuleSIP::~ModuleSIP()
{
    ep.libDestroy();
}

void sip::ModuleSIP::doRegister(const QString& username, const QString& password, const QString& server, int port)
{
    ep.libCreate();

    // Initialize endpoint
    EpConfig ep_cfg;
    ep.libInit( ep_cfg );

    // Create SIP transport. Error handling sample is shown
    TransportConfig tcfg;
    tcfg.port = port;
    try {
        ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
    } catch (Error &err) {
        emit ErrorRegistration(err.info().c_str(), err.status);
        return;
    }

    ep.libStart();
    qInfo() << "*** PJSUA2 STARTED ***" << '\n';

    // Configure an AccountConfig
    QString idUri = QString("sip:%1@%2").arg(username, server);
    AccountConfig acfg;
    acfg.idUri = idUri.toStdString();
    acfg.regConfig.registrarUri = (idUri + ':' + QString::number(port)).toStdString();
    AuthCredInfo cred("digest", "*", username.toStdString(), 0, password.toStdString());
    acfg.sipConfig.authCreds.push_back( cred );

    qInfo() << "ID Uri : " << acfg.idUri << '\n';
    qInfo() << "ID Reg Uri : " << acfg.regConfig.registrarUri  << '\n';

    try {
        acc->create(acfg);
    } catch (Error& err) {
        emit ErrorRegistration(err.info().c_str(), err.status);
        return;
    }
}

void sip::MyAccount::onRegState(OnRegStateParam &prm)
{
    AccountInfo ai = getInfo();
    qInfo() << (ai.regIsActive? "*** Register:" : "*** Unregister:")
            << " code=" << prm.code << '\n';

}

sip::MyAccount::~MyAccount()
{
    shutdown();
}
