#include "contact_list.h"
#include "setting_menu.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

ContactList::ContactList(QWidget *parent)
    : QListWidget{parent},
    statusDialog(nullptr),
    statusLabel(nullptr)
{
    connect(this, &QListWidget::itemDoubleClicked, this, &ContactList::onContactClicked);
}

void ContactList::setSettingMenu(std::shared_ptr<SettingMenu> menu)
{
    settingMenu = menu;
}

void ContactList::onSettingsSubmitted(const QString &clientId, const QString &clientSecret, const QString &httpServer)
{
    emit authConfigEntered(clientId, clientSecret, httpServer);
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

void ContactList::onContactClicked(QListWidgetItem *contact)
{
    emit contactChoose(contact->text());
}

void ContactList::updateList()
{
    emit updateListRequested();
}

void ContactList::showError(const QString &message)
{
    QMessageBox::critical(this, tr("Ошибка валидации данных"), message);
}

void ContactList::showContacts(QStringList contacts)
{
    setContacts(contacts);
}

void ContactList::setStatusBarText(const QString &text)
{
    if (statusDialog && statusLabel) {
        statusLabel->setText(text);
        if (!statusDialog->isVisible()) {
            statusDialog->show();
        }
    }
}

void ContactList::callMenu(const QString &contact)
{
    emit callMenuShowRequested(contact);
}

void ContactList::authMenuRequested()
{
    if (settingMenu) {
        settingMenu->exec();
    } else {
        qInfo() << "where setting menu??";
    }
}

void ContactList::onHideStatus()
{
    if (statusDialog)
        statusDialog->hide();
}
