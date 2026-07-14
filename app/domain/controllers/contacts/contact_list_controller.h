#ifndef CONTACT_LIST_CONTROLLER_H
#define CONTACT_LIST_CONTROLLER_H

#include <QObject>
#include "contact_fetcher_repository.h"

// todo: здесь будет callController с помощью которого мы будем
// вызывать callNumber с выбранным номером

class ContactListController : public QObject
{
    Q_OBJECT
public:
    explicit ContactListController(QObject *parent = nullptr);
    void proccessSelectedNumber(const QString& number);
    void updateContactList();

private:
    std::shared_ptr<IContactFetcherRepository> repo;
signals:
};

#endif // CONTACT_LIST_CONTROLLER_H
