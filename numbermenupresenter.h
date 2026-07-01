#ifndef NUMBERMENUPRESENTER_H
#define NUMBERMENUPRESENTER_H

#include <QObject>
#include "numbermenu.h"
#include "numbermenumodel.h"

class NumberMenuPresenter : public QObject
{
    Q_OBJECT
public:
    explicit NumberMenuPresenter(NumberMenu* v,  QObject *parent = nullptr);

public slots:
    void on_confirmButtonClicked(const QString &number);
    void on_virtualKeyboardPressed(const QObject* sender);
    void on_backspaceClicked();
    void on_clearClicked();
    void on_layoutSwitchToLettersClicked();
    void on_layoutSwitchToSymbolsClicked();
    void on_layoutSwitchToNumbersClicked();

signals:

private:
    NumberMenu* view;
    std::unique_ptr<NumberMenuModel> model;
};

#endif // NUMBERMENUPRESENTER_H
