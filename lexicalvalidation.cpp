#include "lexicalvalidation.h"
#include <QRegularExpression>

using namespace Validation;

LexicalValidation::LexicalValidation(std::unique_ptr<IValidation> n)
    : next(std::move(n)) {}

bool LexicalValidation::validate(const QString& username, const QString& password, QString& error)
{
    if (username.isEmpty()) {
        error = "Логин не может быть пустым";
        return false;
    }
    if (password.isEmpty()) {
        error = "Пароль не может быть пустым";
        return false;
    }

    if (username.length() < 3) {
        error = "Логин должен содержать минимум 3 символа";
        return false;
    }
    if (password.length() < 6) {
        error = "Пароль должен содержать минимум 6 символов";
        return false;
    }

    QRegularExpression loginRegex("^[A-Za-z0-9_]+$");
    if (!loginRegex.match(username).hasMatch()) {
        error = "Логин может содержать только латинские буквы, цифры и подчёркивание";
        return false;
    }

    if (next) {
        return next->validate(username, password, error);
    }

    return true;
}
