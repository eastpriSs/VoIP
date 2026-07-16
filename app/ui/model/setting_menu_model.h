#ifndef SETTING_MENU_MODEL_H
#define SETTING_MENU_MODEL_H

#include <QObject>
#include <QString>
#include "setting_controller.h"

class SettingMenuModel : public QObject
{
    Q_OBJECT
public:
    explicit SettingMenuModel(std::shared_ptr<SettingController> controller, QObject *parent = nullptr);

public slots:
    void saveSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer);
    void getSettings();

signals:
    void settingsSaved();
    void settingsLoaded(const QString &clientId, const QString &clientSecret, const QString &httpServer);

private:
    std::shared_ptr<SettingController> controller;
    QString clientId;
    QString clientSecret;
    QString server;
};

#endif // SETTING_MENU_MODEL_H
