#ifndef RECENT_CALL_REPOSITORY_H
#define RECENT_CALL_REPOSITORY_H

#include <QObject>
#include <QList>
#include "recent_call.h"

class IRecentCallRepository : public QObject
{
    Q_OBJECT
public:
    explicit IRecentCallRepository(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IRecentCallRepository() = default;

    virtual void saveCalls(const QList<RecentCallData>& calls) = 0;
    virtual QList<RecentCallData> getCalls() = 0;
};

#endif // RECENT_CALL_REPOSITORY_H
