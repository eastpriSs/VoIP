#include "main_window.h"
#include <QApplication>

#include "data/services/SIP/module_sip.h"
#include "auth_repository_impl.h"
#include "domain/controllers/auth/auth_controller.h"
#include "auth_menu_presenter.h"
#include "auth_menu.h"
#include "auth_menu_model.h"


#include "contact_list_model.h"
#include "contact_list_presenter.h"
#include "contact_list.h"
#include "contact_list_controller.h"
#include "contact_fetcher_pbx.h"
#include "contact_fetcher_repository_impl.h"

#include "call_menu.h"
#include "call_menu_presenter.h"
#include "call_menu_model.h"
#include "call_controller.h"
#include "call_repository_impl.h"

#include "setting_menu.h"
#include "setting_menu_presenter.h"
#include "setting_menu_model.h"
#include "setting_controller.h"
#include "setting_repository_impl.h"


int main(int argc, char *argv[])
{
    using std::shared_ptr;
    using std::make_shared;
    QApplication a(argc, argv);

    shared_ptr<sip::ModuleSIP> sipService = make_shared<sip::ModuleSIP>();

    AuthMenu* authMenu = new AuthMenu();
    shared_ptr<AuthRepositoryImpl> authRepoImpl = make_shared<AuthRepositoryImpl>(sipService);
    shared_ptr<AuthController> authController = make_shared<AuthController>(authRepoImpl);
    AuthMenuModel* authMenuModel = new AuthMenuModel(authController);
    shared_ptr<AuthMenuPresenter> authMenuPresenter = make_shared<AuthMenuPresenter>(authMenu, authMenuModel);

    CallMenu* callMenu = new CallMenu();
    shared_ptr<CallRepositoryImpl> callRepoImpl = make_shared<CallRepositoryImpl>(sipService);
    shared_ptr<CallController> callController = make_shared<CallController>(callRepoImpl);
    CallMenuModel* callMenuModel = new CallMenuModel(callController);
    std::shared_ptr<CallMenuPresenter> callMenuPresenter = make_shared<CallMenuPresenter>(callMenu, callMenuModel);

    ContactList* contactMenu = new ContactList();
    shared_ptr<ContactFetcherPBX> contactService = make_shared<ContactFetcherPBX>();
    shared_ptr<ContactFetcherRepositoryImpl> contactRepoImpl = make_shared<ContactFetcherRepositoryImpl>(contactService);

    shared_ptr<SettingRepositoryImpl> settingRepoImpl = make_shared<SettingRepositoryImpl>();
    shared_ptr<ContactListController> contactController = make_shared<ContactListController>(
        contactRepoImpl,
        callController,
        settingRepoImpl
        );

    shared_ptr<ContactListModel> contactMenuModel = make_shared<ContactListModel>(contactController);
    shared_ptr<ContactListPresenter> contactMenuPresenter = make_shared<ContactListPresenter>(contactMenu, contactMenuModel);
    shared_ptr<SettingMenu> settingMenu = make_shared<SettingMenu>();
    shared_ptr<SettingController> settingController = make_shared<SettingController>(settingRepoImpl);
    shared_ptr<SettingMenuModel> settingMenuModel = make_shared<SettingMenuModel>(settingController);
    shared_ptr<SettingMenuPresenter> settingMenuPresenter = make_shared<SettingMenuPresenter>(settingMenu, settingMenuModel);

    contactMenu->setSettingMenu(settingMenu);

    MainWindow w(authMenu, callMenu, contactMenu, settingMenu.get());
    w.show();

    return a.exec();
}
