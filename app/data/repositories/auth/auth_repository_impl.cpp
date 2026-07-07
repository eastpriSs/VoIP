#include "auth_repository_impl.h"


AuthRepositoryImpl::AuthRepositoryImpl(std::shared_ptr<sip::ModuleSIP> sipService)
    : sipService(sipService)
{
    QObject::connect(sipService.get(), &sip::ModuleSIP::registrationStateChanged, this);
}

void AuthRepositoryImpl::registerSipAccount(const AuthCredits &authCredits)
{
    sipService->doRegister(authCredits);
}

void AuthRepositoryImpl::onRegStateChanged(int code, QString what)
{
    /*  */
    constexpr ushort OK = 200;
    if (code == OK)
        emit successRegistration();

    // Здесь будем кидать собственные исключения для связи с domain слоем

    // if (statusCode == 401 || statusCode == 403) {
    //     throw InvalidCredentialsException();
    // }
    // else if (statusCode >= 500 && statusCode < 600) {
    //     throw ServerUnavailableException(reason.toStdString());
    // }
    // else if (statusCode == 408) {
    //     throw AuthException("Превышено время ожидания ответа сервера");
    // }
    // else {
    //     throw AuthException("Неизвестная ошибка регистрации: " + reason.toStdString());
    // }
}
