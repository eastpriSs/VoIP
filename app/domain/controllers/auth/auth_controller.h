#ifndef AUTH_CONTROLLER_H
#define AUTH_CONTROLLER_H

#include <QObject>
#include "auth_repository.h"

class AuthController : public QObject {
    Q_OBJECT
public:
    AuthController(std::shared_ptr<IAuthRepository> repo);

    void registerUser(const QString& username,
                      const QString& password,
                      const QString& sipServer,
                      int port);

// signals:
//     void registrationStarted();
//     void registrationSucceeded(const QString& userId);
//     void registrationFailed(const QString& error);

// private slots:
//     void onSipStateChanged(int statusCode, const QString& reason);

private:
    std::shared_ptr<IAuthRepository> repository;
};

#endif // AUTH_CONTROLLER_H
