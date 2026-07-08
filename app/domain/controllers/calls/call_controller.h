#ifndef CALL_CONTROLLER_H
#define CALL_CONTROLLER_H

#include <QObject>

class CallController : public QObject
{
    Q_OBJECT
public:
    explicit CallController(QObject *parent = nullptr);

signals:
};

#endif // CALL_CONTROLLER_H
