#ifndef MY_ACCOUNT_H
#define MY_ACCOUNT_H

#include <pjsua2.hpp>
#include <functional>
#include <QString>

#include "my_call.h"

namespace sip{
class ModuleSIP;
}

namespace sip_private {

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
}

#endif // MY_ACCOUNT_H
