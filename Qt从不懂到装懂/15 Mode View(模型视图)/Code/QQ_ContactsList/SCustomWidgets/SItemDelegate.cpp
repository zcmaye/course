#include "SItemDelegate.h"
#include <QHoverEvent>
SItemDelegate::SItemDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{
}

SItemDelegate::~SItemDelegate()
{
}

int SItemDelegate::itemEvent(QEvent* ev, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	if (ev->type() == QEvent::Type::HoverMove || ev->type() == QEvent::Type::MouseButtonPress)
	{
		QSinglePointEvent* spe = static_cast<QSinglePointEvent*>(ev);
		return itemRole(spe->position().toPoint(), option, index);
	}
	return -1;
}

int SItemDelegate::itemRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return -1;
}



