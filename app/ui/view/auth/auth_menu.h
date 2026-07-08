#ifndef AUTHMENU_H
#define AUTHMENU_H

#include <QDialog>

class QLineEdit;
class QPushButton;
class QLabel;
class QProgressBar;

class AuthMenu : public QDialog {
    Q_OBJECT
public:
    explicit AuthMenu(QWidget *parent = nullptr);
    ~AuthMenu();

    void setProgress(int value);
    void setProgressVisible(bool visible);
    void setBottomStatus(const QString& text);

private:
    void resetProgress();

signals:
    void loginRequested(const QString& username, const QString& password);
    void registerRequested(const QString& username,
                           const QString& password,
                           const QString& sipServer,
                           int sipPort);
    void cancelRequested();

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();

public slots:
    void onRegisterFailed(QString err_text);
    void onRegisterSucces(QString err_text);
    void onProgressChanged(QString status);

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* sipServerEdit;
    QLineEdit* sipPortEdit;

    QPushButton* loginButton;
    QPushButton* registerButton;
    QPushButton* cancelButton;

    QLabel* statusLabel;

    QProgressBar* progressBar;
    QLabel* bottomStatusLabel;
};

#endif // AUTHMENU_H
