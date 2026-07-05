#ifndef AUTH_REPOSITORY_IMPL_H
#define AUTH_REPOSITORY_IMPL_H

#include "module_sip.h"
#include "auth_repository.h"
#include "auth_credits.h"

class AuthRepositoryImpl : public IAuthRepository {

public:
    AuthRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService);
    void registerSipAccount(const AuthCredits& authCredits);

private:
    std::shared_ptr<sip::ModuleSIP> sipService;
};

#endif // AUTH_REPOSITORY_IMPL_H
