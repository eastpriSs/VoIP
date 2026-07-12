#include <QDebug>
#include "call_menu_model.h"

CallMenuModel::CallMenuModel(std::shared_ptr<CallController> cc, QObject *parent)
    : callController(cc), QObject(parent)
{
    connect(cc.get(), &CallController::callNumberFailed, this, &CallMenuModel::onCallNumberFailed);
    connect(cc.get(), &CallController::callNumberSuccess, this, &CallMenuModel::onCallNumberSuccess);
    connect(cc.get(), &CallController::validationDataCompleted, this, &CallMenuModel::onValidationDataCompleted);

    connect(cc.get(), &CallController::incomingCall, this, &CallMenuModel::onIncomingCall);
    connect(cc.get(), &CallController::callingCall, this, &CallMenuModel::onCallingCall);
    connect(cc.get(), &CallController::earlyMediaCall, this, &CallMenuModel::onEarlyMediaCall);
    connect(cc.get(), &CallController::connectingCall, this, &CallMenuModel::onConnectingCall);
    connect(cc.get(), &CallController::activeCall, this, &CallMenuModel::onActiveCall);
    connect(cc.get(), &CallController::disconnectedCall, this, &CallMenuModel::onDisconnectCall);
}

void CallMenuModel::onValidationDataCompleted(bool success)
{
    emit statusBarTextRequest("Имя пользователя введено " + QString(success ? "верно" : "неверно"));
}

void CallMenuModel::onCallingCall()
{
    emit statusBarTextRequest("Текущий вызов (заглушка).");
}

void CallMenuModel::onIncomingCall(QString remoteUri)
{
    emit incomingCallMenuRequested(remoteUri);
}

void CallMenuModel::onEarlyMediaCall()
{
    emit statusBarTextRequest("Гудки...");
}

void CallMenuModel::onConnectingCall()
{
    emit statusBarTextRequest("Подключение...");
}

void CallMenuModel::onActiveCall()
{
    emit callingMenuRequested();
}

void CallMenuModel::onDisconnectCall(const QString &reason)
{
    emit rejectMenuRequested();
    emit statusBarTextRequest("Пользователь сбросил вызов.");
}


void CallMenuModel::onKeyPressed(const QString& text) {
    currentNumber += text;
    emit textChanged(currentNumber);
}

void CallMenuModel::onBackspacePressed() {
    if (!currentNumber.isEmpty()) {
        currentNumber.chop(1);
        emit textChanged(currentNumber);
    }
}

void CallMenuModel::onClearPressed() {
    currentNumber.clear();
    emit textChanged(currentNumber);
}

void CallMenuModel::onLayoutSwitchRequested(int layoutId) {
    emit layoutChanged(layoutId);
}

void CallMenuModel::onConfirmPressed(const QString& number)
{
    callController->callNumber(number);
}

void CallMenuModel::onIncomingCallAccept()
{
    callController->acceptCall();
    emit callingMenuRequested();
    emit statusBarTextRequest("Запрос на вызов принят.");
}

void CallMenuModel::onIncomingCallRejected()
{
    callController->rejectCall();
    emit rejectMenuRequested();
    emit statusBarTextRequest("Запрос на вызов сброшен.");
}

void CallMenuModel::onCallNumberFailed(QString error)
{
    emit errorRequested("Ошибка при вызове номера.", error);
}

void CallMenuModel::onCallNumberSuccess()
{
    emit statusBarTextRequest("Звонок пользователю " + currentNumber + "...");
}

void CallMenuModel::onMuteToggled(bool isMuted)
{
    qInfo() << "Режим без звука:" << isMuted;
}

void CallMenuModel::onHoldToggled(bool isHeld)
{
    qInfo() << "Режим удержания звонка : " << isHeld;

    if (isHeld) {
        callController->holdCall();
    } else {
        callController->unHoldCall();
    }
}

void CallMenuModel::onCallHangUp()
{
    qInfo() << "Завершаем звонок.";
    callController->hangUpCall();
    emit rejectMenuRequested();
}
