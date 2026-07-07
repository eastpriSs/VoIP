#ifndef AUTHMENUPRESENTER_H
#define AUTHMENUPRESENTER_H

#include <QObject>
#include "auth_menu_model.h"
#include "auth_menu.h"

class AuthMenuPresenter : public QObject {
    Q_OBJECT
public:
    AuthMenuPresenter(AuthMenu* view, AuthMenuModel* model, QObject* parent = nullptr);

public slots:
    void onLoginRequested(const QString& username, const QString& password);
    void onRegisterRequested(const QString& username,
                             const QString& password,
                             const QString& sipServer,
                             int sipPort);

    void onLoginSuccess();
    void onLoginFailed(QString error);
    void onRegisterSuccess();
    void onRegisterFailed(QString error);

private:
    AuthMenu* view;
    AuthMenuModel* model;
};

#endif // AUTHMENUPRESENTER_H
