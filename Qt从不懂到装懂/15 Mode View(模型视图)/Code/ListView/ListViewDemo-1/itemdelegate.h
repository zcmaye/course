#pragma once

#include<QStyledItemDelegate>
class ItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	ItemDelegate(QObject *parent = nullptr);
	~ItemDelegate();

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const override;

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

};
