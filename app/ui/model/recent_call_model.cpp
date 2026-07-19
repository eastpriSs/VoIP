#include "recent_call_model.h"

RecentCallModel::RecentCallModel(std::shared_ptr<RecentCallController> controller, QObject *parent)
    : QObject{parent}, controller(controller)
{
    connect(this->controller.get(), &RecentCallController::callsLoaded,
            this, &RecentCallModel::onCallsLoaded);
    connect(this->controller.get(), &RecentCallController::callAdded,
            this, &RecentCallModel::onCallAdded);
}

void RecentCallModel::requestLoad()
{
    controller->loadCalls();
}

QString RecentCallModel::formatCallData(const RecentCallData& call)
{
    QString type = call.isIncoming ? "Входящий" : "Исходящий";
    QString timeStr = call.time.toString("dd.MM.yy HH:mm");

    QString durationStr = QString("%1 мин %2 сек")
                              .arg(call.durationSeconds / 60)
                              .arg(call.durationSeconds % 60);

    return QString("%1 | %2 | %3 | %4")
        .arg(timeStr)
        .arg(type, 10)
        .arg(call.number, 15)
        .arg(durationStr);
}

void RecentCallModel::onCallsLoaded(const QList<RecentCallData>& calls)
{
    QStringList formattedList;
    for (const RecentCallData& call : calls) {
        formattedList.append(formatCallData(call));
    }
    emit updateViewWithList(formattedList);
}

void RecentCallModel::onCallAdded(const RecentCallData& call)
{
    emit updateViewWithNewCall(formatCallData(call));
}
