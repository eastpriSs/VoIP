#ifndef CONTACT_LIST_PRESENTER_H
#define CONTACT_LIST_PRESENTER_H

#include <QObject>

class ContactListPresenter : public QObject
{
    Q_OBJECT
public:
    explicit ContactListPresenter(QObject *parent = nullptr);

signals:
};

#endif // CONTACT_LIST_PRESENTER_H
