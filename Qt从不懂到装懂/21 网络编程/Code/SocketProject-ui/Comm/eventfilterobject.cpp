#include "eventfilterobject.h"
#include<QMouseEvent>
#include<QWidget>
#include<QGraphicsDropShadowEffect>
eventFilterObject::eventFilterObject(QObject *parent) : QObject(parent)
{
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setColor(QColor(112,112,112));
    shadow->setOffset(0);
    shadow->setBlurRadius(10);

    static_cast<QWidget*>(parent)->setGraphicsEffect(shadow);
}

bool eventFilterObject::eventFilter(QObject *watched, QEvent *ev)
{
    auto* mouseEv = static_cast<QMouseEvent*>(ev);
    static QPoint dis;
    if(ev->type() == QEvent::MouseButtonPress)
    {
        dis = mouseEv->pos();
    }
    else if(ev->type() == QEvent::MouseMove && mouseEv->buttons()&Qt::LeftButton
            && !dis.isNull())
    {
        auto *pthis = static_cast<QWidget*>(watched);
        //if(pthis->parent()==nullptr)
        pthis->move(mouseEv->globalPos() - dis);
        //pthis->move(pthis->mapToParent(mouseEv->pos()) - dis);
    }
    else if(ev->type() == QEvent::MouseButtonRelease)
    {
        dis = QPoint();
    }
    return false;
}
