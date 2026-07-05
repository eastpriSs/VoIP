#include "auth_controller.h"
#include "auth_credits.h"

AuthController::AuthController(std::shared_ptr<IAuthRepository> repo)
    : repository(repo)
{
}

void AuthController::registerUser(const QString &username, const QString &password, const QString &sipServer, int port)
{
    AuthCredits authCredits(username, password, sipServer, port);
    repository->registerSipAccount(authCredits);
}
