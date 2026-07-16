#ifndef CALL_CONTROLLER_H
#define CALL_CONTROLLER_H

#include <QObject>
#include <QString>
#include "call_repository.h"
#include "call_state.h"
#include "call_initiator.h"

class CallController : public QObject, public ICallInitiator
{
    Q_OBJECT
public:
    explicit CallController(std::shared_ptr<ICallRepository> rep, QObject *parent = nullptr);

    void initiateCall(const QString& number) override;

    void hangUpCall();
    void acceptCall();
    void rejectCall();
    void holdCall();
    void unHoldCall();
    void mute();
    void unMute();

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
