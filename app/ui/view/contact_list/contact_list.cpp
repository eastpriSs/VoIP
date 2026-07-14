#include "contact_list.h"

ContactList::ContactList(QWidget *parent)
    : QListWidget{parent}
{
    connect(this, &ContactList::itemClicked, this, &ContactList::onContactClicked);
}

void ContactList::uploadList(const QStringList& contacts)
{
}

void ContactList::addContact(const QString &name)
{
    this->addItem(name);
}

void ContactList::removeSelectedContact()
{
    QListWidgetItem *item = this->currentItem();
    if (item) {
        delete item;
    }
}

void ContactList::setContacts(const QStringList &contacts)
{
    this->clear();
    this->addItems(contacts);
}

void ContactList::clearList()
{
    this->clear();
}

void ContactList::updateList()
{
    emit updateListRequested();
}

void ContactList::onContactClicked(QListWidgetItem *contact)
{
    emit contactChoose(contact->text());
}
