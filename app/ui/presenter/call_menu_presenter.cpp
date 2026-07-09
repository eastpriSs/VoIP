#include "call_menu_presenter.h"

CallMenuPresenter::CallMenuPresenter(CallMenu* v, CallMenuModel* m, QObject *parent)
    : QObject(parent), view(v), model(m)
{
    connect(view, &CallMenu::keyPressed, model.get(), &CallMenuModel::onKeyPressed);
    connect(view, &CallMenu::backspacePressed, model.get(), &CallMenuModel::onBackspacePressed);
    connect(view, &CallMenu::clearPressed, model.get(), &CallMenuModel::onClearPressed);
    connect(view, &CallMenu::layoutSwitchRequested, model.get(), &CallMenuModel::onLayoutSwitchRequested);
    connect(view, &CallMenu::confirmPressed, model.get(), &CallMenuModel::onConfirmPressed);
    connect(view, &CallMenu::callAccepted, model.get(), &CallMenuModel::onIncomingCallAccept);
    connect(view, &CallMenu::callRejected, model.get(), &CallMenuModel::onIncomingCallRejected);

    connect(model.get(), &CallMenuModel::textChanged, view, &CallMenu::setTextNumber);
    connect(model.get(), &CallMenuModel::layoutChanged, view, &CallMenu::changeLayout);
    connect(model.get(), &CallMenuModel::warningRequested, view, &CallMenu::showWarning);
    connect(model.get(), &CallMenuModel::errorRequested, view, &CallMenu::showError);
    connect(model.get(), &CallMenuModel::statusBarTextRequest, view, &CallMenu::setStatusBarText);
    connect(model.get(), &CallMenuModel::incomingCallMenuRequested, view, &CallMenu::showIncomingCallMenu);
    connect(model.get(), &CallMenuModel::callingMenuRequested, view, &CallMenu::onRequestCallingMenu);
    connect(model.get(), &CallMenuModel::rejectMenuRequested, view, &CallMenu::onRequestRejectMenu);

}
