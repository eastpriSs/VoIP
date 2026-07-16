#ifndef SETTING_MENU_PRESENTER_H
#define SETTING_MENU_PRESENTER_H

#include <QObject>
#include "setting_menu.h"
#include "setting_menu_model.h"

class SettingMenuPresenter : public QObject
{
    Q_OBJECT
public:
    explicit SettingMenuPresenter(std::shared_ptr<SettingMenu> view, std::shared_ptr<SettingMenuModel> model, QObject *parent = nullptr);

private:
    std::shared_ptr<SettingMenu> view;
    std::shared_ptr<SettingMenuModel> model;
};

#endif // SETTING_MENU_PRESENTER_H
