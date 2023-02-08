#ifndef SITEMDELEGATE_H_
#define SITEMDELEGATE_H_
#include <QStyledItemDelegate>

class SItemDelegate
	: public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit SItemDelegate(QObject* parent = nullptr);
	~SItemDelegate();

	/**  
	* 处理item事件，默认只处理hoverMove和mouseButtonPress
	* @param ev 事件指针
	* @param option item的选项信息
	* @param index 鼠标所在的item
	*/
	Q_INVOKABLE virtual int itemEvent(QEvent* ev, const QStyleOptionViewItem& option, const QModelIndex& index);
protected:
	/** 
	* 获取指定位置的角色ID，由用户实现
	* @param pos 鼠标在视图上的坐标
	* @param option item的选项信息
	* @param index 鼠标所在的item
	*/
	virtual int itemRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index)const;

};
#endif // !SITEMDELEGATE_H_
