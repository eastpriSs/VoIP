#ifndef CONTACT_LIST_CONTROLLER_H
#define CONTACT_LIST_CONTROLLER_H

#include <QObject>
#include <memory>
#include "contact_fetcher_repository.h"

class ContactListController : public QObject
{
    Q_OBJECT
public:
    explicit ContactListController(std::shared_ptr<IContactFetcherRepository> repo, QObject *parent = nullptr);
    void proccessSelectedNumber(const QString& number);
    void updateContactList(const QString &clientId, const QString &clientSecret, const QString &server);

private:
    std::shared_ptr<IContactFetcherRepository> repo;

private slots:
    void onReplyRecieved(QStringList extensions);

signals:
    void pbxAuthError(const QString &message);
    void extensionsRecieved(QStringList extensions);
};

#endif // CONTACT_LIST_CONTROLLER_H
