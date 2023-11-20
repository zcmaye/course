#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mythread.h"
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:

    void closeThread();


    void recvImage(QImage temp);

protected:
    //绘图事件，所有绘图操作都在这里面
    void paintEvent(QPaintEvent *event);
private:
    Ui::Widget *ui;
    QImage      image;
    QThread*    pThread;
    MyThread*   pMyThread;

};
#endif // WIDGET_H
