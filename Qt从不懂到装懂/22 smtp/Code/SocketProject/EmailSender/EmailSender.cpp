#include "EmailSender.h"
#include<QFileInfo>
#define CR "\r\n"
EmailSender::EmailSender(QObject *parent)
    : QObject(parent)
    ,m_tcpSocket(new QTcpSocket(this))
{

}

EmailSender::~EmailSender()
{
    quit();
}

void EmailSender::setHostInfo(const QString &ip, quint16 port)
{
    auto list = QHostInfo::fromName(ip).addresses();
    if(list.isEmpty())
    {
        qWarning("没有找到对应的服务器");
        return;
    }
    m_addr  = list.first();
    m_port = port;
}

bool EmailSender::login(const QString &user, const QString &password)
{
    m_from = user;
    //smtp.qq.com ->ip地址
    m_tcpSocket->connectToHost(m_addr,m_port);
    if(!m_tcpSocket->waitForConnected())
        qWarning("连接到服务器失败");
    else
    {
        mcout<< readMsg() <<m_tcpSocket->state();
    }
    //buzkrfdyittjbcda   YnV6a3JmZHlpdHRqYmNkYQ==
    //825943234@qq.com   ODI1OTQzMjM0QHFxLmNvbQ==
    //1,打个招呼
    m_tcpSocket->write("EHLO " + user.toUtf8() + "\r\n");
    mcout<<readMsg();

    //2,选择登录方式
    m_tcpSocket->write("AUTH LOGIN\r\n");
    mcout<<readMsg();

    //3,发送账号,需要使用base64加密
    QByteArray cryptoUser = user.toUtf8().toBase64();
    m_tcpSocket->write(cryptoUser+"\r\n");
    mcout<<readMsg();

    //4,发送密码,需要使用base64加密
    m_tcpSocket->write(password.toUtf8().toBase64() + "\r\n");
    auto data = readMsg();
    if(data.contains("235"))
    {
        mcout<<data;
        return true;    //登录成功
    }
    return false;
}

void EmailSender::quit()
{
    m_tcpSocket->write("QUIT\r\n");
    mcout<<readMsg();
}

void EmailSender::setHeader(const QString &to, const QString &subject)
{
    m_tolist = to.split(";");
    m_subject = subject;
}

void EmailSender::setBody(const QString &body)
{
    m_body = body;
}

void EmailSender::addAttr(const QStringList &list)
{
    m_attlist.append(list);
}

void EmailSender::sendEmail()
{
    sendHeader();
    sendBody();
    sendAttr();
    sendEnd();
}

void EmailSender::sendHeader()
{
    //发送人
    m_tcpSocket->write("MAIL FROM:<" + m_from.toUtf8() + ">\r\n");
    mcout<<readMsg();

    //多个接收人
    for(auto to : m_tolist)
    {
        m_tcpSocket->write("RCPT TO:<" + to.toUtf8() + ">\r\n");
        mcout<<readMsg();
    }

    //告诉服务器开始发送数据
    m_tcpSocket->write("DATA\r\n");
    mcout<<readMsg();

    QByteArray data;
    data += "From:"+m_from.toUtf8()+"\r\n";
    data += "To:"+m_tolist.first().toUtf8()+"\r\n";
    data += "Subject:"+m_subject.toUtf8()+"\r\n";
    data += "MINE-Version:1.0\r\n";
    data += "Content-Type:multipart/mixed;charset=\"utf-8\";boundary=maye\r\n\r\n"; //定义整个邮件的格式
    m_tcpSocket->write(data);   //发送

}

void EmailSender::sendBody()
{
    QByteArray data = "--maye\r\n"; //数据开始
    data += "Content-Type:text/html\r\n\r\n";
    data += m_body.toUtf8();
    data += "\r\n\r\n";
    m_tcpSocket->write(data);
    //mcout<<readMsg();
}

void EmailSender::sendAttr()
{
    qDebug()<<m_attlist;
    for(QString filename : m_attlist)
    {
        QByteArray data = "--maye\r\n";
        data += "Content-Type:application/octet-stream;\r\n";
        data += "Content-Transfer-Encoding:base64\r\n";
        data += "Content-Disposition:attachment;filename="+QFileInfo(filename).fileName()+ "\r\n\r\n";


        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
            qWarning("文件打开失败");
            continue;
        }
        m_tcpSocket->write(data);   //打开成功发送mime字段
        mcout<<"send file";
        m_tcpSocket->write(file.readAll().toBase64()+"\r\n\r\n");
        mcout<<"send file end";
        //分块发送
//        while (!file.atEnd())
//        {
//             //m_tcpSocket->write(file.read(1024*1024*100).toBase64() + "\r\n");
//        }
    }
}

void EmailSender::sendEnd()
{
    m_tcpSocket->write("--maye--\r\n.\r\n");
    mcout<<"sendend";
    mcout<<readMsg();
    mcout<<"sendend .....";
}

QByteArray EmailSender::readMsg()
{
    QByteArray data;
    if(m_tcpSocket->waitForReadyRead(3000))
        data = m_tcpSocket->readAll();
    else
        mcout<<m_tcpSocket->errorString();
    return data;
}
















