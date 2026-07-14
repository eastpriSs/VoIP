#ifndef CONTACT_LIST_MODEL_H
#define CONTACT_LIST_MODEL_H

#include <QObject>
#include "contact_list_controller.h"

class ContactListModel : public QObject
{
    Q_OBJECT
public:
    explicit ContactListModel(QObject *parent = nullptr);

public slots:
    void onContactClicked(const QString& contact);
    void onUpdateListRequested();
private:
    std::shared_ptr<ContactListController> contactController;

};

#endif // CONTACT_LIST_MODEL_H
