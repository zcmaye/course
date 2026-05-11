#include "SContactsItemDelegate.h"
#include <QDebug>
#include <QPainter>
#include "ContactsInfo.h"
#include <QHoverEvent>
#include <QAbstractItemView>
SContactsItemDelegate::SContactsItemDelegate(QObject* parent)
	:SItemDelegate(parent)
{
}

SContactsItemDelegate::~SContactsItemDelegate()
{
}

int SContactsItemDelegate::itemRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	m_mousePos = pos;
	//获取用户数据
	auto info = index.data(Qt::UserRole + 1).value<ContactsInfo*>();
	if (!info)
		return -1;

	int spacing = 5;
	QRect profileRect = { option.rect.x(),option.rect.y() + (option.rect.height() - 42) / 2,42,42 };
	if (profileRect.contains(pos))
	{
		//qInfo() << "m_profileRect" << profileRect << pos << profileRect.contains(pos);
		return ContactsInfo::InfoRole::ProfileRole;
	}
	int nameTextHeight = option.fontMetrics.height();
	int nameTextWidth = option.fontMetrics.horizontalAdvance(info->username_);
	QRect usernameRect = { profileRect.right() + spacing, profileRect.y() ,nameTextWidth,nameTextHeight };
	if (usernameRect.contains(pos))
	{

		return ContactsInfo::InfoRole::UsernameRole;
	}
	QRect vipRect = { usernameRect.x() + nameTextWidth + spacing, usernameRect.y(),28,10 };
	//qInfo() << "vipRect" << vipRect << pos << vipRect.contains(pos);
	if (vipRect.contains(pos))
	{

		return ContactsInfo::InfoRole::VipRole;
	}

	QRect signatureRect = { profileRect.right() + spacing, usernameRect.y() + spacing + nameTextHeight ,option.fontMetrics.horizontalAdvance(info->signature_),nameTextHeight };
	if (signatureRect.contains(pos))
	{
		return ContactsInfo::InfoRole::SignatureRole;
	}
	return -1;
}

void SContactsItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	//背景颜色，选中颜色，交给父亲处理
	//QStyledItemDelegate::paint(painter, option, index);

	if (option.state.testFlag(QStyle::StateFlag::State_MouseOver))
	{
		painter->fillRect(option.rect, QColor(242, 242, 242));
	}

	if (option.state.testFlag(QStyle::StateFlag::State_Selected))
	{
		painter->fillRect(option.rect, QColor(235, 235, 235));

	}

	//获取用户数据
	auto info = index.data(Qt::UserRole + 1).value<ContactsInfo*>();
	if (!info)
		return;

	int spacing = 5;
	painter->save();
	//绘制头像
	//qInfo() << option.rect.x()<< option.rect.y() << m_hoverPos;
	m_profileRect = { option.rect.x(),option.rect.y() + (option.rect.height() - 42) / 2,42,42 };
	painter->drawPixmap(m_profileRect, info->profile_);

	//绘制名字
	int nameTextHeight = painter->fontMetrics().height();
	int nameTextWidth = painter->fontMetrics().horizontalAdvance(info->username_);
	m_usernameRect = { m_profileRect.right() + spacing, m_profileRect.y() ,nameTextWidth,nameTextHeight };
	painter->drawText(m_usernameRect, info->username_);
	//painter->drawRect(m_usernameRect);

	//绘制vip
	QPixmap pix;
	switch (info->vipType_)
	{
	case ContactsInfo::NoVIP:
		break;
	case ContactsInfo::VIP:
		pix = QPixmap(":/ContactsAssets/images/vip.png");
		break;
	case ContactsInfo::SVIP:
		pix = QPixmap(":/ContactsAssets/images/svip.png");
		break;
	}
	m_vipRect = { m_usernameRect.x() + nameTextWidth + spacing, m_usernameRect.y(),pix.width(),pix.height()};
	painter->drawPixmap(m_vipRect, pix);
	//qInfo() << index.data(MousePosRole);
	if (m_vipRect.contains(m_mousePos))
	{
		painter->setPen(Qt::GlobalColor::red);
		painter->drawRect(m_vipRect.adjusted(0,-1,0,1));
	}

	//绘制签名
	painter->setPen(QColor(132, 132, 132));
	m_signatureRect = { m_profileRect.right() + spacing, m_usernameRect.y() + spacing +nameTextHeight ,painter->fontMetrics().horizontalAdvance(info->signature_),nameTextHeight };
	painter->drawText(m_signatureRect, info->signature_);
	//painter->drawRect(m_signatureRect);
	painter->restore();

	//QStyledItemDelegate::paint(painter, option, index);
}

QSize SContactsItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(option.widget->width(), 60);
}

