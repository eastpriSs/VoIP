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

int main(int argc, char *argv[])
{
    using std::shared_ptr;
    using std::make_shared;

    QApplication a(argc, argv);
    AuthMenu* authMenu = new AuthMenu();
    shared_ptr<sip::ModuleSIP> sipService = make_shared<sip::ModuleSIP>();
    shared_ptr<AuthRepositoryImpl> authRepoImpl = make_shared<AuthRepositoryImpl>(sipService);
    shared_ptr<AuthController> authController = make_shared<AuthController>(authRepoImpl);
    AuthMenuModel* authMenuModel = new AuthMenuModel(authController);
    shared_ptr<AuthMenuPresenter> authMenuPresenter = make_shared<AuthMenuPresenter>(authMenu, authMenuModel);

    ContactList* contactMenu = new ContactList();
    shared_ptr<ContactFetcherPBX> contactService = make_shared<ContactFetcherPBX>();
    shared_ptr<ContactFetcherRepositoryImpl> contactRepoImpl = make_shared<ContactFetcherRepositoryImpl>(contactService);
    shared_ptr<ContactListController> contactController = make_shared<ContactListController>(contactRepoImpl);
    ContactListModel* contactMenuModel = new ContactListModel(contactController);
    shared_ptr<ContactListPresenter> contactMenuPresenter = make_shared<ContactListPresenter>(contactMenu, contactMenuModel);


    MainWindow w(authMenu, contactMenu);
    w.show();

    return a.exec();

    delete authMenuModel;
    delete authMenu;
}
