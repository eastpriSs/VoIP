#ifndef AUTH_REPOSITORY_IMPL_H
#define AUTH_REPOSITORY_IMPL_H

#include <QObject>

#include "module_sip.h"
#include "auth_repository.h"
#include "auth_credits.h"

class AuthRepositoryImpl : public IAuthRepository {
    Q_OBJECT
public:
    AuthRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService);
    void registerSipAccount(const AuthCredits& authCredits);

signals:
    void successRegistration(/* userName */);
    void faildRegistration(QString what);

private slots:
    void onRegStateChanged(int code, QString what = "");

private:
    std::shared_ptr<sip::ModuleSIP> sipService;
};

#endif // AUTH_REPOSITORY_IMPL_H
