#ifndef MY_CALL_H
#define MY_CALL_H

#include <pjsua2.hpp>
#include <functional>
#include <QString>

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

}

#endif // MY_CALL_H
