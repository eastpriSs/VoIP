#ifndef CONTACT_LIST_MODEL_H
#define CONTACT_LIST_MODEL_H

#include <QObject>

class ContactListModel : public QObject
{
    Q_OBJECT
public:
    explicit ContactListModel(QObject *parent = nullptr);

public slots:
    void onContactClicked(const QString& contact);

private:
    std::shared_ptr<ContactListController> contactController;

};

#endif // CONTACT_LIST_MODEL_H
