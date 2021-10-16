#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
class QLabel        ;
class QLineEdit     ;
class QCheckBox     ;
class QPushButton   ;
class QComboBox     ;
class LoginWidget : public QWidget
{
    Q_OBJECT
    struct User
    {
        User(const QString& username="",const QString& passwd="")
            :username(username),passwd(passwd)
        {
        }
        QString username;
        QString passwd;
    };

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void initUi();
    void closeEvent(QCloseEvent *event) override;
    void readSettings();
    void writeSettings();
private:
    QLabel* imageLabel;
    QComboBox* userNamaeEdit;
    QLineEdit* passwdEdit;
    QCheckBox* rememberCheckBox ;
    QCheckBox* autoLoginCheckBox;
    QPushButton* registerBtn ;
    QPushButton* forgetBtn;
    QPushButton* loginBtn;

    QList<User> user_list;
};
#endif // LOGINWIDGET_H
