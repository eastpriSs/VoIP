#include "lexicalvalidation.h"
#include "regex_patterns.h"

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

    if (!RegexPatterns::internalNumber.match(username).hasMatch() &&
        !RegexPatterns::virtualNumber.match(username).hasMatch() &&
        !RegexPatterns::username.match(username).hasMatch() &&
        !RegexPatterns::sipUri.match(username).hasMatch()) {

        error = "Логин должен соответствовать одному из форматов: внутренний/виртуальный номер, логин, SIP URI.";
        return false;
    }

    if (next) {
        return next->validate(username, password, error);
    }
    return true;
}
