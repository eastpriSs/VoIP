#include "setting_menu_presenter.h"

SettingMenuPresenter::SettingMenuPresenter(SettingMenu *view, SettingMenuModel *model, QObject *parent)
    : QObject{parent},
    view(view),
    model(model)
{
    connect(this->view, &SettingMenu::settingsSubmitted,
                this->model, &SettingMenuModel::saveSettings);

    connect(this->model, &SettingMenuModel::settingsLoaded,
                this->view, &SettingMenu::setInitialSettings);

    this->model->getSettings();

}
