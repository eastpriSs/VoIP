#include <QDebug>
#include "setting_menu_model.h"

SettingMenuModel::SettingMenuModel(std::shared_ptr<SettingController> controller, QObject *parent)
    : QObject{parent}, controller(controller)
{}

void SettingMenuModel::saveSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    controller->saveSettings(clientId, clientSecret, httpServer);
    emit settingsSaved();
}

void SettingMenuModel::getSettings()
{
    controller->getSettings(clientId, clientSecret, server);
    qInfo() << "GET Settings:" << clientId << ',' << clientSecret << ',' << server;
    emit settingsLoaded(clientId, clientSecret, server);
}
