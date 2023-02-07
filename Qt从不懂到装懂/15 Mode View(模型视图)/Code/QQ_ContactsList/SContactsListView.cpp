#include "SContactsListView.h"

#include <QStandardItemModel>
#include <QEvent>
#include <QMouseEvent>

#include "SContactsItemDelegate.h"
#include "ContactsInfo.h"

SContactsListView::SContactsListView(QWidget* parent)
	:QListView(parent)
	, m_model(new QStandardItemModel(this))
{
	
	init();
}

void SContactsListView::init()
{
	auto dgate = new SContactsItemDelegate(this);
	setItemDelegate(dgate);
	setModel(m_model);

	//准备联系人信息
	m_infos.append(new ContactsInfo("十一期 暮念"));
	m_infos.append(new ContactsInfo("十一期 江涛", "面包会有的，一切都会有的"));
	m_infos.append(new ContactsInfo("爵士", "嗦粉去"));
	m_infos.append(new ContactsInfo("宁静之湖", "我是我是无敌无敌的小可爱"));

	//创建item
	for (auto info : m_infos)
	{
		auto item = new QStandardItem(info->username_);
		item->setData(QVariant::fromValue(info));
		m_model->appendRow(item);

	}
	connect(dgate, &SContactsItemDelegate::hovered, this, [=](const QModelIndex& index,int role)
		{
			if (!index.isValid())
				return;
			qInfo() << index << role;
			ContactsInfo* info = index.data(Qt::UserRole + 1).value<ContactsInfo*>();
			QString toolTipStr;
			switch (role)
			{
			case ContactsInfo::ProfileRole:
				toolTipStr ="我是头像啦！";
				break;
			case ContactsInfo::UsernameRole:
				toolTipStr = info->username_, Qt::ToolTipRole;
				break;
			case ContactsInfo::VipRole:
				if (info->vipType_ != ContactsInfo::NoVIP)
				{
					toolTipStr = info->vipType_ == ContactsInfo::VIP ? "会员身份铭牌" : "超级会员身份铭牌";
				}
				break;
			case ContactsInfo::SignatureRole:
				toolTipStr = info->signature_;
				break;
			default:
				toolTipStr = "??";
				break;
			}
			m_model->itemFromIndex(index)->setData(toolTipStr, Qt::ToolTipRole);
		});
}

bool SContactsListView::viewportEvent(QEvent* ev)
{
	//qInfo() << ev->type()<<viewportSizeHint();

	if (ev->type() == QEvent::HoverMove)
	{
		//qInfo() << static_cast<QHoverEvent*>(ev)->pos();		
		auto hoverEv = static_cast<QHoverEvent*>(ev);
		QModelIndex index = indexAt(hoverEv->pos());
		if (index.isValid())
		{
			QStyleOptionViewItem option;
			option.initFrom(this);
			option.widget = this;
			option.rect = visualRect(index);
			option.text = index.data().toString();
			option.state.setFlag(index == currentIndex() ? QStyle::StateFlag::State_Selected : QStyle::StateFlag::State_None);

			//qInfo() << option.rect << option.text << option.state;

			static_cast<SContactsItemDelegate*>(itemDelegate())->hoverEvent(hoverEv, option, index);


		}
	}
	return QListView::viewportEvent(ev);
}
