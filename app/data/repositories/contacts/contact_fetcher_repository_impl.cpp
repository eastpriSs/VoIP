#include "contact_fetcher_repository_impl.h"

ContactFetcherRepositoryImpl::ContactFetcherRepositoryImpl(std::shared_ptr<ContactFetcherPBX> m)
    : module(m)
{
    connect(module.get(), &ContactFetcherPBX::tokenRecieved,
            this, &ContactFetcherRepositoryImpl::onTokenRecieved);
    connect(module.get(), &ContactFetcherPBX::extensionsRecieved,
            this, &ContactFetcherRepositoryImpl::onExtensionsRecieved);
}

void ContactFetcherRepositoryImpl::sendContactListRequest(const QString &clientId, const QString &clientSecret,
                                                          const QString &server)
{
    serverDomain = server;
    if (!accessToken.isActive()) {
        module->fetchToken(clientId, clientSecret, server);
        // emit stateChanged(tokenRequested);
    }
}

void ContactFetcherRepositoryImpl::onTokenRecieved(QString token, int lifeTime)
{
    // emit stateChanged(tokenRecieved);

    accessToken.setHash(std::move(token));
    accessToken.setLifeTime(lifeTime);
    module->fetchExtensions(token, serverDomain);

    // emit stateChanged(extensionsRequested);
}

void ContactFetcherRepositoryImpl::onExtensionsRecieved(QStringList extensions)
{
    // emit stateChanged(extensionsRecieved);
    emit replyRecieved(std::move(extensions));
}

bool ContactFetcherRepositoryImpl::AccessToken::isActive()
{
    return !timeActiveted.isNull() && timeActiveted.secsTo(QTime::currentTime()) < lifeTime;
}

uint ContactFetcherRepositoryImpl::AccessToken::getLifeTime() const
{
    return lifeTime;
}

void ContactFetcherRepositoryImpl::AccessToken::setLifeTime(uint newLifeTime)
{
    lifeTime = newLifeTime;
}

void ContactFetcherRepositoryImpl::AccessToken::setHash(const QString &newHash)
{
    hash = newHash;
}
