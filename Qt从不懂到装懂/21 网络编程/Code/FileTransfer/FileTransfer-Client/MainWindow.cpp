#include"MainWindow.h"
#include"ui_MainWindow.h"
#include<QFileDialog>
#include "TcpConnection.h"
MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
	,ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->sendProgressWidget->hide();
	TcpConnection::mainCon()->onReadyRead =  std::bind(&MainWindow::onMsg,this,std::placeholders::_1);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::onMsg(QTcpSocket* sock)
{

}

void MainWindow::on_select_Send_btn_released()
{
	//选择文件
	if (btnState == 0)
	{
		filename = QFileDialog::getOpenFileName(this, "选择要发送的文件", "../bin", "all(*.*);;images(*.jpg;*.png;*.jpeg;*.gif);;exe(*.exe);;package(*.zip;*.7z)");
		if (filename.isEmpty())
		{
			return;
		}
		ui->filePathEdit->setText(QFileInfo(filename).fileName());
		ui->select_Send_btn->setText("发送");
		btnState = 1;
	}
	//发送文件
	else
	{
		ui->select_Send_btn->setEnabled(false);
		ui->sendProgressWidget->show();
		btnState = 0;


		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly))
		{
			qWarning() << "file open failed:" << file.errorString();
			return;
		}
		double totalSize = 0;
		while (!file.atEnd())
		{
			auto data = file.read(1024 * 5);
			//发送
			
			//设置进度
			totalSize += data.size();
			ui->sendProgressBar->setValue(totalSize /file.size() *100);
			//qInfo() << "progress" << totalSize / file.size() * 100;
		}
		ui->select_Send_btn->setText("选择文件");
		ui->select_Send_btn->setEnabled(true);
		ui->sendProgressWidget->hide();

	}
	qInfo() << "btn";
}
