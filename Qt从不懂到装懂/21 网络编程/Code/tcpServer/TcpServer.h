#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnStart_clicked();

    void onError(QAbstractSocket::SocketError socketError);
    void onNewConnetion();
    void onDisConnection();
    void on_btnClose_released();
    void onReadyRead();
private:
    Ui::MainWindow *ui;
    QTcpServer *m_tcpServer;

    //定义一个列表，保存连接上的socket
    QList<QTcpSocket*> m_clients;
};
#endif // MAINWINDOW_H
