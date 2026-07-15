#include "contact_list.h"
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
    QDialog dialog(this->window());
    dialog.setWindowTitle(tr("Настройки подключения PBX"));

    QFormLayout form(&dialog);

    QLineEdit clientIdEdit(&dialog);

    QLineEdit clientSecretEdit(&dialog);
    clientSecretEdit.setEchoMode(QLineEdit::Password);

    QLineEdit serverEdit(&dialog);
    serverEdit.setPlaceholderText("http://example.com");

    form.addRow(tr("Client ID:"), &clientIdEdit);
    form.addRow(tr("Client Secret:"), &clientSecretEdit);
    form.addRow(tr("Server HTTPS:"), &serverEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString clientId = clientIdEdit.text().trimmed();
        QString clientSecret = clientSecretEdit.text().trimmed();
        QString server = serverEdit.text().trimmed();

        if (!statusDialog) {
            statusDialog = new QDialog(this->window());
            statusDialog->setWindowTitle(tr("Статус авторизации"));
            statusDialog->resize(HEIGHT_STATUS_LABEL, WEIGHT_STATUS_LABEL);

            QVBoxLayout *layout = new QVBoxLayout(statusDialog);
            statusLabel = new QLabel(tr("Инициализация..."), statusDialog);

            statusLabel->setAlignment(Qt::AlignCenter);

            layout->addWidget(statusLabel);
        }

        statusDialog->show();
        statusLabel->setText(tr("Подключение к серверу..."));

        emit authConfigEntered(clientId, clientSecret, server);
    }
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

void ContactList::onHideStatus()
{
    if (statusDialog)
        statusDialog->hide();
}
