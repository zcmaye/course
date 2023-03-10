#ifndef SERVER_H
#define SERVER_H

#include<QTcpServer>
#include<QTcpSocket>
#include<QHash>
class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject*parent = nullptr);
    ~Server();
    bool startListen(quint16 port);
private slots:
    //服务器接受连接
    void onNewConnetion();
    //客户端消息
    void onDisConnected();
    void onReadyRead();
private:

    QTcpServer *m_tcpServer;

    QHash<size_t,QTcpSocket*> m_clients;
};
#endif // MAINWINDOW_H
