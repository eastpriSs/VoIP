#ifndef AUTHMENUMODEL_H
#define AUTHMENUMODEL_H

#include <QObject>

#include "auth_controller.h"

class AuthMenuModel : public QObject {
    Q_OBJECT
public:
    explicit AuthMenuModel(std::shared_ptr<AuthController> controller, QObject *parent = nullptr);

    void login(const QString& username, const QString& password);
    void registerUser(const QString& username,
                      const QString& password,
                      const QString& sipServer,
                      int sipPort);

private slots:
    void onRegistrationError(QString text, int code);

signals:
    void loginSuccess();
    void loginFailed(QString error);
    void registerSuccess();
    void registerFailed(QString error);

private:
    std::shared_ptr<AuthController> authController;
};

#endif // AUTHMENUMODEL_H
