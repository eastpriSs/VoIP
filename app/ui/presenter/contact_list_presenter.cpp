#include "contact_list_presenter.h"

ContactListPresenter::ContactListPresenter(QObject *parent)
    : QObject{parent}
{
    connect(view, &ContactList::contactChoose, model, &ContactListModel::onContactClicked);
}
