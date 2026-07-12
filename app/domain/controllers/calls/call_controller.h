#ifndef CALL_CONTROLLER_H
#define CALL_CONTROLLER_H

#include <QObject>
#include <QString>
#include "call_repository.h"
#include "call_state.h"

class CallController : public QObject
{
    Q_OBJECT
public:
    explicit CallController(std::shared_ptr<ICallRepository> rep, QObject *parent = nullptr);
    void callNumber(QString number);
    void hangUpCall();
    void acceptCall();
    void rejectCall();
    void holdCall();
    void unHoldCall();

signals:
    void callNumberFailed(QString error);
    void callNumberSuccess();
    void incomingCall(QString remoteUri);
    void validationDataCompleted(bool success = true);

    void callingCall();
    void incomingCallState();
    void earlyMediaCall();
    void connectingCall();
    void activeCall();
    void disconnectedCall(const QString& reason);

private slots:
    void onIncomingCall(SipUri remoteUri, int callID);
    void onCallStateChanged(CallState state, const QString& stateText);

private:
    std::shared_ptr<ICallRepository> repo;
};

#endif // CALL_CONTROLLER_H
