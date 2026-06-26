#ifndef AUTHMENU_H
#define AUTHMENU_H

#include <QDialog>
#include <memory>

class QLineEdit;
class QPushButton;
class QLabel;

class AuthMenu : public QDialog {
    Q_OBJECT
public:
    explicit AuthMenu(QWidget *parent = nullptr);
    ~AuthMenu();

signals:
    void loginRequested(const QString& username, const QString& password);
    void registerRequested(const QString& username, const QString& password);
    void cancelRequested();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QPushButton* loginButton;
    QPushButton* registerButton;
    QPushButton* cancelButton;
    QLabel* statusLabel;
};

#endif // AUTHMENU_H
