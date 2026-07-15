#ifndef RECENT_CALL_MODEL_H
#define RECENT_CALL_MODEL_H

#include <QObject>
#include <memory>
#include <QStringList>
#include "recent_call_controller.h"
#include "recent_call.h"

class RecentCallModel : public QObject
{
    Q_OBJECT
public:
    explicit RecentCallModel(std::shared_ptr<RecentCallController> controller, QObject *parent = nullptr);

public slots:
    void requestLoad();

signals:
    void updateViewWithList(const QStringList& formattedCalls);
    void updateViewWithNewCall(const QString& formattedCall);

private slots:
    void onCallsLoaded(const QList<RecentCallData>& calls);
    void onCallAdded(const RecentCallData& call);

private:
    std::shared_ptr<RecentCallController> controller;
    QString formatCallData(const RecentCallData& call);
};

#endif // RECENT_CALL_MODEL_H
