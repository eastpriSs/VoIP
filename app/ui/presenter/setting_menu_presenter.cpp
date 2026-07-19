#include "setting_menu_presenter.h"

SettingMenuPresenter::SettingMenuPresenter(std::shared_ptr<SettingMenu> v,
                                           std::shared_ptr<SettingMenuModel> m,
                                           QObject *parent)
    : QObject{parent}, view(v), model(m)
{
    connect(view.get(), &SettingMenu::submitRequested, model.get(), &SettingMenuModel::requestSaveSettings);
    connect(model.get(), &SettingMenuModel::settingsSaved, view.get(), &SettingMenu::closeOnSuccess);
    connect(model.get(), &SettingMenuModel::saveError, view.get(), &SettingMenu::showValidationError);
    connect(model.get(), &SettingMenuModel::settingsLoaded, view.get(), &SettingMenu::setInitialSettings);

    model->getSettings();
}
