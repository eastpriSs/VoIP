#include "recent_call_controller.h"

RecentCallController::RecentCallController(std::shared_ptr<IRecentCallRepository> repo, QObject *parent)
    : QObject{parent}, repo(repo) {}

void RecentCallController::loadCalls()
{
    if (!repo) return;

    cacheList = repo->getCalls();
    emit callsLoaded(cacheList);
}

void RecentCallController::addCall(const QString& number, const QDateTime& time, int durationSec, bool isIncoming)
{
    RecentCallData newCall{time, durationSec, number, isIncoming};
    cacheList.prepend(newCall);

    if (cacheList.size() > 100) {
        cacheList.removeLast();
    }

    if (repo) {
        repo->saveCalls(cacheList);
    }

    emit callAdded(newCall);
}
