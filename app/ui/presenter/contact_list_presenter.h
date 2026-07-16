#ifndef CONTACT_LIST_PRESENTER_H
#define CONTACT_LIST_PRESENTER_H

#include <QObject>
#include <memory>
#include "contact_list.h"
#include "contact_list_model.h"

class ContactListPresenter : public QObject
{
    Q_OBJECT
public:
    ContactListPresenter(ContactList* v, std::shared_ptr<ContactListModel> m, QObject *parent = nullptr);

signals:

private:
    ContactList* view;
    std::shared_ptr<ContactListModel> model;
};

#endif // CONTACT_LIST_PRESENTER_H
