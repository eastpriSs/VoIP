#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include <QObject>
#include <memory>
#include "auth_repository.h"
#include "auth_error.h"

class AuthController : public QObject {
    Q_OBJECT
public:
    AuthController(std::shared_ptr<IAuthRepository> repo);
    void registerUser(const QString& username,
                      const QString& password,
                      const QString& sipServer,
                      int port);

signals:
    void registrationSucceeded();
    void registrationFailed(const QString& error);
    void validationDataCompleted(bool success = true);
    void registrationRequestCreated();

private slots:
    void onRepoSuccess();
    void onRepoFailed(const AuthError& error);

private:
    std::shared_ptr<IAuthRepository> repository;
};

#endif // AUTH_CONTROLLER_H
