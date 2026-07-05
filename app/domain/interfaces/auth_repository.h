#ifndef AUTH_REPOSITORY_H
#define AUTH_REPOSITORY_H

#include "auth_credits.h"

class IAuthRepository {
public:
    virtual ~IAuthRepository() = default;
    virtual void registerSipAccount(const AuthCredits& creds) = 0;
    //virtual void loginSipAccount(const AuthCredits& creds) = 0;
};

#endif // AUTH_REPOSITORY_H
