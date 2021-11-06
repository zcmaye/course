#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QObject>
#include<QTcpSocket>
#include<QHostAddress>
#include<QHostInfo>
class EmailSender : public QObject
{
    Q_OBJECT
public:
    explicit EmailSender(QObject *parent = nullptr);
    ~EmailSender();
    void setHostInfo(const QString& ip,quint16 port);           //设置右键服务器名和端口号
    bool login(const QString&user,const QString&password);      //使用指定的账号和密码登录服务器
    void quit();                                                //退出登录
    void setHeader(const QStringList& tolist,const QString&subject);    //设置右键首部信息(接收人，邮件主题)
    void setBody(const QString&body);               //设置邮件主体（正文）
    void addAttachment(const QString& fileName);    //添加附件
    bool sendEmail();
private:
    QByteArray readMsg();
    bool sendHeader();  //发送首部数据
    bool sendBody();    //发送正文
    bool sendEnd();     //邮件发送完毕
    bool sendAtachment();//发送附件
private:
    QHostAddress m_hostAddr;    //服务器地址
    quint16 m_port;             //服务器端口号
    QTcpSocket *m_tcpSocket;

    QString     m_user;         //用户名

    QStringList m_tolist;       //收件人
    QString     m_subject;      //主题
    QString     m_body;         //主体
    QStringList m_attachList;   //附件

};

#endif // EMAILSENDER_H
