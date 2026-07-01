#ifndef NUMBERMENUMODEL_H
#define NUMBERMENUMODEL_H

#include <QObject>

class NumberMenuModel : public QObject
{
    Q_OBJECT
public:
    explicit NumberMenuModel(QObject *parent = nullptr);

signals:
};

#endif // NUMBERMENUMODEL_H
