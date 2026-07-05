#pragma once


#include <QObject>
#include <QString>
#include <QTimer>
#include <pjsua2.hpp>
#include <QDebug>
#include "auth_credits.h"

namespace sip {

using namespace pj;

class MyAccount : public Account {
public:
    MyAccount();
    void onRegState(OnRegStateParam &prm) override;
    ~MyAccount();
    void setIsCreated(bool newIsCreated);

private:
    bool isCreated;
};

class ModuleSIP : public QObject
{
    Q_OBJECT

signals:
    void ErrorRegistration(QString errorInfo, int errorCode);

public:
    ModuleSIP();
    ~ModuleSIP();
    void doRegister(const AuthCredits& authCredits);
private:
    Endpoint ep;
    std::unique_ptr<MyAccount> acc;
    bool isEndpointInit;
};


}
