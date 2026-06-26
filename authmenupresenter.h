#ifndef AUTHMENUPRESENTER_H
#define AUTHMENUPRESENTER_H

#include <QObject>
#include "authmenu.h"
#include "authmenumodel.h"

class AuthMenuPresenter : public QObject {
    Q_OBJECT
public:
    explicit AuthMenuPresenter(AuthMenu* view, QObject* parent = nullptr);

public slots:
    void onLoginRequested(const QString& username, const QString& password);
    void onRegisterRequested(const QString& username, const QString& password);

    void onLoginSuccess();
    void onLoginFailed(const QString& error);
    void onRegisterSuccess();
    void onRegisterFailed(const QString& error);

private:
    AuthMenu* view;
    AuthMenuModel* model;
};

#endif // AUTHMENUPRESENTER_H
