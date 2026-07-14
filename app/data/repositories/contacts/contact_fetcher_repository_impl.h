#ifndef CONTACT_FETCHER_REPOSITORY_IMPL_H
#define CONTACT_FETCHER_REPOSITORY_IMPL_H

#include <QObject>
#include "contact_fetcher_repository.h"
#include "contact_fetcher_pbx.h"

class ContactFetcherRepositoryImpl : public IContactFetcherRepository
{
    Q_OBJECT
public:
    explicit ContactFetcherRepositoryImpl();
    void sendContactListRequest() override;
private:
    ContactFetcherPBX* module;
signals:
};

#endif // CONTACT_FETCHER_REPOSITORY_IMPL_H
