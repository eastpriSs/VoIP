#include "contact_list_presenter.h"

ContactListPresenter::ContactListPresenter(ContactList *v, std::shared_ptr<ContactListModel> m, QObject *parent)
    : QObject{parent}, view(v), model(m)
{
    connect(view, &ContactList::contactChoose, model.get(), &ContactListModel::onContactClicked);
    connect(view, &ContactList::authConfigEntered, model.get(), &ContactListModel::onAuthConfigReceived);
    connect(view, &ContactList::updateListRequested, model.get(), &ContactListModel::onUpdateListRequested);
    connect(model.get(), &ContactListModel::showSettingsMenuRequested, view, &ContactList::authMenuRequested);
    connect(model.get(), &ContactListModel::authError, view, &ContactList::showError);
    connect(model.get(), &ContactListModel::showContacts, view, &ContactList::showContacts);
    connect(model.get(), &ContactListModel::setStatus, view, &ContactList::setStatusBarText);
    connect(model.get(), &ContactListModel::callMenuRequested, view, &ContactList::callMenu);
    connect(model.get(), &ContactListModel::hideStatus, view, &ContactList::onHideStatus);
}
