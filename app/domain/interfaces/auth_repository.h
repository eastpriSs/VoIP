#ifndef AUTH_REPOSITORY_H
#define AUTH_REPOSITORY_H

#include <QObject>
#include "auth_credits.h"
#include "auth_error.h"

class IAuthRepository : public QObject {
    Q_OBJECT
public:
    explicit IAuthRepository(QObject* parent = nullptr) : QObject(parent) {}
    virtual void registerSipAccount(const AuthCredits& authCredits) = 0;

signals:
    void registrationSuccess();
    void registrationFailed(const AuthError& error);
};

#endif // AUTH_REPOSITORY_H
