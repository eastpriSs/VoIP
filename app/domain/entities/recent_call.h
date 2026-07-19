#ifndef RECENT_CALL_H
#define RECENT_CALL_H
#include <QDateTime>
#include <QString>

struct RecentCallData {
    QDateTime time;
    int durationSeconds;
    QString number;
    bool isIncoming;
};

#endif // RECENT_CALL_H
