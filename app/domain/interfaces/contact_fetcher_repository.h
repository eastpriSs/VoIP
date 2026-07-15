#ifndef CONTACT_FETCHER_REPOSITORY_H
#define CONTACT_FETCHER_REPOSITORY_H

#include <QObject>
#include "request_states.h"
#include "pbx_auth_credits.h"

class IContactFetcherRepository : public QObject
{
    Q_OBJECT
public:
    explicit IContactFetcherRepository(QObject *parent = nullptr) : QObject(parent) {};
    virtual void sendContactListRequest(PBXAuthCredits pbxCred) = 0;
signals:
    void replyRecieved(QStringList extensions);
    void stateChanged(RequestState state);
};

#endif // CONTACT_FETCHER_REPOSITORY_H
