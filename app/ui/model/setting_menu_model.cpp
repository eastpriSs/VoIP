#include "setting_menu_model.h"
#include <QDebug>

SettingMenuModel::SettingMenuModel(std::shared_ptr<SettingController> controller, QObject *parent)
    : QObject{parent}, controller(controller)
{
    connect(controller.get(), &SettingController::settingsSaved, this, &SettingMenuModel::settingsSaved);
    connect(controller.get(), &SettingController::saveError, this, &SettingMenuModel::saveError);
}

void SettingMenuModel::requestSaveSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    controller->saveSettings(clientId, clientSecret, httpServer);
}

void SettingMenuModel::getSettings()
{
    controller->getSettings(clientId, clientSecret, server);
    qInfo() << "GET Settings:" << clientId << ',' << clientSecret << ',' << server;
    emit settingsLoaded(clientId, clientSecret, server);
}
