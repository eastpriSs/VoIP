#include "setting_menu_presenter.h"

SettingMenuPresenter::SettingMenuPresenter(std::shared_ptr<SettingMenu> view,
                                           std::shared_ptr<SettingMenuModel> model, QObject *parent)
    : QObject{parent},
    view(view),
    model(model)
{
    connect(this->view.get(), &SettingMenu::settingsSubmitted,
                this->model.get(), &SettingMenuModel::saveSettings);

    connect(this->model.get(), &SettingMenuModel::settingsLoaded,
                this->view.get(), &SettingMenu::setInitialSettings);

    this->model->getSettings();
}
