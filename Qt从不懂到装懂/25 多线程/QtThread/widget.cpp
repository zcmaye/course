#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //创建线程对象
    pThread = new QThread(this);
    pMyThread = new MyThread;
    //添加线程对象
    pMyThread->moveToThread(pThread);
    //启动线程
    pThread->start();
    //每当按下按钮，就启动线程函数
    connect(ui->pushButton,&QPushButton::pressed,
            pMyThread,&MyThread::drawImage);


    //结束线程对象
    connect(this,&QWidget::destroyed,this,&Widget::closeThread);

    //把分支线程发送过来的QImage显示到窗口上，刷新界面
    connect(pMyThread,&MyThread::sendImage,this,&Widget::recvImage);
}
void Widget::recvImage(QImage temp){
    image = temp;
    update();//刷新界面
}

//绘图事件，所有绘图操作都在这里面
void Widget::paintEvent(QPaintEvent *event){
    QPainter p(this);

    p.drawImage(40,40,image);
}

void Widget::closeThread(){
    pThread->quit();
    pThread->wait();
    delete pMyThread;
}
Widget::~Widget()
{
    delete ui;
}

