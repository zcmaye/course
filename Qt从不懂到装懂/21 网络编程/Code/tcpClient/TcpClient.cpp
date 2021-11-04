#include "TcpClient.h"
#include "ui_TcpClient.h"
#include<QFileDialog>
#include<QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnConnect_released()
{
    connect(m_tcpSocket,QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),this,&MainWindow::onError);
    connect(m_tcpSocket,&QTcpSocket::connected,this,&MainWindow::onConneted);
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&MainWindow::onReadyRead);  //读取数据

    //连接到服务器，填写服务器的IP地址和端口号
    m_tcpSocket->connectToHost(ui->editIp->text(),ui->editPort->text().toUShort());
    ui->btnConnect->setText("连接成功...");
}

void MainWindow::onError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<"client haserror"<<socketError<<m_tcpSocket->errorString();
}
void MainWindow::onConneted()
{

}

void MainWindow::onReadyRead()
{
    QDataStream stream(m_tcpSocket);
    if(m_msgType == Null)
    {
        //解包
        stream>>m_msgType;
        qDebug()<<"msgRead"<<m_msgType;
    }
    if(m_msgType == Text)
    {
        QByteArray data;
        stream>>data;
        ui->textBrowser->append(data);
        m_msgType = Null;
    }
    else
    {
        if(m_dataSize == 0) //刚开始结束数据
        {
            stream>>m_filename>>m_dataSize;
            m_localFile.setFileName(m_filename);
            if(!m_localFile.open(QIODevice::WriteOnly))
            {
                qWarning("文件打开失败~");
                return;
            }
            qDebug()<<"size size"<<m_filename<<m_dataSize;
            m_diaog = new QProgressDialog(this);
            m_diaog->setRange(0,m_dataSize);
            m_diaog->open();
        }
        else    //不断接受数据
        {
            QByteArray blockData = m_tcpSocket->readAll();
            m_recvSize += blockData.size(); //计算已经接受的大小
            m_localFile.write(blockData);
            m_localFile.flush();            //立即写入文件

            //qDebug()<<blockData.size()<<"/"<<m_dataSize<<"---"<<m_recvSize;
            m_diaog->setLabelText(QString("%1/%2").arg(m_recvSize).arg(m_dataSize));
            m_diaog->setValue(m_recvSize);

        }
        //接受完毕退出
        if(m_recvSize >= m_dataSize)
        {

            m_dataSize = 0;
            m_recvSize = 0;
            m_localFile.close();
            m_msgType = Null;

            m_diaog->deleteLater();
            qDebug()<<"传输完成。。。";
            image(m_filename);
            m_filename.clear();
        }
    }
}


void MainWindow::on_btnDisConnect_released()
{
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
    ui->btnConnect->setText("连接服务器");
}

void MainWindow::on_btnSend_released()
{
    QByteArray resData;
    QDataStream stream(&resData,QIODevice::WriteOnly);
    stream<<(quint8)Text<<ui->textEdit->toPlainText().toUtf8();

    m_tcpSocket->write(resData);
    ui->textBrowser->append("我：" + ui->textEdit->toPlainText());

    //清除输入框里面的文字
    ui->textEdit->clear();
}

void MainWindow::on_btnSendFile_released()
{
    QString filename =  QFileDialog::getOpenFileName(this,"选择文件","./");
    if(filename.isEmpty())
    {
        qWarning("请选择文件");
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    //文件名大小和文件名
    QByteArray fileName = QFileInfo(filename).fileName().toUtf8();
    quint8 msgtype = File;
    //数据的大小
    quint64 dataSize = file.size();
    //封装头部数据
    QByteArray headerData;
    QDataStream stream(&headerData,QIODevice::WriteOnly);
    stream<<(quint8)msgtype<<fileName<<dataSize;
    //发送
    m_tcpSocket->write(headerData);
    //发送内容(QDataStream 串行化的数据，必须用它再解析，因为对于字符串会在前面加上长度，所以单独发送内容)

    quint64 realSize =  m_tcpSocket->write(file.readAll());
    qDebug()<<"realSize"<<realSize<<dataSize;
}

void MainWindow::image(const QString &filename)
{
    static QStringList suffix = QStringList()<<"jpg"<<"png"<<"jpeg"<<"gif";
    if(!suffix.contains(QFileInfo(filename).suffix(),Qt::CaseSensitivity::CaseInsensitive))
    {
        return;
    }
    ui->textBrowser->insertHtml(QString("<img src=\"%1\">").arg(filename));
}
