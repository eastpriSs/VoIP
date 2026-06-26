#include "databasevalidation.h"
#include <QDebug>

using namespace Validation;

DataBaseValidation::DataBaseValidation(std::unique_ptr<IValidation> n)
    : next(std::move(n)) {
}

bool DataBaseValidation::validate(const QString& username, const QString& password, QString& error) {

    if (next) {
        if (!next->validate(username, password, error)) {
            return false;
        }
    }

    // Проверка наличия пользователя в БД
    qDebug() << "DataBaseValidation: поиск пользователя" << username;
    return true;
}
