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
#include "call_controller.h"
#include "call_repository_impl.h"

#include "setting_menu.h"
#include "setting_menu_presenter.h"
#include "setting_menu_model.h"
#include "setting_controller.h"
#include "setting_repository_impl.h"


template<
    typename Menu,
    typename Presenter,
    typename Model,
    typename Controller,
    typename Repo,
    typename Service
    >
// todo добавить концепты на конструкторы как минимум
[[nodiscard]] Menu* makeStack(Service* service)
{
    using std::shared_ptr;

    Menu* menu = new Menu();
    shared_ptr<Repo> repo = std::make_shared<Repo>(service);
    shared_ptr<Controller> contorller = std::make_shared<Controller>(repo);
    Model* model = new Model(contorller);
    shared_ptr<Presenter> presenter = std::make_shared<Presenter>(menu, model);

    return menu;
}


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


    shared_ptr<SettingMenu> settingMenu = make_shared<SettingMenu>(new SettingMenu());
    shared_ptr<SettingRepositoryImpl> settingRepoImpl = make_shared<SettingRepositoryImpl>();
    shared_ptr<SettingController> settingController = make_shared<SettingController>(settingRepoImpl);
    shared_ptr<SettingMenuModel> settingMenuModel = make_shared<SettingMenuModel>(settingController);
    shared_ptr<SettingMenuPresenter> settingMenuPresenter = make_shared<SettingMenuPresenter>(settingMenu, settingMenuModel);

    MainWindow w(authMenu, callMenu, settingMenu.get());

    // реализация примитивного списка
    QObject::connect(callController.get(), &CallController::incomingCall,
         [&](QString  dist)
         {
            QString record = QString("%1 | %2 ").arg(dist, "Входящий");
            w.appendRecentCall(record);
         }
    );

    QObject::connect(callController.get(), &CallController::outComingCall,
         [&](QString  dist)
         {
             QString record = QString("%1 | %2 ").arg(dist, "Исходящий");
             w.appendRecentCall(record);
         }
    );


    w.show();

    return a.exec();
}
