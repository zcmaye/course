///////////////////////////////////////////
//*  @file    eventfilterobject.h
//*  @date    2021/10/02 23:16
//*  @brief   过滤器对象(窗口拖动)
//*
//*  @author  Maye(顽石老师)
//*  @contact zcmaye@gmail.com
//*  @微信公众号 C语言Plus
///////////////////////////////////////////
#ifndef EVENTFILTEROBJECT_H
#define EVENTFILTEROBJECT_H

#include <QObject>

class eventFilterObject : public QObject
{
    Q_OBJECT
public:
    explicit eventFilterObject(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:

};

#endif // EVENTFILTEROBJECT_H
