#include "auth_controller.h"
#include "auth_credits.h"
#include <stdexcept>

AuthController::AuthController(std::shared_ptr<IAuthRepository> repo)
    : repository(repo)
{
    connect(repository.get(), &IAuthRepository::registrationSuccess,
            this, &AuthController::onRepoSuccess);

    connect(repository.get(), &IAuthRepository::registrationFailed,
            this, &AuthController::onRepoFailed);
}

void AuthController::registerUser(const QString &username, const QString &password,
                                  const QString &sipServer, int port)
{
    try {
        AuthCredits authCredits(username, password, sipServer, port);
        emit validationDataCompleted();
        repository->registerSipAccount(authCredits);
        emit registrationRequestCreated();
    }
    catch (const std::invalid_argument& e) {
        emit validationDataCompleted(false);
        emit registrationFailed(QString::fromUtf8(e.what()));
    }
    catch (const std::runtime_error& e) {
        emit registrationFailed(QString("Произошла непредвиденная ошибка при запуске регистрации. Ошибка: %1").arg(e.what()));
    }
}

void AuthController::onRepoSuccess()
{
    emit registrationSucceeded();
}

void AuthController::onRepoFailed(const AuthError& error)
{
    // Здесь Domain слой уже получил идентифицированную ошибку.
    // Если нужна будет разная логика, можно сделать switch(error.type) или
    /* Пример:
    if (error.type == AuthErrorType::InvalidCredentials) {
        // Какая-то специфичная логика, например, сбросить счетчик попыток
    }
    */

    emit registrationFailed(error.message);
}
