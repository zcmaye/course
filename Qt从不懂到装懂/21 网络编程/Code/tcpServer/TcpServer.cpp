#include "TcpServer.h"
#include "ui_TcpServer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_tcpServer(new QTcpServer(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStart_clicked()
{
    //ushort  2个字节 [0,65535] 0~1024 保留端口，我们一般不要使用他
    bool isOk = m_tcpServer->listen(QHostAddress(ui->editIp->currentText()),ui->editPort->text().toUShort());
    if(isOk)
    {
        connect(m_tcpServer,&QTcpServer::acceptError,this,&MainWindow::onError);
        connect(m_tcpServer,&QTcpServer::newConnection,this,&MainWindow::onNewConnetion);
        ui->btnStart->setText("服务器已经开启了");
        ui->btnStart->setEnabled(false);
    }
    else
    {
        qDebug()<<"has error"<<m_tcpServer->errorString();
    }
}

void MainWindow::onError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<socketError<<m_tcpServer->errorString();
}


void MainWindow::onNewConnetion()
{
    //获取下一个未处理的连接
    QTcpSocket* newSocket = m_tcpServer->nextPendingConnection();
    if(!newSocket)
        return;
    m_clients.push_back(newSocket);
    //连接socket断开信号
    connect(newSocket,&QTcpSocket::disconnected,this,&MainWindow::onDisConnection);
    connect(newSocket,&QTcpSocket::readyRead,this,&MainWindow::onReadyRead);

    //获取对方的信息ip，port
    QString info = newSocket->peerAddress().toString()+":"+QString::number(newSocket->peerPort());
    //添加到listwidget
    ui->listWidget->addItem(info);
}

void MainWindow::onDisConnection()
{
    //获得信号的发送者的指针
    QTcpSocket* tcpSocket = dynamic_cast<QTcpSocket*>(sender());
    if(!tcpSocket)
        return;

     QString info = tcpSocket->peerAddress().toString()+":"+QString::number(tcpSocket->peerPort());
    //在listwidget中查找对应的客户端并移除
    auto list = ui->listWidget->findItems(info,Qt::MatchFlag::MatchContains);
    if(!list.isEmpty())
    {
        delete  list.first();   //获取第一个
    }
}

void MainWindow::on_btnClose_released()
{
    ui->btnStart->setEnabled(true);
    ui->btnStart->setText("开启服务器");

    m_tcpServer->close();
}

void MainWindow::onReadyRead()
{
    QTcpSocket *tcpScoket = dynamic_cast<QTcpSocket*>(sender());
    if(!tcpScoket)
        return;
    //接受数据
    QByteArray data = tcpScoket->readAll();
    static int size = 0;
    //消息转发(发给别的客户端)
    for(auto socket : m_clients)
    {
        //排除发消息的客户端
        if(socket !=tcpScoket)
        {
            size += socket->write(data);
            ui->label_3->setText(QString("共转发成功%1字节数据").arg(size));
        }
    }
}
