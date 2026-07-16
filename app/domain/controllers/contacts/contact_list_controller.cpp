#include "contact_list_controller.h"
#include "pbx_auth_credits.h"
#include <stdexcept>
#include <QDebug>

ContactListController::ContactListController(std::shared_ptr<IContactFetcherRepository> repo,
                                             std::shared_ptr<ICallInitiator> callInitiator,
                                             std::shared_ptr<ISettingRepository> settingRepo,
                                             QObject *parent)
    : QObject{parent}, repo(repo), callInitiator(callInitiator), settingRepo(settingRepo)
{
    connect(repo.get(), &IContactFetcherRepository::replyRecieved, this, &ContactListController::onReplyRecieved);
    connect(repo.get(), &IContactFetcherRepository::stateChanged, this, &ContactListController::onStateChanged);
}

void ContactListController::proccessSelectedNumber(const QString &number)
{
    if (callInitiator) {
        callInitiator->initiateCall(number);
    }
}

void ContactListController::tryUpdateFromSettings()
{
    if (!settingRepo) {
        emit pbxAuthError("Репозиторий настроек не инициализирован");
        return;
    }

    try {
        PBXAuthCredits credits = settingRepo->getSettings();
        if (credits.isEmpty()) {
            emit settingsRequired();
            return;
        }
        qInfo() << "SEND : " << credits.clientId() << ',' << credits.clientSecret() << ',' << credits.server();
        repo->sendContactListRequest(std::move(credits));    
    }
    catch (const std::invalid_argument& e) {
        emit pbxAuthError(QString("Сохраненные настройки некорректны. Может, файл был поврежден. Ошибка: %1").arg(e.what()));
    }
    catch (const std::exception& e) {
        emit pbxAuthError(QString::fromUtf8(e.what()));
    }
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
