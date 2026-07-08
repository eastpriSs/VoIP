#pragma once
#include <QObject>
#include <QString>
#include <memory>
#include "auth_credits.h"
#include "sip_uri.h"

namespace sip_private {

class SIPImpl;
class MyAccount;

} // namespace sip_private

namespace sip {

using namespace sip_private;

constexpr int OK = 200;

class ModuleSIP : public QObject
{
    Q_OBJECT
public:
    explicit ModuleSIP(QObject* parent = nullptr);
    ~ModuleSIP() override;

    int doRegister(const AuthCredits& authCredits);
    int doCall(const SipUri& dist);

    QString getTextError(int code);
signals:
    void registrationStateChanged(int code, const QString& info = "");
    void incomingCallReceived(const QString& remoteUri, int callId);
    void callStateChanged(int callId, int pjsip_state, const QString& stateText);

public:
    std::unique_ptr<SIPImpl> impl;
};
} // namespace sip
