#include "auth_menu_presenter.h"

AuthMenuPresenter::AuthMenuPresenter(AuthMenu* v, AuthMenuModel* model, QObject* parent)
    : QObject(parent), view(v), model(model) {

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
    connect(model, &AuthMenuModel::progressChanged,
            this, &AuthMenuPresenter::onProgressChanged);
    connect(this, &AuthMenuPresenter::regSuccess, view, &AuthMenu::onRegisterSucces);
    connect(this, &AuthMenuPresenter::regFailed, view, &AuthMenu::onRegisterFailed);
    connect(this, &AuthMenuPresenter::progressChanged, view, &AuthMenu::onProgressChanged);

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

void AuthMenuPresenter::onLoginFailed(QString error) {
}

void AuthMenuPresenter::onRegisterSuccess() {
    regSuccess("Пользователь зарегистрирован.");
}

void AuthMenuPresenter::onRegisterFailed(QString error) {
    emit regFailed(error);
}

void AuthMenuPresenter::onProgressChanged(QString status)
{
    emit progressChanged(std::move(status));
}
