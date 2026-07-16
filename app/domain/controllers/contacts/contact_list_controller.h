#ifndef CONTACT_LIST_CONTROLLER_H
#define CONTACT_LIST_CONTROLLER_H

#include <QObject>
#include <memory>
#include "contact_fetcher_repository.h"
#include "call_initiator.h"
#include "setting_repository.h"
#include "request_states.h"

class ContactListController : public QObject
{
    Q_OBJECT
public:
    explicit ContactListController(std::shared_ptr<IContactFetcherRepository> repo,
                                   std::shared_ptr<ICallInitiator> callInitiator = nullptr,                                    std::shared_ptr<ISettingRepository> settingRepo = nullptr,
                                   QObject *parent = nullptr);

    void proccessSelectedNumber(const QString& number);
    void updateContactList(const QString &clientId, const QString &clientSecret, const QString &server);
    void tryUpdateFromSettings();

private:
    std::shared_ptr<IContactFetcherRepository> repo;
    std::shared_ptr<ICallInitiator> callInitiator;
    std::shared_ptr<ISettingRepository> settingRepo;

private slots:
    void onReplyRecieved(QStringList extensions);
    void onStateChanged(RequestState state);

signals:
    void pbxAuthError(const QString &message);
    void extensionsRecieved(QStringList extensions);
    void requestStateChanged(QString state);
    void settingsRequired();
};

#endif // CONTACT_LIST_CONTROLLER_H
