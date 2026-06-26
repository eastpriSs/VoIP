#ifndef AUTHMENUMODEL_H
#define AUTHMENUMODEL_H

#include <QObject>

class AuthMenuModel : public QObject {
    Q_OBJECT
public:
    explicit AuthMenuModel(QObject *parent = nullptr);

    void login(const QString& username, const QString& password);
    void registerUser(const QString& username, const QString& password);

signals:
    void loginSuccess();
    void loginFailed(const QString& error);
    void registerSuccess();
    void registerFailed(const QString& error);

private:
    bool validateCredentials(const QString& username, const QString& password);
};

#endif // AUTHMENUMODEL_H
