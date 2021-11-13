#include "mythread.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

//线程函数  绘图
void MyThread::drawImage(){
    //1 QImage设备
    QImage image(600,600,QImage::Format_ARGB32);

    //2 画家
    QPainter p(&image);
//    p.begin(&image);
    //3 画笔，画刷
    QPen    pen;
    pen.setWidth(3);
    p.setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::Dense6Pattern);

    p.setBrush(brush);

    //4 点
    QPoint pos[6] = {
        QPoint(qrand()%600,qrand()%600),QPoint(qrand()%600,qrand()%600),
        QPoint(qrand()%600,qrand()%600),QPoint(qrand()%600,qrand()%600),
        QPoint(qrand()%600,qrand()%600),QPoint(qrand()%600,qrand()%600)
    };
    //5 绘制QImage
    p.drawPolygon(pos,6);
    static int i = 0;
    i++;
    qDebug() << "分支线程被调用:"<<i;

//    p.end();
    //6 发送信号
    emit sendImage(image);
}
