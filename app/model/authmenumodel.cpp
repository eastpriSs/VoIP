#include <QDebug>
#include "authmenumodel.h"
#include "validation.h"
#include "lexicalvalidation.h"

AuthMenuModel::AuthMenuModel(QObject *parent) : QObject(parent)
{
    connect(&sip, &sip::ModuleSIP::ErrorRegistration, this, &AuthMenuModel::onRegistrationError);
}

void AuthMenuModel::login(const QString& username, const QString& password)
{
    using namespace Validation;

    std::unique_ptr<IValidation> validator =
        std::make_unique<LexicalValidation>();

    QString error;
    if (!validator->validate(username, password, error))
        emit loginFailed(std::move(error));
    else
        emit loginSuccess();
}

void AuthMenuModel::registerUser(const QString& username,
                                 const QString& password,
                                 const QString& sipServer,
                                 int sipPort)
{
    using namespace sip;
    using namespace Validation;

    std::unique_ptr<IValidation> validator =
        std::make_unique<LexicalValidation>();

    QString error;
    if (!validator->validate(username, password, error)) {
        emit registerFailed(std::move(error));
        return;
    }
    sip.doRegister(username, password, sipServer, sipPort);
}

void AuthMenuModel::onRegistrationError(QString text, int code)
{
    emit registerFailed(text);
}
