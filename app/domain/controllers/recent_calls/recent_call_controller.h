#ifndef RECENT_CALL_CONTROLLER_H
#define RECENT_CALL_CONTROLLER_H

#include <QObject>
#include <memory>
#include <QList>
#include <QDateTime>
#include "recent_call_repository.h"
#include "recent_call.h"

class RecentCallController : public QObject
{
    Q_OBJECT
public:
    explicit RecentCallController(std::shared_ptr<IRecentCallRepository> repo, QObject *parent = nullptr);

public slots:
    void loadCalls();
    void addCall(const QString& number, const QDateTime& time, int durationSec, bool isIncoming);

signals:
    void callsLoaded(const QList<RecentCallData>& calls);
    void callAdded(const RecentCallData& call);

private:
    std::shared_ptr<IRecentCallRepository> repo;
    QList<RecentCallData> cacheList;
};

#endif // RECENT_CALL_CONTROLLER_H
