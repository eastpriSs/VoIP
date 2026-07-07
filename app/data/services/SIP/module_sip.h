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
    Q_OBJECT
public:
    MyAccount();
    ~MyAccount();

    void onRegState(OnRegStateParam &prm) override;
    void setIsCreated(bool newIsCreated);

signals:
    void regStateChanged(OnRegStateParam &prm);

private:
    bool isCreated;
};

class ModuleSIP : public QObject
{
    Q_OBJECT

signals:
    void registrationStateChanged(int code, QString info = "");

private slots:
    void onAccountRegStateChanged(OnRegStateParam &prm);

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
