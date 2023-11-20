#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QDebug>
#include <QImage>
#include <QPainter>

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    //线程函数  绘图
    void drawImage();


signals:
    //把分支线程中绘制好的图片  发送给 主线程
    void sendImage(QImage image);
};

#endif // MYTHREAD_H
