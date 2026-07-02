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
    virtual void onRegState(OnRegStateParam &prm) {
        AccountInfo ai = getInfo();
        qInfo() << (ai.regIsActive? "*** Register:" : "*** Unregister:")
                  << " code=" << prm.code << '\n';
    }
};

class ModuleSIP
{
public:
    void doRegister(char* username, char* password, char* server);
};


}
