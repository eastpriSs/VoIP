#ifndef SETTING_MENU_PRESENTER_H
#define SETTING_MENU_PRESENTER_H

#include <QObject>
#include "setting_menu.h"
#include "setting_menu_model.h"

class SettingMenuPresenter : public QObject
{
    Q_OBJECT
public:
    explicit SettingMenuPresenter(SettingMenu *view, SettingMenuModel *model, QObject *parent = nullptr);

private:
    SettingMenu *view;
    SettingMenuModel *model;
};

#endif // SETTING_MENU_PRESENTER_H
