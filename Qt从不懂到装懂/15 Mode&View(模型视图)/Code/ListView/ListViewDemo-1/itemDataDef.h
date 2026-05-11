#pragma once

#include<QMetaType>
enum ItemStatus
{
	S_Red,
	S_Blue,
	S_Yellow
};
Q_DECLARE_METATYPE(ItemStatus)
struct ItemData
{
	ItemData();
	QString name;
	QString tel;
	/*想要拖动项，必须重载QDataStream输入输出，并在构造函数中注册*/
	friend QDataStream& operator<<(QDataStream& out, const ItemData& myObj);
	friend QDataStream& operator>>(QDataStream& in, ItemData& myObj);
};
Q_DECLARE_METATYPE(ItemData)


