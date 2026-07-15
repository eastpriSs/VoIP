#ifndef CALL_MENU_PRESENTER_H
#define CALL_MENU_PRESENTER_H

#include <QObject>
#include <memory>
#include "call_menu.h"
#include "call_menu_model.h"

class CallMenuPresenter : public QObject
{
    Q_OBJECT
public:
    explicit CallMenuPresenter(CallMenu* v, CallMenuModel* m, QObject *parent = nullptr);

private:
    CallMenu* view;
    std::unique_ptr<CallMenuModel> model;
};

#endif // CALL_MENU_PRESENTER_H
