#include <QDebug>
#include "auth_menu_model.h"

AuthMenuModel::AuthMenuModel(std::shared_ptr<AuthController> controller, QObject *parent)
    : authController(controller),  QObject(parent)
{
    connect(authController.get(), &AuthController::registrationFailed, this, &AuthMenuModel::onRegistrationError);
    connect(authController.get(), &AuthController::registrationSucceeded, this, &AuthMenuModel::onRegistrationSuccess);
    connect(authController.get(), &AuthController::validationDataCompleted, this, &AuthMenuModel::onValidationDataCompleted);
    connect(authController.get(), &AuthController::registrationRequestCreated, this, &AuthMenuModel::onRegistrationRequestCreated);
}

void AuthMenuModel::login(const QString& username, const QString& password)
{
}

void AuthMenuModel::registerUser(const QString& username,
                                 const QString& password,
                                 const QString& sipServer,
                                 int sipPort)
{
    try {
        authController->registerUser(username, password, sipServer, sipPort);
    } catch (const std::invalid_argument& exception) {
        emit registerFailed(exception.what());
        return;
    }
}

void AuthMenuModel::onRegistrationError(QString text)
{
    emit registerFailed(text);
}

void AuthMenuModel::onRegistrationSuccess()
{
    emit progressChanged("Регистрация завершена.");
    emit registerSuccess();
}

void AuthMenuModel::onValidationDataCompleted(bool success)
{
    emit progressChanged(success ? "Валидация прошла успешно." : "Валидация не пройдена.");
}

void AuthMenuModel::onRegistrationRequestCreated()
{
    emit progressChanged("Запрос на регистрацию отправлен. Ожидаем ответ сервера...");
}
