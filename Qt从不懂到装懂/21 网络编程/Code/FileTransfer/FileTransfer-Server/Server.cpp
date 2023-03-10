#include "Server.h"

Server::Server(QObject*parent)
    : QObject(parent)
    ,m_tcpServer(new QTcpServer(this))
{

}

Server::~Server()
{
    for (auto client : m_clients)
    {
        client->close();
    }
    m_tcpServer->close();
}

bool Server::startListen(quint16 port)
{
    if (!m_tcpServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "startListen failed:" << m_tcpServer->errorString();
        return false;
    }
    connect(m_tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnetion);
    qDebug() << "Server listen succeed~";
    return true;
}

void Server::onNewConnetion()
{
    //如果有待处理的连接
    while (m_tcpServer->hasPendingConnections())
    {
        //获取下一个未处理的连接
        QTcpSocket* newSocket = m_tcpServer->nextPendingConnection();
        m_clients.insert(qHash(newSocket),newSocket);

        //连接socket信号
        connect(newSocket, &QTcpSocket::disconnected, this, &Server::onDisConnected);
        connect(newSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    }
    qInfo() << "total connection nums:" << m_clients.size();
}

void Server::onDisConnected()
{
    //获得信号的发送者的指针
    QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
    if(!tcpSocket)
        return;
    
    m_clients.remove(qHash(tcpSocket));
}

void Server::onReadyRead()
{
    QTcpSocket *tcpScoket = dynamic_cast<QTcpSocket*>(sender());
    if(!tcpScoket)
        return;

    while (tcpScoket->bytesAvailable())
    {
        //接受数据
        QByteArray data = tcpScoket->readAll();

        //消息转发(发给别的客户端)
        for (auto socket : m_clients)
        {
            //排除发消息的客户端
            if (socket != tcpScoket)
            {
                socket->write(data);
            }
        }
        qInfo() << "成功转发一条数据~~~";
    }
}
