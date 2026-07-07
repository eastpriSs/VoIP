#include "lexicalvalidation.h"
#include <QRegularExpression>

using namespace validation;

LexicalValidation::LexicalValidation(std::unique_ptr<IValidation> n)
    : next(std::move(n)) {}

bool LexicalValidation::validate(const QString& username, const QString& password, QString& error)
{
    constexpr unsigned MIN_USERNAME_LEN = 3;
    constexpr unsigned MIN_PASSWORD_LEN = 6;

    if (username.length() < MIN_USERNAME_LEN) {
        error = QString("Логин должен содержать минимум %1 символа").arg(MIN_USERNAME_LEN);
        return false;
    }
    if (password.length() < MIN_PASSWORD_LEN) {
        error = QString("Пароль должен содержать минимум %1 символов").arg(MIN_PASSWORD_LEN);
        return false;
    }

    const QRegularExpression internalNumberRegex("^[A-Za-z0-9_]+$");          // aka 101, 102, ...
    const QRegularExpression virtualNumberRegex("^\\+?[1-9]\\d{9,14}$");      // aka +74950000000, 74950000000, 88005553535, ...
    const QRegularExpression usernameRegex("^[a-zA-Z0-9_\\.\\*\\-@]{3,64}$"); // aka user_1234, 100567*321, ivan.ivanov, user@domain.com
    const QRegularExpression SipUriRegex("^[a-zA-Z0-9_\\-\\.\\+]+@[a-zA-Z0-9\\-]+(\\.[a-zA-Z0-9\\-]+)+(\\:[0-9]{1,5})?(;\\S+)?$");

    if (!internalNumberRegex.match(username).hasMatch() &&
        !virtualNumberRegex.match(username).hasMatch()  &&
        !usernameRegex.match(username).hasMatch()  &&
        !SipUriRegex.match(username).hasMatch()) {
        error = "Логин должен соотвествовать одному из форматов: внутренний/виртуальный номер, логин, SIP uri.";
        return false;
    }

    if (next) {
        return next->validate(username, password, error);
    }

    return true;
}
