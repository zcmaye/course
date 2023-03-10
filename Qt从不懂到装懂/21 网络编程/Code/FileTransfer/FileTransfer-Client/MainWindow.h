#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<QWidget>
#include<QTcpSocket>
namespace Ui
{
	class MainWindow;
}

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
public slots:
	void on_select_Send_btn_released();
	void onMsg(QTcpSocket* sock);
private:
	Ui::MainWindow* ui;
	int btnState{ 0 };
	QString filename;
};


#endif // !MAINWINDOW_H_
