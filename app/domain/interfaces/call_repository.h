#ifndef CALL_REPOSITORY_H
#define CALL_REPOSITORY_H

#include <QObject>
#include "sip_uri.h"
#include "call_error.h"

class ICallRepository : public QObject {
    Q_OBJECT
public:
    explicit ICallRepository(QObject* parent = nullptr) : QObject(parent) {}
    virtual void callSipAccount(const SipUri& sipUri) = 0;

signals:
    void initCallSuccess();
    void initCallFailed(const CallError& error);
};

#endif // CALL_REPOSITORY_H
