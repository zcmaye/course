#include "SContactsItemDelegate.h"
#include <QDebug>
#include <QPainter>
#include "ContactsInfo.h"
#include <QHoverEvent>
#include <QAbstractItemView>
SContactsItemDelegate::SContactsItemDelegate(QObject* parent)
	:QStyledItemDelegate(parent)
{
}

SContactsItemDelegate::~SContactsItemDelegate()
{
}

void SContactsItemDelegate::hoverEvent(QHoverEvent* ev, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	m_hoverPos = ev->pos();
	//if (1)
	{
		//qInfo() << option.widget;
		auto w  = const_cast<QWidget*>(option.widget);
		auto view = qobject_cast<QAbstractItemView*>(w);
		view->update(index);
		
	}

	emit hovered(index, hoverRole(m_hoverPos, option, index));
}

void SContactsItemDelegate::pressEvent(QMouseEvent* ev, const QStyleOptionViewItem& option, const QModelIndex& index)
{
}

int SContactsItemDelegate::hoverRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	//qInfo() << m_profileRect << pos;
	//m_profileRect不能一直在paint中更新
	if (m_profileRect.contains(pos))
	{
		return ContactsInfo::InfoRole::ProfileRole;
	}
	if (m_usernameRect.contains(pos))
	{
		return ContactsInfo::InfoRole::UsernameRole;
	}
	if (m_vipRect.contains(pos))
	{
		return ContactsInfo::InfoRole::VipRole;
	}
	if (m_signatureRect.contains(pos))
	{
		return ContactsInfo::InfoRole::SignatureRole;
	}
	return -1;
}

int SContactsItemDelegate::pressRole(const QPoint& pos, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
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
	qInfo() << m_profileRect << m_hoverPos;
	painter->drawPixmap(m_profileRect, info->profile_);

	//绘制名字
	int nameTextHeight = painter->fontMetrics().height();
	int nameTextWidth = painter->fontMetrics().horizontalAdvance(info->username_);
	m_usernameRect = { m_profileRect.right() + spacing, m_profileRect.y() ,nameTextWidth,nameTextHeight };
	painter->drawText(m_usernameRect, info->username_);
	painter->drawRect(m_usernameRect);

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

	if (m_vipRect.contains(m_hoverPos))
	{
		painter->setPen(Qt::GlobalColor::red);
		painter->drawRect(m_vipRect.adjusted(0,-1,0,1));
	}

	//绘制签名
	painter->setPen(QColor(132, 132, 132));
	m_signatureRect = { m_profileRect.right() + spacing, m_usernameRect.y() + spacing +nameTextHeight ,painter->fontMetrics().horizontalAdvance(info->signature_),nameTextHeight };
	painter->drawText(m_signatureRect, info->signature_);
	painter->drawRect(m_signatureRect);
	painter->restore();

	//QStyledItemDelegate::paint(painter, option, index);
}

QSize SContactsItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	return QSize(option.widget->width(), 60);
}

