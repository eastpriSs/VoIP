#ifndef CALL_CONTROLLER_H
#define CALL_CONTROLLER_H

#include <QObject>
#include <QString>
#include "call_repository.h"

class CallController : public QObject
{
    Q_OBJECT
public:
    explicit CallController(std::shared_ptr<ICallRepository> rep, QObject *parent = nullptr);
    void callNumber(QString number);
private:
    std::shared_ptr<ICallRepository> repo;
};

#endif // CALL_CONTROLLER_H
