#ifndef SETTING_CONTROLLER_H
#define SETTING_CONTROLLER_H

#include <QObject>
#include <memory>
#include <QString>
#include "setting_repository.h"

class SettingController : public QObject
{
    Q_OBJECT
public:
    explicit SettingController(std::shared_ptr<ISettingRepository> repo, QObject *parent = nullptr);
    void saveSettings(const QString &clientId, const QString &clientSecret, const QString &httpServer);
    void getSettings(QString &clientId, QString &clientSecret, QString &httpServer);

private:
    std::shared_ptr<ISettingRepository> repo;

signals:
};

#endif // SETTING_CONTROLLER_H
