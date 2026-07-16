#include "setting_repository_impl.h"

SettingRepositoryImpl::SettingRepositoryImpl(QObject *parent)
    : ISettingRepository{parent}
{}

void SettingRepositoryImpl::saveSettings(PBXAuthCredits credits)
{
    QString rawId = credits.clientId();
    QString rawSecret = credits.clientSecret();
    QString rawHttp = credits.server();

    QString encId = crypto.encrypt(rawId);
    QString encSecret = crypto.encrypt(rawSecret);
    QString encHttp = crypto.encrypt(rawHttp);

    saver.savePBXCred(encId, encSecret, encHttp);
}

PBXAuthCredits SettingRepositoryImpl::getSettings()
{
    QString encId, encSecret, encHttp;

    saver.getPBXCred(encId, encSecret, encHttp);

    QString decId = crypto.decrypt(encId);
    QString decSecret = crypto.decrypt(encSecret);
    QString decHttp = crypto.decrypt(encHttp);

    return PBXAuthCredits(decId, decSecret, decHttp);
}
