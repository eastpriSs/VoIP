#include "main_window.h"
#include <QApplication>

#include "data/services/SIP/module_sip.h"
#include "auth_repository_impl.h"
#include "domain/controllers/auth/auth_controller.h"
#include "auth_menu_presenter.h"
#include "auth_menu.h"
#include "auth_menu_model.h"

#include "call_menu.h"
#include "call_menu_presenter.h"
#include "call_menu_model.h"

// TODO : template  T  makeMenu
// where T is CallMenu or AuthMenu, ...

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

    CallMenu* callMenu = new CallMenu();
    CallMenuModel* callMenuModel = new CallMenuModel();
    std::shared_ptr<CallMenuPresenter> callMenuPresenter = make_shared<CallMenuPresenter>(callMenu, callMenuModel);

    MainWindow w(authMenu, callMenu);
    w.show();

    return a.exec();

    delete authMenuModel;
    delete authMenu;
}
