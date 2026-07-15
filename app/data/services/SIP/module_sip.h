#pragma once
#include <QObject>
#include <QString>
#include <pjsua2.hpp>
#include "auth_credits.h"
#include "sip_uri.h"
#include "my_account.h"

namespace sip {

class ModuleSIP : public QObject
{
    Q_OBJECT
public:
    explicit ModuleSIP(QObject* parent = nullptr);
    ~ModuleSIP() override;

    int doRegister(const AuthCredits& authCredits);
    int doCall(const SipUri& dist);
    int doAcceptCall();
    int doRejectCall();
    int doHangUpCall();
    int doHoldCall();
    int doUnHoldCall();
    int doMute();
    int doUnMute();

    QString getTextError(int code);

signals:
    void registrationStateChanged(int code, const QString& info = "");
    void incomingCallReceived(const QString& remoteUri, int callId);
    void callStateChanged(int callId, int pjsip_state, const QString& stateText);

private:
    int checkAccountAndCall() const;

private:
    pj::Endpoint ep;
    std::unique_ptr<sip_private::MyAccount> acc;
    bool isEndpointInit;
};

} // namespace sip
