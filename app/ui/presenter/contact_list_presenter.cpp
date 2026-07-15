#include "contact_list_presenter.h"

ContactListPresenter::ContactListPresenter(ContactList *v, ContactListModel *m, QObject *parent)
    : QObject{parent}, view(v), model(m)
{
    connect(view, &ContactList::contactChoose, model, &ContactListModel::onContactClicked);
    connect(view, &ContactList::updateListRequested, model, &ContactListModel::onUpdateListRequested);
    connect(view, &ContactList::authConfigEntered, model, &ContactListModel::onAuthConfigReceived);
    connect(model, &ContactListModel::authError, view, &ContactList::showError);
    connect(model, &ContactListModel::showContacts, view, &ContactList::showContacts);
    connect(model, &ContactListModel::setStatus, view, &ContactList::setStatusBarText);
    connect(model, &ContactListModel::callMenuRequested, view, &ContactList::callMenu);
}
