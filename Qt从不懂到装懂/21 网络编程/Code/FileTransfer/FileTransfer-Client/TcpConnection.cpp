#include "TcpConnection.h"
#include "TcpConnection.h"
#include "TcpConnection.h"

TcpConnection::TcpConnection(QObject*parent)
    : QObject(parent)
    ,m_tcpSocket(new QTcpSocket(this))
{

}

TcpConnection::~TcpConnection()
{
    m_tcpSocket->close();
}

void TcpConnection::connectToHost(const QHostAddress& addr, quint16 port)
{
    m_tcpSocket->connectToHost(addr, port);
    connect(m_tcpSocket, &QTcpSocket::errorOccurred, this, &TcpConnection::onErrorOccurred);
    connect(m_tcpSocket, &QTcpSocket::connected, this, &TcpConnection::onConnected);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &TcpConnection::onDisConnected);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, [=] {if (onReadyRead) emit onReadyRead; });
}

TcpConnection* TcpConnection::mainCon()
{
    static TcpConnection*  con = new TcpConnection;
    con->connectToHost(QHostAddress("127.0.0.1"), 5678);
    return con;
}


void TcpConnection::onErrorOccurred(QTcpSocket::SocketError error)
{
    qWarning() << "connection Error:" << m_tcpSocket->errorString();
}

void TcpConnection::onConnected()
{
    qWarning() << "connection Successed!";
}

void TcpConnection::onDisConnected()
{
    qWarning() << "Server Quit:" << m_tcpSocket->errorString();
    m_tcpSocket->close();
}
