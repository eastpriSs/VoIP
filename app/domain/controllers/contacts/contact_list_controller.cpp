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
        repo->sendContactListRequest(std::move(credits));
    }
    catch (const std::invalid_argument &e) {
        emit pbxAuthError(QString::fromUtf8(e.what()));
    }
}

void ContactListController::onReplyRecieved(QStringList extensions)
{
    emit extensionsRecieved(std::move(extensions));
}

void ContactListController::onStateChanged(RequestState state)
{
    QString stateTxt;
    switch (state)
    {
    case RequestState::tokenRequested:
        stateTxt = "Запрос на предоставление токена отправлен...";
        break;

    case RequestState::tokenRecieved:
        stateTxt = "Токен получен.";
        break;

    case RequestState::extensionsRequested:
        stateTxt = "Запрос контактов...";
        break;

    case RequestState::extensionsRecieved:
        stateTxt = "Успех.Контакты получены.";
        break;

    default:
        break;
    }
    emit requestStateChanged(std::move(stateTxt));
}
