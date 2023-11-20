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

}
/*添加附件*/
void MainWindow::on_btnAddatt_released()
{
    QStringList names = QFileDialog::getOpenFileNames(this,"选择图片","./",
                                                      "All (*.*);;Images (*.jpg *.png *.jpeg *.gif);;"
                                                      "Exe (*.exe);;zip (*.zip *.7z *.tar)");
    for(QString filename : names)
    {

    }
}
/*添加图片*/
void MainWindow::on_btnAddImage_released()
{
    QStringList names =  QFileDialog::getOpenFileNames(this,"选择图片","./","Images (*.jpg *.png *.jpeg *.gif)");
    for(QString filename : names)
    {

    }
}
