#include "SListView.h"

#include <QStandardItemModel>
#include <QEvent>
#include <QMouseEvent>
#include "SItemDelegate.h"
#include <QCursor>

SListView::SListView(QWidget* parent)
	:QListView(parent)
{

}

bool SListView::viewportEvent(QEvent* ev)
{
	QModelIndex index = indexAt(viewport()->mapFromGlobal(QCursor::pos()));
	//必须要有item
	if (index.isValid() &&	
		//只关心鼠标悬停和鼠标点击事件
		(ev->type() == QEvent::HoverMove || ev->type() == QEvent::MouseButtonPress))
	{
		QStyleOptionViewItem option;
		option.initFrom(this);
		option.widget = this;
		option.rect = visualRect(index);
		option.text = index.data().toString();
		option.state.setFlag(index == currentIndex() ? QStyle::StateFlag::State_Selected : QStyle::StateFlag::State_None);
		option.font = qobject_cast<QStandardItemModel*>(model())->itemFromIndex(index)->font();

		int role = -1;
		auto dgate = qobject_cast<SItemDelegate*>(itemDelegate());
		if (dgate)
		{
			//1,直接调用
			role = dgate->itemEvent(ev, option, index);
			//2,通过invokeMethod调用,注意:必须在被调用函数申明之前加上Q_INVOKABLE(如 Q_INVOKABLE int itemEvent(...);)
			//QMetaObject::invokeMethod(dgate, "itemEvent",
			//	Q_RETURN_ARG(int, role),
			//	Q_ARG(QEvent*, ev),
			//	Q_ARG(const QStyleOptionViewItem&, option),
			//	Q_ARG(const QModelIndex&, index));
		}
		if (ev->type() == QEvent::HoverMove)
		{
			emit hoveredRole(index, role);
			update(index);
		}		
		else if (ev->type() == QEvent::MouseButtonPress)
		{
			emit pressedRole(index, role);
			update(index);
		}		
	}
	return QListView::viewportEvent(ev);
}