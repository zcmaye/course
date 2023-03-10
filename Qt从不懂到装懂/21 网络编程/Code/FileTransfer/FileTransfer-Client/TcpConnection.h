#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include<QTcpSocket>
class TcpConnection : public QObject
{
    Q_OBJECT
public:
    TcpConnection(QObject*parent = nullptr);
    ~TcpConnection();
    void connectToHost(const QHostAddress& addr, quint16 port);
    static TcpConnection* mainCon();
private slots:
    void onErrorOccurred(QTcpSocket::SocketError error);
    void onConnected();
    void onDisConnected();
public:
    std::function<void(QTcpSocket* sock)> onReadyRead;
private:
    QTcpSocket *m_tcpSocket;
};
#endif // TCPCONNECTION_H
