#ifndef CALL_REPOSITORY_H
#define CALL_REPOSITORY_H

#include <QObject>
#include "sip_uri.h"
#include "call_error.h"
#include "call_state.h"

class ICallRepository : public QObject {
    Q_OBJECT
public:
    explicit ICallRepository(QObject* parent = nullptr) : QObject(parent) {}
    virtual void callSipAccount(const SipUri& sipUri) = 0;
    virtual void acceptSipCall() = 0;
    virtual void rejectSipCall() = 0;

signals:
    void initCallSuccess();
    void initCallFailed(const CallError& error);
    void incomingCall(SipUri remoteSip, int callID);
    void callStateChenged(CallState callState, const QString& state);
};

#endif // CALL_REPOSITORY_H
