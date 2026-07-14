#ifndef CONTACT_FETCHER_REPOSITORY_H
#define CONTACT_FETCHER_REPOSITORY_H

#include <QObject>

class IContactFetcherRepository : public QObject
{
    Q_OBJECT
public:
    explicit IContactFetcherRepository(QObject *parent = nullptr) : QObject(parent) {};
    virtual void sendContactListRequest() = 0;
signals:
    void replyRecieved();
};

#endif // CONTACT_FETCHER_REPOSITORY_H
