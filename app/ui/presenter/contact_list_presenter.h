#ifndef CONTACT_LIST_PRESENTER_H
#define CONTACT_LIST_PRESENTER_H

#include <QObject>
#include "contact_list.h"
#include "contact_list_model.h"

class ContactListPresenter : public QObject
{
    Q_OBJECT
public:
    ContactListPresenter(ContactList* v, ContactListModel* m,  QObject *parent = nullptr);

signals:

private:
    ContactList* view;
    ContactListModel* model;
};

#endif // CONTACT_LIST_PRESENTER_H
