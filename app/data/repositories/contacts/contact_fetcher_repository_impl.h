#ifndef CONTACT_FETCHER_REPOSITORY_IMPL_H
#define CONTACT_FETCHER_REPOSITORY_IMPL_H

#include <QObject>
#include <QTime>
#include <QString>
#include "contact_fetcher_repository.h"
#include "contact_fetcher_pbx.h"


class ContactFetcherRepositoryImpl : public IContactFetcherRepository
{
    Q_OBJECT

    class AccessToken
    {
    public:
        bool isActive();
        uint getLifeTime() const;
        void setLifeTime(uint newLifeTime);
        void setHash(const QString &newHash);

    private:
        QString hash;
        QTime   timeActiveted;
        uint    lifeTime;

    } accessToken;

public:
    explicit ContactFetcherRepositoryImpl(std::shared_ptr<ContactFetcherPBX> m);
    void sendContactListRequest(const QString &clientId, const QString &clientSecret, const QString &server) override;

private slots:
    void onTokenRecieved(QString token, int lifeTime);
    void onExtensionsRecieved(QStringList extensions);

private:
    std::shared_ptr<ContactFetcherPBX> module;
    QString serverDomain;

signals:
};

#endif // CONTACT_FETCHER_REPOSITORY_IMPL_H
