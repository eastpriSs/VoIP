#ifndef CONTACT_LIST_H
#define CONTACT_LIST_H

#include <QListWidget>
#include <QDialog>
#include <QLabel>

class ContactList : public QListWidget
{
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);

    void addContact(const QString &name);
    void removeSelectedContact();
    void setContacts(const QStringList &contacts);
    void clearList();
    void updateList();

signals:
    void itemClicked(QListWidgetItem *item);
    void contactChoose(const QString& contact);
    void updateListRequested();
    void authConfigEntered(const QString &clientId, const QString &clientSecret, const QString &server);
    void callMenuShowRequested(const QString &contact);

public slots:
    void uploadList(const QStringList& contacts);
    void showError(const QString &message);
    void showContacts(QStringList contacts);
    void setStatusBarText(const QString &text);
    void callMenu(const QString &contact);

private slots:
    void onContactClicked(QListWidgetItem* contact);

private:
    QDialog *statusDialog = nullptr;
    QLabel *statusLabel = nullptr;
};

#endif // CONTACT_LIST_H
