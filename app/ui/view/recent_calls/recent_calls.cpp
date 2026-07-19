#include "recent_calls.h"
#include <QVBoxLayout>
#include <QLabel>

RecentCalls::RecentCalls(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("<b>Недавние звонки</b>", this);
    listWidget = new QListWidget(this);

    layout->addWidget(title);
    layout->addWidget(listWidget);
}

void RecentCalls::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    static bool loaded = false;
    if (!loaded) {
        emit viewReady();
        loaded = true;
    }
}

void RecentCalls::setCalls(const QStringList& calls)
{
    listWidget->clear();
    listWidget->addItems(calls);
}

void RecentCalls::appendCall(const QString& call)
{
    listWidget->insertItem(0, call);
}
