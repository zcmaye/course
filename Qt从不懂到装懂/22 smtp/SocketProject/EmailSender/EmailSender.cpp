#include "EmailSender.h"
#include<QFileInfo>
EmailSender::EmailSender(QObject *parent)
    : QObject(parent)
    ,m_tcpSocket(new QTcpSocket(this))
{
    setHostInfo("smtp.qq.com",25);
}

EmailSender::~EmailSender()
{
    m_tcpSocket->disconnectFromHost();
    m_tcpSocket->close();
}

void EmailSender::setHostInfo(const QString &ip, quint16 port)
{
    //如果是stmp.qq.com这种格式，就解析成IP地址
    quint32 addr = QHostInfo::fromName(ip).addresses().first().toIPv4Address();
    m_hostAddr = QHostAddress(addr);
    m_port = port;
}

bool EmailSender::login(const QString &user, const QString &password)
{
    m_user = user;
    m_tcpSocket->connectToHost(m_hostAddr,m_port);
    if(!m_tcpSocket->waitForConnected())
        qWarning("连接到服务器失败");
    else    //成功需要读取一下服务器发送的消息
        qDebug()<<"welcome:"<<readMsg();



    //1，向服务器问好
    m_tcpSocket->write(QByteArray("EHLO ")+ user.toUtf8()+ "\r\n");
    qDebug()<<"EHLO:"<<readMsg();
    if(m_tcpSocket->error() == QTcpSocket::SocketError::RemoteHostClosedError)
    {
        qDebug()<<"false";
        return false;
    }

    //2,告诉服务器准备验证
    m_tcpSocket->write("AUTH LOGIN\r\n");
    qDebug()<<"AUTH LOGIN:"<<readMsg();

    //3,发送账号
    QByteArray cryptoUser = QByteArray(user.toUtf8()).toBase64();
    m_tcpSocket->write(cryptoUser+"\r\n");
    qDebug()<<"USER:"<<readMsg();

    //4，发送密码
    QByteArray cryptoPasswd = QByteArray(password.toUtf8()).toBase64();
    m_tcpSocket->write(cryptoPasswd+"\r\n");
    QByteArray data = readMsg();
    qDebug()<<"PassWord:"<<data;
    if(data.contains("235"))   //等待用户输入验证信息
    {
        return true;
    }
    return false;
}

void EmailSender::quit()
{
    m_tcpSocket->write("QUIT\r\n");
    qDebug()<<"QUIT:"<<readMsg();
}

void EmailSender::setBody(const QString &body)
{
    m_body = body;
}

void EmailSender::addAttachment(const QString &fileName)
{
    if(!fileName.isEmpty())
        m_attachList.push_back(fileName);
}

bool EmailSender::sendEmail()
{
    sendHeader();
    sendBody();
    sendAtachment();
    sendEnd();
    return true;
}

void EmailSender::setHeader(const QStringList &tolist, const QString &subject)
{
    m_tolist = tolist;
    m_subject = subject;
}

/*@内部函数*/
QByteArray EmailSender::readMsg()
{
    QByteArray data;
    if(m_tcpSocket->waitForReadyRead())
    {
        data = m_tcpSocket->readAll();
    }
    else
    {
        qDebug()<<"[Read No Data:]"<<m_tcpSocket->errorString();
    }
    return data;
}

bool EmailSender::sendHeader()
{
    m_tcpSocket->write("MAIL FROM:<" + m_user.toUtf8() +">\r\n");
    qDebug()<<"MAIL FROM:"<<readMsg();

    for(auto to : m_tolist) //给多个人发送邮件
    {
        m_tcpSocket->write("RCPT TO:<" + to.toUtf8() + ">\r\n");
        qDebug()<<"RCPT TO:"<<readMsg();
    }

    m_tcpSocket->write("DATA\r\n");
    qDebug()<<"DATA:"<<readMsg();

    QString data;
    data += "From:"+ m_user.toUtf8() + "\r\n";
    data += "To:" + m_tolist.first().toUtf8() + "\r\n";
    data += "Subject:"+ m_subject.toUtf8() +"\r\n";
    data += "MINE-Version:1.0\r\n";
    data += "Content-Type:multipart/mixed;charset=\"utf-8\";boundary=maye\r\n";
    data += "\r\n";

    m_tcpSocket->write(data.toUtf8());

    return true;
}

bool EmailSender::sendBody()
{
    QByteArray data = "--maye\r\n";
    data += "Content-Type:text/html;charset=\"utf-8\"\r\n\r\n";
    data += m_body.toUtf8();
    data += "\r\n\r\n";
    m_tcpSocket->write(data);

    return true;
}

bool EmailSender::sendEnd()
{
    QByteArray data = "--maye--\r\n.\r\n";
    m_tcpSocket->write(data);
    qDebug()<<"sendEnd:"<< readMsg();
    return true;
}

bool EmailSender::sendAtachment()
{
    for(QString filename : m_attachList)
    {
        //没有路径的文件名
        QString name = QFileInfo(filename).fileName();

        QByteArray data = "--maye\r\n";
        data += "Content-Type:application/octet-stream;\r\n";
        //data += QString(" name=%1\r\n").arg(name).toUtf8();//name前面必须要有空格
        data += "Content-Transfer-Encoding:base64\r\n";
        data += QString("Content-Disposition:attachment;filename=%1\r\n").arg(name);
        //data += QString("filename=%1\r\n").arg(name).toUtf8();
        data += "\r\n";
        m_tcpSocket->write(data);

        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
            qWarning("有文件打开失败");
            continue;
        }
        //分块发
        while(!file.atEnd())
        {
            QByteArray content = file.read(100*1024*1024).toBase64();
            content += "\r\n";
            m_tcpSocket->write(content);
        }
        file.close();
    }
    return true;
}
