#include "authmenupresenter.h"
#include <QMessageBox>

AuthMenuPresenter::AuthMenuPresenter(AuthMenu* v, QObject* parent)
    : QObject(parent), view(v) {
    model = new AuthMenuModel(this);

    connect(view, &AuthMenu::loginRequested,
            this, &AuthMenuPresenter::onLoginRequested);
    connect(view, &AuthMenu::registerRequested,
            this, &AuthMenuPresenter::onRegisterRequested);
    connect(model, &AuthMenuModel::loginSuccess,
            this, &AuthMenuPresenter::onLoginSuccess);
    connect(model, &AuthMenuModel::loginFailed,
            this, &AuthMenuPresenter::onLoginFailed);
    connect(model, &AuthMenuModel::registerSuccess,
            this, &AuthMenuPresenter::onRegisterSuccess);
    connect(model, &AuthMenuModel::registerFailed,
            this, &AuthMenuPresenter::onRegisterFailed);
}

void AuthMenuPresenter::onLoginRequested(const QString& username, const QString& password) {
    model->login(username, password);
}

void AuthMenuPresenter::onRegisterRequested(const QString& username,
                                            const QString& password,
                                            const QString& sipServer,
                                            int sipPort) {
    model->registerUser(username, password, sipServer, sipPort);
}

void AuthMenuPresenter::onLoginSuccess() {
    view->accept();
}

void AuthMenuPresenter::onLoginFailed(const QString& error) {
    QMessageBox::warning(view, "Ошибка входа", error);
}

void AuthMenuPresenter::onRegisterSuccess() {
    QMessageBox::information(view, "Регистрация", "Пользователь успешно зарегистрирован!");
}

void AuthMenuPresenter::onRegisterFailed(const QString& error) {
    QMessageBox::warning(view, "Ошибка регистрации", error);
}
