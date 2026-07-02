#include "modulesip.h"

sip::ModuleSIP::ModuleSIP()
{
    bufferIdUri = new char[BUFFER_SIZE];
    bufferIdRegistrarUri = new char[BUFFER_SIZE];
}

sip::ModuleSIP::~ModuleSIP()
{
    bufferIdUri[BUFFER_SIZE - 1] = '\0';
    bufferIdRegistrarUri[BUFFER_SIZE - 1] = '\0';
    delete[] bufferIdUri;
    delete[] bufferIdRegistrarUri;
}

void sip::ModuleSIP::doRegister(char *username, char *password, char *server, int port)
{
    Endpoint ep;

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
        qInfo() << err.info().c_str() << '\n';
        return;
    }

    // Start the library (worker threads etc)
    ep.libStart();
    qInfo() << "*** PJSUA2 STARTED ***" << '\n';

    snprintf(bufferIdUri, BUFFER_SIZE, "sip:%s@%s", username, server);
    snprintf(bufferIdRegistrarUri, BUFFER_SIZE, "sip:%s@%s:%d", username, server, tcfg.port);

    qInfo() << "ID Uri : " << bufferIdUri << '\n';
    qInfo() << "ID Reg Uri : " << bufferIdRegistrarUri << '\n';

    // Configure an AccountConfig
    AccountConfig acfg;
    acfg.idUri = bufferIdUri;
    acfg.regConfig.registrarUri = bufferIdRegistrarUri;
    AuthCredInfo cred("digest", "*", "test", 0, "secret");
    acfg.sipConfig.authCreds.push_back( cred );

    // Create the account
    MyAccount *acc = new MyAccount;
    try {
        acc->create(acfg);
    } catch (Error& err) {
        qInfo() << err.info().c_str() << '\n';
        return;
    }
}

void sip::MyAccount::onRegState(OnRegStateParam &prm)
{
    AccountInfo ai = getInfo();
    qInfo() << (ai.regIsActive? "*** Register:" : "*** Unregister:")
            << " code=" << prm.code << '\n';

}
