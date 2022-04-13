#include "eventfilterobject.h"
#include<QMouseEvent>
#include<QWidget>
eventFilterObject::eventFilterObject(QObject *parent) : QObject(parent)
{

}

bool eventFilterObject::eventFilter(QObject *watched, QEvent *ev)
{
    auto* mouseEv = static_cast<QMouseEvent*>(ev);
    static QPoint dis;
    if(ev->type() == QEvent::MouseButtonPress)
    {
        dis = mouseEv->pos();
    }
    else if(ev->type() == QEvent::MouseMove && mouseEv->buttons()&Qt::LeftButton)
    {
        auto *pthis = static_cast<QWidget*>(watched);
        pthis->move(mouseEv->globalPos() - dis);
    }
    return false;
}
