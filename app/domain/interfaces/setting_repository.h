#ifndef SETTING_REPOSITORY_H
#define SETTING_REPOSITORY_H

#include <QObject>
#include "pbx_auth_credits.h"

class ISettingRepository : public QObject
{
    Q_OBJECT
public:
    explicit ISettingRepository(QObject *parent = nullptr);
    virtual ~ISettingRepository() = default;

    virtual void saveSettings(PBXAuthCredits credits) = 0;
    [[nodiscard]] virtual PBXAuthCredits getSettings() = 0;

signals:
};

#endif // SETTING_REPOSITORY_H
