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
    virtual void onRegState(OnRegStateParam &prm);
};

class ModuleSIP : public QObject
{
    Q_OBJECT

signals:
    void ErrorRegistration(QString errorInfo, int errorCode);

public:
    ModuleSIP();
    ~ModuleSIP();
    void doRegister(char* username, char* password, char* server, int port);
private:
    char* bufferIdUri;
    char* bufferIdRegistrarUri;
    static constexpr ushort BUFFER_SIZE = 100;
};


}
