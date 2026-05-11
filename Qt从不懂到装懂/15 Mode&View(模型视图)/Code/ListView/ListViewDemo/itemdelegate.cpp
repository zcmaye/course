#include "itemdelegate.h"
#include<QPainter>
#include"itemDataDef.h"
#include<QDebug>
ItemDelegate::ItemDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

ItemDelegate::~ItemDelegate()
{
}

void ItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (!index.isValid())
		return;
	painter->save();
	//项矩形
	QRect rect(option.rect.adjusted(0,0,-1,-1));
	//画圆角矩形,绘制选中、鼠标悬停和正常样式
	if (option.state & QStyle::State_Selected)	
	{
		painter->setPen(Qt::blue);
		painter->setBrush(QColor(229, 241, 255));
	}
	else if (option.state & QStyle::State_MouseOver)
	{
		painter->setPen(Qt::green);
	}
	else
	{
		painter->setPen(Qt::black);
	}
	
	painter->drawRoundedRect(rect, 5, 5);
	//绘制数据
	QRect nameRect(rect.x()+10, rect.top()+10, rect.width()-30,20);
	QRect telRect(rect.x() + 10, rect.bottom() - 25, rect.width() - 10, 20);
	ItemData itemData = index.data(Qt::UserRole + 1).value<ItemData>();
	//绘制name
	painter->setPen(Qt::black);
	painter->setFont(QFont("Times", 12,QFont::Bold));
	painter->drawText(nameRect, itemData.name);
	//绘制tel
	painter->setPen(Qt::gray);
	painter->setFont(QFont("Times", 10));
	painter->drawText(telRect, itemData.tel);

	painter->restore();
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(160,60);
}
