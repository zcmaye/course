#ifndef SCONTACTSITEMDELEGATE_H_
#define SCONTACTSITEMDELEGATE_H_
#include "SCustomWidgets/SItemDelegate.h"

class SContactsItemDelegate : public SItemDelegate
{
	Q_OBJECT
public:
	explicit SContactsItemDelegate(QObject* parent = nullptr);
	~SContactsItemDelegate();

protected:
	int itemRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index)const;

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
private:
	mutable QPoint m_mousePos;
	mutable QRect m_profileRect;
	mutable QRect m_usernameRect;
	mutable QRect m_vipRect;
	mutable QRect m_signatureRect;

};
#endif // !SCONTACTSITEMDELEGATE_H_
