#include "contact_list_controller.h"
#include "pbx_auth_credits.h"
#include <stdexcept>

ContactListController::ContactListController(std::shared_ptr<IContactFetcherRepository> repo,
                                             std::shared_ptr<CallController> callController,
                                             QObject *parent)
    : QObject{parent}, repo(repo), callController(callController)
{
    connect(repo.get(), &IContactFetcherRepository::replyRecieved, this, &ContactListController::onReplyRecieved);
    connect(repo.get(), &IContactFetcherRepository::stateChanged, this, &ContactListController::onStateChanged);

}

void ContactListController::proccessSelectedNumber(const QString &number)
{
    if (callController)
        callController->callNumber(number);
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

void ContactListController::onStateChanged()
{
    /*
        switch(...) { ... }
    */
    emit requestStateChanged();
}
