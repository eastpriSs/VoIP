#include "contact_fetcher_repository_impl.h"
#include "request_states.h"

ContactFetcherRepositoryImpl::ContactFetcherRepositoryImpl(std::shared_ptr<ContactFetcherPBX> m)
    : module(m)
{
    connect(module.get(), &ContactFetcherPBX::tokenRecieved,
            this, &ContactFetcherRepositoryImpl::onTokenRecieved);
    connect(module.get(), &ContactFetcherPBX::extensionsRecieved,
            this, &ContactFetcherRepositoryImpl::onExtensionsRecieved);
}

void ContactFetcherRepositoryImpl::sendContactListRequest(PBXAuthCredits pbxCred)
{
    serverDomain = pbxCred.server();
    if (!accessToken.isActive()) {
        module->fetchToken(pbxCred.clientId(), pbxCred.clientSecret(), pbxCred.server());
        emit stateChanged(RequestState::tokenRequested);
    }
}
void ContactFetcherRepositoryImpl::onTokenRecieved(QString token, int lifeTime)
{
    emit stateChanged(RequestState::tokenRecieved);

    accessToken.setHash(std::move(token));
    accessToken.setLifeTime(lifeTime);
    accessToken.setTimeActivated(QTime::currentTime());
    module->fetchExtensions(token, serverDomain);

    emit stateChanged(RequestState::extensionsRequested);
}

void ContactFetcherRepositoryImpl::onExtensionsRecieved(QStringList extensions)
{
    emit stateChanged(RequestState::extensionsRecieved);
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

void ContactFetcherRepositoryImpl::AccessToken::setTimeActivated(QTime time)
{
    timeActiveted = time;
}
