#include "call_menu_model.h"

CallMenuModel::CallMenuModel(std::shared_ptr<CallController> cc, QObject *parent)
    : callController(cc), QObject(parent)
{
    connect(cc.get(), &CallController::callNumberFailed, this, &CallMenuModel::onCallNumberFailed);
    connect(cc.get(), &CallController::callNumberSuccess, this, &CallMenuModel::onCallNumberSuccess);
    connect(cc.get(), &CallController::validationDataCompleted, this, &CallMenuModel::onValidationDataCompleted);
    connect(cc.get(), &CallController::incomingCall, this, &CallMenuModel::onIncomingCall);
}

void CallMenuModel::onValidationDataCompleted(bool success)
{
    emit statusBarTextRequest("Имя пользователя введено " + QString(success ? "верно" : "неверно"));
}

void CallMenuModel::onIncomingCall(QString remoteUri)
{
    emit incomingCallMenuRequested(remoteUri);
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
