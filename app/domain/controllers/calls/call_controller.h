#ifndef CALL_CONTROLLER_H
#define CALL_CONTROLLER_H

#include <QObject>
#include <QString>
#include "call_repository.h"

class CallController : public QObject
{
    Q_OBJECT
public:
    explicit CallController(std::shared_ptr<ICallRepository> rep, QObject *parent = nullptr);
    void callNumber(QString number);
    void acceptCall();
    void rejectCall();

signals:
    void callNumberFailed(QString error);
    void callNumberSuccess();
    void incomingCall(QString remoteUri);
    void validationDataCompleted(bool success = true);

private slots:
    void onIncomingCall(SipUri remoteUri, int callID);

private:
    std::shared_ptr<ICallRepository> repo;
};

#endif // CALL_CONTROLLER_H
