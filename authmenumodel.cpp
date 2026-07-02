#include <QDebug>
#include "authmenumodel.h"
#include "validation.h"
#include "lexicalvalidation.h"
#include "databasevalidation.h"
#include "modulesip.h"

AuthMenuModel::AuthMenuModel(QObject *parent) : QObject(parent) {}

void AuthMenuModel::login(const QString& username, const QString& password) {
    using namespace Validation;

    std::unique_ptr<IValidation> validator =
        std::make_unique<LexicalValidation>(
            std::make_unique<DataBaseValidation>(nullptr)
            );

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

    ModuleSIP sip;
    QString tmpUser(username);
    QString tmpPass(password);
    QString tmpServer(sipServer);

    sip.doRegister(tmpUser.toUtf8().data(), tmpPass.toUtf8().data(), tmpServer.toUtf8().data(), sipPort);
}
