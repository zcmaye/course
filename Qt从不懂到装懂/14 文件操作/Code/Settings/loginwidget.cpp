#include "loginwidget.h"
#include<QLabel>
#include<QCheckBox>
#include<QPushButton>
#include<QLineEdit>
#include<QComboBox>
#include<QGridLayout>
#include<QSettings>
#include<QApplication>
#include<QDebug>
LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    initUi();
    readSettings();
}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::initUi()
{
   imageLabel = new QLabel;
   userNamaeEdit = new QComboBox;
   passwdEdit = new QLineEdit;
   rememberCheckBox = new QCheckBox;
   autoLoginCheckBox = new QCheckBox;
   registerBtn = new QPushButton;
   forgetBtn = new QPushButton;
   loginBtn = new QPushButton;

    //设置图片
    imageLabel->setFixedSize(90,90);
    imageLabel->setPixmap(QPixmap("://images/loginIcon.png"));
    imageLabel->setScaledContents(true);

    //设置输入框
    userNamaeEdit->setEditable(true);
    userNamaeEdit->lineEdit()-> setPlaceholderText("QQ号码/手机/邮箱");
    passwdEdit->setPlaceholderText("密码");

    //设置复选框
    rememberCheckBox->setText("记住密码");
    autoLoginCheckBox->setText("自动登录");

    //设置按钮
    registerBtn->setText("注册账号");
    forgetBtn->setText("找回密码");
    loginBtn->setText("登录");

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(imageLabel,0,0,3,1);
    layout->addWidget(userNamaeEdit,0,1,1,2);
    layout->addWidget(registerBtn,0,3);
    layout->addWidget(passwdEdit,1,1,1,2);
    layout->addWidget(forgetBtn,1,3);
    layout->addWidget(rememberCheckBox,2,1);
    layout->addWidget(autoLoginCheckBox,2,2);
    layout->addWidget(loginBtn,3,1,1,2);

    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(10);
    layout->setContentsMargins(20,20,20,20);

    this->setLayout(layout);

    connect(loginBtn,&QPushButton::clicked,this,[=]()
    {
       if(!userNamaeEdit->currentText().isEmpty())
       {
           userNamaeEdit->addItem(userNamaeEdit->currentText());

           User user(userNamaeEdit->currentText(),passwdEdit->text());
           user_list.push_back(user);
       }
    });
}

void LoginWidget::closeEvent(QCloseEvent *event)
{
    writeSettings();
}

void LoginWidget::readSettings()
{
    QSettings settings(QApplication::applicationDirPath()+"/setting.ini",QSettings::Format::IniFormat);
    rememberCheckBox->setChecked(settings.value("rememberPasswd").toBool());
    autoLoginCheckBox->setChecked(settings.value("autoLogin").toBool());

    userNamaeEdit->lineEdit()->setText(settings.value("user/userName").toString());
    passwdEdit->setText(settings.value("user/passwd").toString());

    int cnt = settings.beginReadArray("users");
    qDebug()<<settings.childGroups()<<settings.childKeys();
    for(int i = 0;i<cnt;i++)
    {
        settings.setArrayIndex(i);
        User user;
        user.username = settings.value("userName").toString();
        user.passwd = settings.value("passwd").toString();
        user_list.push_back(user);
        userNamaeEdit->addItem(user.username);
        passwdEdit->setText(user.passwd);
    }
    settings.endArray();


}

void LoginWidget::writeSettings()
{
    QSettings settings(QApplication::applicationDirPath()+"/setting.ini",QSettings::Format::IniFormat);
    settings.setValue("rememberPasswd",rememberCheckBox->isChecked());
    settings.setValue("autoLogin",autoLoginCheckBox->isChecked());

    settings.beginGroup("user");
    settings.setValue("userName",userNamaeEdit->lineEdit()->text());
    settings.setValue("passwd",passwdEdit->text());
    settings.endGroup();

    settings.beginWriteArray("users");
    for(int i = 0; i < user_list.size();i++)
    {
        settings.setArrayIndex(i);
        settings.setValue("userName",user_list[i].username);
        settings.setValue("passwd",user_list[i].passwd);
    }
    settings.endArray();
    settings.remove("user");



}

