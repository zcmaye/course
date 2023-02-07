#include "ContactsInfo.h"
#include <QDebug>
#include <qrandom.h>
ContactsInfo::ContactsInfo(const QString& username, const QString& signature, const QPixmap& profile)
	:username_(username)
	,signature_(signature)
	,profile_(profile)
	,vipType_(VIPType(QRandomGenerator::global()->bounded(0,3)))
{
	qInfo() << "viptype" << vipType_;
}

QDebug operator<<(QDebug out, const ContactsInfo& info)
{
	out << "name:" << info.username_ << "sigature:" << info.signature_;
	return out;
}
