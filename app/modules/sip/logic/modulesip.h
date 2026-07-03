#pragma once


#include <QObject>
#include <QString>
#include <QTimer>
#include <pjsua2.hpp>
#include <QDebug>

namespace sip {

using namespace pj;

class MyAccount : public Account {
public:
    void onRegState(OnRegStateParam &prm) override;
    ~MyAccount();
};

class ModuleSIP : public QObject
{
    Q_OBJECT

signals:
    void ErrorRegistration(QString errorInfo, int errorCode);

public:
    ModuleSIP();
    ~ModuleSIP();
    void doRegister(const QString& username, const QString& password, const QString& server, int port);
private:
    Endpoint ep;
    std::unique_ptr<MyAccount> acc;
};


}
