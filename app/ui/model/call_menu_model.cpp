#include "call_menu_model.h"

CallMenuModel::CallMenuModel(QObject *parent) : QObject(parent) {}

void CallMenuModel::onKeyPressed(const QString& text) {
    m_currentNumber += text;
    emit textChanged(m_currentNumber);
}

void CallMenuModel::onBackspacePressed() {
    if (!m_currentNumber.isEmpty()) {
        m_currentNumber.chop(1);
        emit textChanged(m_currentNumber);
    }
}

void CallMenuModel::onClearPressed() {
    m_currentNumber.clear();
    emit textChanged(m_currentNumber);
}

void CallMenuModel::onLayoutSwitchRequested(int layoutId) {
    emit layoutChanged(layoutId);
}

void CallMenuModel::onConfirmPressed(const QString& number) {
    QString msg = QString("Здесь будет вызов по этому номеру: %1").arg(number);
    emit warningRequested("Заглушка", msg);
}
