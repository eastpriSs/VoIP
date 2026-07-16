// setting_controller.cpp
#include "setting_controller.h"
#include "pbx_auth_credits.h"
#include <stdexcept>

SettingController::SettingController(std::shared_ptr<ISettingRepository> repo, QObject *parent)
    : QObject{parent}, repo(repo)
{}

void SettingController::saveSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    try {
        PBXAuthCredits credits(clientId, clientSecret, httpServer);
        repo->saveSettings(credits);
        emit settingsSaved();
    }
    catch (const std::invalid_argument& e) {
        emit saveError(QString::fromUtf8(e.what()));
    }
    catch (const std::exception& e) {
        emit saveError(QString::fromUtf8(e.what()));
    }
}

void SettingController::getSettings(QString &clientId, QString &clientSecret, QString &httpServer)
{
    try {
        PBXAuthCredits cred = repo->getSettings();
        clientId = cred.clientId();
        clientSecret = cred.clientSecret();
        httpServer = cred.server();
    } catch (const std::invalid_argument& err) {
        clientId = "";
        clientSecret = "";
        httpServer = "";
    }
}
