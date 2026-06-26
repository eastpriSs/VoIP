#include "authmenumodel.h"
#include <QDebug>

AuthMenuModel::AuthMenuModel(QObject *parent) : QObject(parent) {}

bool AuthMenuModel::validateCredentials(const QString& username, const QString& password) {
    return !username.isEmpty() && !password.isEmpty();
}

void AuthMenuModel::login(const QString& username, const QString& password) {
    qDebug() << "Login attempt:" << username;
    if (validateCredentials(username, password)) {
        emit loginSuccess();
    } else {
        emit loginFailed("Неверный логин или пароль");
    }
}

void AuthMenuModel::registerUser(const QString& username, const QString& password) {
    qDebug() << "Register attempt:" << username;
    if (validateCredentials(username, password)) {
        emit registerSuccess();
    } else {
        emit registerFailed("Логин и пароль не могут быть пустыми");
    }
}
