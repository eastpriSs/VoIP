#ifndef CALL_MENU_MODEL_H
#define CALL_MENU_MODEL_H

#include <QObject>
#include <QString>
#include "call_controller.h"

class CallMenuModel : public QObject
{
    Q_OBJECT
public:
    explicit CallMenuModel(std::shared_ptr<CallController> cc, QObject *parent = nullptr);

public slots:
    void onKeyPressed(const QString& text);
    void onBackspacePressed();
    void onClearPressed();
    void onLayoutSwitchRequested(int layoutId);
    void onConfirmPressed(const QString& number);
    void onIncomingCallAccept();
    void onIncomingCallRejected();

private slots:
    void onCallNumberFailed(QString error);
    void onCallNumberSuccess();
    void onValidationDataCompleted(bool success = true);
    void onIncomingCall(QString remoteUri);

signals:
    void textChanged(const QString& text);
    void layoutChanged(int layoutId);
    void warningRequested(const QString& title, const QString& message);
    void errorRequested(const QString& title, const QString& message);
    void statusBarTextRequest(const QString& text);
    void incomingCallMenuRequested(const QString& remoteUri);
    void callingMenuRequested();
    void rejectMenuRequested();
    void callAccepted();
    void callRejected();

private:
    QString currentNumber;
    std::shared_ptr<CallController> callController;
};

#endif // CALL_MENU_MODEL_H
