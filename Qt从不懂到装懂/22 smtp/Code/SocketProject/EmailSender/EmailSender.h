#ifndef EMAILSENDER_H
#define EMAILSENDER_H

#include <QObject>
#include<QTcpSocket>
#include<QHostAddress>
#include<QHostInfo>

#define mcout qDebug()<<"[Read No Data"<<__LINE__<<"]"

class EmailSender : public QObject
{
    Q_OBJECT
public:
    explicit EmailSender(QObject *parent = nullptr);
    ~EmailSender();
    void setHostInfo(const QString& ip,quint16 port);
    bool login(const QString&user,const QString&password);  //登录
    void quit();                                            //退出
    void setHeader(const QString& to,const QString& subject);   //设置头部数据
    void setBody(const QString& body);
    void addAttr(const QStringList& list);                      //添加附件
    void sendEmail();                                           //发送邮件
signals:
private:
    void sendHeader();                                          //发送头部数据
    void sendBody();
    void sendAttr();
    void sendEnd();                                             //发送完毕

    QByteArray readMsg();
private:
    QHostAddress m_addr;
    quint16 m_port;
    QTcpSocket *m_tcpSocket;

    QString m_from;             //发件人
    QStringList m_tolist;       //收件人
    QString m_subject;          //邮件主题

    QString m_body;             //主题部分

    QStringList m_attlist;      //附件
};

#endif // EMAILSENDER_H
