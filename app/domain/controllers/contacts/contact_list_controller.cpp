#include "contact_list_controller.h"

ContactListController::ContactListController(QObject *parent)
    : QObject{parent}
{}

void ContactListController::proccessSelectedNumber(const QString &number)
{
    // осуществляется звонок
}

void ContactListController::updateContactList()
{
    repo->sendContactListRequest();
}
