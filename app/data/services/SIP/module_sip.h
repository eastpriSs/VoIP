#pragma once
#include <QObject>
#include <QString>
#include <memory>
#include "auth_credits.h"

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
    QString getTextError(int code);
signals:
    void registrationStateChanged(int code, const QString& info = "");

public:
    std::unique_ptr<SIPImpl> impl;
};
} // namespace sip
