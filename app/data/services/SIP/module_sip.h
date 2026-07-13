#pragma once
#include <QObject>
#include <QString>
#include <memory>
#include <functional>
#include <pjsua2.hpp>
#include "auth_credits.h"
#include "sip_uri.h"

namespace sip {
class ModuleSIP;
}

namespace sip_private {

class MyCall : public pj::Call {
public:
    using StateCallback = std::function<void(int callId, int stateCode, const QString& stateText)>;

    explicit MyCall(pj::Account &acc, int call_id = PJSUA_INVALID_ID, StateCallback cb = nullptr);
    ~MyCall() override = default;

    void onCallState(pj::OnCallStateParam &prm) override;
    void onCallMediaState(pj::OnCallMediaStateParam &prm) override;

    void setMuteVoice(bool v);

private:
    void applyMute();

    StateCallback stateCallback;
    bool muteVoice;
};

class MyAccount : public pj::Account {
public:
    using RegCallback = std::function<void(int)>;
    using IncomingCallCallback = std::function<void(QString remoteUri, int callId)>;

    explicit MyAccount(RegCallback cb, IncomingCallCallback icb, MyCall::StateCallback stcb = nullptr);
    ~MyAccount() override;

    void onRegState(pj::OnRegStateParam &prm) override;
    void onIncomingCall(pj::OnIncomingCallParam &iprm) override;

    void setIsCreated(bool v);
    void answerCall();
    void rejectCall();

private:
    friend class sip::ModuleSIP;

    std::unique_ptr<MyCall> call;
    RegCallback regCallback;
    IncomingCallCallback inCallback;
    MyCall::StateCallback stateCallback;
    bool isCreated;
};

} // namespace sip_private

namespace sip {

enum ReturningStates
{
    OK = 200,
    ACCOUNT_UNREGISTRED = 100
};

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
