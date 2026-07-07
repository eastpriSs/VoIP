#include <stdexcept>
#include "auth_credits.h"
#include "validation.h"
#include "lexicalvalidation.h"

QString AuthCredits::getLogin() const { return login; }
QString AuthCredits::getPassword() const { return password; }
QString AuthCredits::getIDUri() const { return QString("sip:%1@%2").arg(login, sipServer); }
QString AuthCredits::getRegistrarUri() const { return QString("sip:%1@%2:%3").arg(login, sipServer, QString::number(port)); }
int AuthCredits::getPort() const { return port; }

AuthCredits::AuthCredits(QString login, QString password, QString sipServer, int port)
    : login(std::move(login)), password(std::move(password)), sipServer(std::move(sipServer)), port(port) {
    validate();
}

void AuthCredits::validate() const
{
    using namespace validation;

    std::unique_ptr<IValidation> validator = std::make_unique<LexicalValidation>();
    QString error;
    if (!validator->validate(login, password, error))
        throw std::invalid_argument(error.toStdString());
}
