#include "SItemCheckDelegate.h"

#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>

SItemCheckDelegate::SItemCheckDelegate(QWidget* parent) :
    QStyledItemDelegate(parent)
{
}

void SItemCheckDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
     bool bChecked = index.data().toBool();
     QPixmap pixmap;
     QRect rect = option.rect;
     QPoint pt = rect.center();

     QStyleOptionButton cbxOpt;
     cbxOpt.rect = QRect(option.rect.x() + 20, option.rect.y(), option.rect.width(), option.rect.height()); //option.rect;
     if (bChecked)
     {
         cbxOpt.state = option.state | QStyle::State_On;
     }
     else
     {
         cbxOpt.state = option.state | QStyle::State_Off;
     }
     qApp->style()->drawControl(QStyle::CE_CheckBox, &cbxOpt, painter);
}

bool SItemCheckDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    QRect rect = option.rect;
    if (event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent* ev = static_cast<QMouseEvent*>(event);
        if (rect.contains(ev->pos()))
            emit signalClicked(index);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}