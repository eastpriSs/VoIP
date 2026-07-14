#include "contact_list_controller.h"
#include "pbx_auth_credits.h"
#include <stdexcept>

ContactListController::ContactListController(std::shared_ptr<IContactFetcherRepository> repo, QObject *parent)
    : QObject{parent}, repo(repo)
{
    connect(repo.get(), &IContactFetcherRepository::replyRecieved, this, &ContactListController::onReplyRecieved);
}

void ContactListController::proccessSelectedNumber(const QString &number)
{
    // осуществляется звонок
}

void ContactListController::updateContactList(const QString &clientId, const QString &clientSecret, const QString &server)
{
    try {
        PBXAuthCredits credits(clientId, clientSecret, server);
        repo->sendContactListRequest(credits.clientId(), credits.clientSecret(), credits.server());
    }
    catch (const std::invalid_argument &e) {
        emit pbxAuthError(QString::fromUtf8(e.what()));
    }
}

void ContactListController::onReplyRecieved(QStringList extensions)
{
    emit extensionsRecieved(std::move(extensions));
}
