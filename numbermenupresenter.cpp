#include "numbermenupresenter.h"
#include <QMessageBox>

NumberMenuPresenter::NumberMenuPresenter(NumberMenu* v, QObject *parent)
    : QObject{parent}, view(v)
{
    connect(view, &NumberMenu::backspaceClicked, this, &NumberMenuPresenter::on_backspaceClicked);
    connect(view, &NumberMenu::virtualKeyboardPressed, this, &NumberMenuPresenter::on_virtualKeyboardPressed);
    connect(view, &NumberMenu::clearClicked, this, &NumberMenuPresenter::on_clearClicked);
    connect(view, &NumberMenu::layoutSwitchToNumbersClicked, this, &NumberMenuPresenter::on_layoutSwitchToNumbersClicked);
    connect(view, &NumberMenu::layoutSwitchToLettersClicked, this, &NumberMenuPresenter::on_layoutSwitchToLettersClicked);
    connect(view, &NumberMenu::layoutSwitchToSymbolsClicked, this, &NumberMenuPresenter::on_layoutSwitchToSymbolsClicked);
    connect(view, &NumberMenu::confirmButtonClicked, this, &NumberMenuPresenter::on_confirmButtonClicked);
}

void NumberMenuPresenter::on_backspaceClicked()
{
    QString text = view->getTextNumber();
    if (!text.isEmpty()) {
         text.chop(1);
         view->setTextNumber(std::move(text));
    }
}

void NumberMenuPresenter::on_virtualKeyboardPressed(const QObject* sender)
{
    if (!sender) return;

    const QPushButton *button = qobject_cast<const QPushButton*>(sender);

    if (button)
        view->insertInTextNumber(button->text());
}

void NumberMenuPresenter::on_clearClicked()
{
    view->clearTextNumber();
}

void NumberMenuPresenter::on_layoutSwitchToLettersClicked()
{
    view->setupLettersLayout();
}

void NumberMenuPresenter::on_layoutSwitchToNumbersClicked()
{
    view->setupNumbersLayout();
}

void NumberMenuPresenter::on_layoutSwitchToSymbolsClicked()
{
    view->setupSymbolsLayout();
}

void NumberMenuPresenter::on_confirmButtonClicked(const QString &number)
{
    QMessageBox::warning(view, "Заглушка", QString("Здесь будет вызов по этому номеру: %1").arg(number));
}
