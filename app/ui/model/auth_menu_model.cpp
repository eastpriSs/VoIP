#include <QDebug>
#include "auth_menu_model.h"

AuthMenuModel::AuthMenuModel(std::shared_ptr<AuthController> controller, QObject *parent)
    : authController(controller),  QObject(parent)
{
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
    } catch (std::invalid_argument exception) {
        emit registerFailed(exception.what());
    }
}

void AuthMenuModel::onRegistrationError(QString text, int code)
{
    emit registerFailed(text);
}
