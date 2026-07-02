#include "modulesip.h"

void sip::ModuleSIP::doRegister(char *username, char *password, char *server)
{
    Endpoint ep;

    ep.libCreate();

    // Initialize endpoint
    EpConfig ep_cfg;
    ep.libInit( ep_cfg );

    // Create SIP transport. Error handling sample is shown
    TransportConfig tcfg;
    tcfg.port = 5060;
    try {
        ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
    } catch (Error &err) {
        qInfo() << err.info().c_str() << '\n';
        return;
    }

    // Start the library (worker threads etc)
    ep.libStart();
    qInfo() << "*** PJSUA2 STARTED ***" << '\n';

    // Configure an AccountConfig
    AccountConfig acfg;
    acfg.idUri = "sip:test@0.0.0.0";
    acfg.regConfig.registrarUri = "sip:test@0.0.0.0:5060";
    AuthCredInfo cred("digest", "*", "test", 0, "secret");
    acfg.sipConfig.authCreds.push_back( cred );

    // Create the account
    MyAccount *acc = new MyAccount;
    acc->create(acfg);
}
