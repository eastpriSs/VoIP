#ifndef RECENT_CALL_H
#define RECENT_CALL_H

struct RecentCallData {
    QDateTime time;
    int durationSeconds;
    QString number;
    bool isIncoming;
};

#endif // RECENT_CALL_H
