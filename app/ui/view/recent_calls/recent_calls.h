#ifndef RECENT_CALLS_H
#define RECENT_CALLS_H

#include <QWidget>
#include <QListWidget>
#include <QStringList>
#include <QShowEvent>

class RecentCalls : public QWidget
{
    Q_OBJECT
public:
    explicit RecentCalls(QWidget *parent = nullptr);

public slots:
    void setCalls(const QStringList& calls);
    void appendCall(const QString& call);

signals:
    void viewReady();

protected:
    void showEvent(QShowEvent *event) override;

private:
    QListWidget* listWidget;
};

#endif // RECENT_CALLS_H
