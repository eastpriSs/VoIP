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

signals:
    void itemClicked(QListWidgetItem *item);
    void contactChoose(const QString& contact);

public slots:
    void uploadList(const QStringList& contacts);

private slots:
    void onContactClicked(QListWidgetItem* contact);
signals:
};

#endif // CONTACT_LIST_H
