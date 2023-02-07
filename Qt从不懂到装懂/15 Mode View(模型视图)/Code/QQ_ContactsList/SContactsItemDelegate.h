#ifndef SCONTACTSITEMDELEGATE_H_
#define SCONTACTSITEMDELEGATE_H_
#include <QStyledItemDelegate>

class SContactsItemDelegate :public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit SContactsItemDelegate(QObject* parent = nullptr);
	~SContactsItemDelegate();

	/**
	* 自定义的虚函数，由上层View调用
	*/
	virtual void hoverEvent(QHoverEvent* ev, const QStyleOptionViewItem& option, const QModelIndex& index);
	virtual void pressEvent(QMouseEvent* ev, const QStyleOptionViewItem& option, const QModelIndex& index);
	virtual int hoverRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index)const;
	virtual int pressRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index)const;
protected:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
signals:
	void hovered(const QModelIndex& index,int role);
private:
	QPoint m_hoverPos;
	mutable QRect m_profileRect;
	mutable QRect m_usernameRect;
	mutable QRect m_vipRect;
	mutable QRect m_signatureRect;
};
#endif // !SCONTACTSITEMDELEGATE_H_
