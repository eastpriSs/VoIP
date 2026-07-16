#ifndef SETTING_REPOSITORY_IMPL_H
#define SETTING_REPOSITORY_IMPL_H

#include "setting_repository.h"
#include "crypto.h"
#include "setting_saver.h"

class SettingRepositoryImpl : public ISettingRepository
{
    Q_OBJECT
public:
    explicit SettingRepositoryImpl(QObject *parent = nullptr);

    void saveSettings(PBXAuthCredits credits) override;
    PBXAuthCredits getSettings() override;

private:
    Crypto crypto;
    SettingSaver saver;
};

#endif // SETTING_REPOSITORY_IMPL_H
