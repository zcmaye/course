#include"itemDataDef.h"



ItemData::ItemData()
{
	qRegisterMetaTypeStreamOperators<ItemData>("ItemData");
}
QDataStream& operator<<(QDataStream& out, const ItemData& myObj)
{
	out << myObj.name << myObj.tel;
	return out;
}

QDataStream& operator>>(QDataStream& in, ItemData& myObj)
{
	in >> myObj.name >> myObj.tel;
	return in;
}


