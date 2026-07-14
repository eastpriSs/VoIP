#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <QListWidget>

class ContactList : public QListWidget
{
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);

    void addContact(const QString &name);
    void removeSelectedContact();
    void setContacts(const QStringList &contacts);
    void clearList();

public slots:
    void uploadList();

signals:
};

#endif // CONTACT_LIST_H
