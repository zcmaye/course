#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>
#include<QFile>
#include<QProgressDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum MSG_Type:quint8{Null,Text,File};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnect_released();
    void onError(QAbstractSocket::SocketError socketError);
    void onConneted();
    void onReadyRead();


    void on_btnDisConnect_released();

    void on_btnSend_released();

    void on_btnSendFile_released();

    //如果是图片
    void image(const QString& filename);

private:
    Ui::MainWindow *ui;

    QTcpSocket *m_tcpSocket;

    qint8   m_msgType = Null;   //消息类型
    QByteArray m_filename;         //文件名
    quint64 m_dataSize = 0;     //除去头之外的，发送的文件的总大小
    QFile   m_localFile;        //
    quint64 m_recvSize = 0;     //接收到的数据的总大小

    QProgressDialog *m_diaog;

};
#endif // MAINWINDOW_H
