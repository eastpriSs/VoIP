#include <stdexcept>
#include "auth_repository_impl.h"


AuthRepositoryImpl::AuthRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService)
    : sipService(sipService)
{
    qRegisterMetaType<AuthError>("AuthError");
    QObject::connect(sipService.get(), &sip::ModuleSIP::registrationStateChanged,
                     this, &AuthRepositoryImpl::onRegStateChanged);
}

void AuthRepositoryImpl::registerSipAccount(const AuthCredits &authCredits)
{
    int code = sipService->doRegister(authCredits);
    if (code != sip::OK)
        throw std::runtime_error(sipService->getTextError(code).toStdString());
}

void AuthRepositoryImpl::onRegStateChanged(int code, QString what)
{
    if (code == sip::OK) {
        emit registrationSuccess();
        return;
    }

    AuthError error;
    if (code == 401 || code == 403) {
        error.type = AuthErrorType::InvalidCredentials;
        error.message = "Неверные данные для регистрации.";
    } else if (code >= 500 && code < 600) {
        error.type = AuthErrorType::ServerUnavailable;
        error.message = "Сервер недоступен.";
    } else if (code == 408) {
        error.type = AuthErrorType::Timeout;
        error.message = "Превышено время ожидания ответа сервера.";
    } else {
        error.type = AuthErrorType::Unknown;
        error.message = "Неизвестная ошибка регистрации. Код: " + QString::number(code);
    }

    emit registrationFailed(error);
}
