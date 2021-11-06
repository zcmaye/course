#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Comm/eventfilterobject.h"
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->installEventFilter(new eventFilterObject(this));
    this->setWindowFlag(Qt::WindowType::FramelessWindowHint,true);
    this->setAttribute(Qt::WA_TranslucentBackground);

    emailSender.login("1140412397@qq.com","kgkuqixghafdijid");
    //emailSender.login("825943234@qq.com","copfxxjdwrwjbfbf");
    //emailSender.setHostInfo("smtp.163.com",25);
    //emailSender.login("ydpatjj@163.com","ydp520zy");

}

MainWindow::~MainWindow()
{
    emailSender.quit();
    delete ui;
}


void MainWindow::on_btnMin_released()
{
    this->showMinimized();
}

void MainWindow::on_btnMax_released()
{
    if(windowState() == Qt::WindowState::WindowMaximized)
        this->showNormal();
    else
        this->showMaximized();
}

void MainWindow::on_btnClose_released()
{
    this->close();
}

/*发送邮件*/
void MainWindow::on_btnSend_released()
{
    //获取接收人
    auto tolist = ui->editRecv->text().split(";");
    auto subject = ui->editSubject->text();
    auto body = ui->editBody->toHtml();

    emailSender.setHeader(tolist,subject);
    emailSender.setBody(body);
    emailSender.sendEmail();
}
/*添加附件*/
void MainWindow::on_btnAddatt_released()
{
    QStringList names = QFileDialog::getOpenFileNames(this,"选择图片","./","All (*.*);;Images (*.jpg *.png *.jpeg *.gif);;Exe (*.exe);;zip (*.zip *.7z *.tar)");
    for(QString filename : names)
    {
        emailSender.addAttachment(filename);
    }

}
/*添加图片*/
void MainWindow::on_btnAddImage_released()
{
    QStringList names =  QFileDialog::getOpenFileNames(this,"选择图片","./","Images (*.jpg *.png *.jpeg *.gif)");
    for(QString filename : names)
    {
        QFile file(filename);
        if(file.open(QIODevice::ReadOnly))
        {
            if(file.size()>1024*1024)
            {
                //qWarning("文件超过1M,请用附件方式传送");
                ui->labelTip->setText("<font style='color:red;'>文件超过1M,请用附件方式传送</font>");
                continue;
            }
            qDebug()<<file.fileName()<<file.size();
            ui->editBody->insertHtml("<img src='data:image/png;base64," + file.readAll().toBase64() +"' width:'100px' height:'100px'/>");
        }
    }
}
