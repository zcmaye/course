﻿#include "mainwindow.h"
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

    m_emailSender.setHostInfo("smtp.qq.com",25);
    m_emailSender.login("823861087@qq.com","liyonmsnpzjlbffb");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnMin_released()
{
    this->showMinimized();
}

void MainWindow::on_btnMax_released()
{
    if(windowState() & Qt::WindowState::WindowMaximized)
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
    auto recv = ui->editRecv->text();
    auto subject = ui->editSubject->text();

    m_emailSender.setHeader(recv,subject);
    m_emailSender.setBody(ui->textEdit->toHtml());
    m_emailSender.sendEmail();
}
/*添加附件*/
void MainWindow::on_btnAddatt_released()
{
    QStringList names = QFileDialog::getOpenFileNames(this,"选择图片","./","All (*.*);;Images (*.jpg *.png *.jpeg *.gif);;Exe (*.exe);;zip (*.zip *.7z *.tar)");
    m_emailSender.addAttr(names);
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
            if(file.size() > 1*1024*1024)
            {
                qWarning("图片超过1M,请使用附件的形式发送");
                continue;
            }
             ui->textEdit->insertHtml("<img src='data:image/png;base64," + file.readAll().toBase64() +" width='100' height='100''/>");
        }
    }
}
