#include "auth_controller.h"
#include "auth_credits.h"

AuthController::AuthController(std::shared_ptr<IAuthRepository> repo)
    : repository(repo)
{
}

void AuthController::registerUser(const QString &username, const QString &password, const QString &sipServer, int port)
{
    AuthCredits authCredits(username, password, sipServer, port);
    try {
        repository->registerSipAccount(authCredits);
    }  catch (std::invalid_argument err) {

    }
    // Здесь будем отлавливать исключения с уровня data и пробрасывать дальше

    // } catch (const std::invalid_argument& e) {
    //     emit registrationFailed(QString::fromUtf8(e.what()));
    // }
    // catch (const InvalidCredentialsException& e) {
    //     emit registrationFailed(QString::fromUtf8(e.what()));
    // }
    // catch (const AuthException& e) {
    //     emit registrationFailed(QString::fromUtf8(e.what()));
    // }
    // catch (...) {
    //     emit registrationFailed("Произошла непредвиденная ошибка");
    // }
}
