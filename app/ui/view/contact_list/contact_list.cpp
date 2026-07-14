#include "contact_list.h"

ContactList::ContactList(QWidget *parent)
    : QListWidget{parent}
{}

void ContactList::uploadList()
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
