#include "auth_repository_impl.h"


AuthRepositoryImpl::AuthRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService)
    : sipService(sipService)
{
}

void AuthRepositoryImpl::registerSipAccount(const AuthCredits &authCredits)
{
    sipService->doRegister(authCredits);
}
