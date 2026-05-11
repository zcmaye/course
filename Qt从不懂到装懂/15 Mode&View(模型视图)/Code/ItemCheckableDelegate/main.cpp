#include<QApplication>
#include<QWidget>
#include<QIcon>
#include <QTableView>
#include <QScrollBar>
#include <QScroller>
#include <QStandardItemModel>
#include <QHeaderView>
#include "SItemCheckDelegate.h"
class Widget : public QTableView
{
	Q_OBJECT
public:
	Widget(QWidget* parent = nullptr)
		:QTableView(parent)
	{
		resize(250, 150);
		setWindowTitle("QToolButton");
		setWindowIcon(QIcon("icon.jpg"));
		initUI();
	}
	void initUI()
	{
		//this->setStyleSheet(strStyle);

		m_Model = new QStandardItemModel();
		m_Model->setColumnCount(4);
		m_Model->setHeaderData(0, Qt::Horizontal, "序号");
		m_Model->setHeaderData(1, Qt::Horizontal, "文件编号");
		m_Model->setHeaderData(2, Qt::Horizontal, "文件描述");
		m_Model->setHeaderData(3, Qt::Horizontal, "选择");

		//最后一列用
		SItemCheckDelegate* pDelegate = new SItemCheckDelegate;
		connect(pDelegate, &SItemCheckDelegate::signalClicked, this, [=](const QModelIndex& index) {
			bool bVal = m_Model->data(index).toBool();
		m_Model->setData(index, !bVal);
			});
		this->setItemDelegateForColumn(0, pDelegate);
		//this->setItemDelegate(pDelegate);
		this->setModel(m_Model);

		m_Model->setRowCount(20);
		for (int i = 0; i < 20; i++)
		{
			QStandardItem* item = nullptr;
			//QStandardItem* item = new QStandardItem(QString("%1").arg(i + 1));
			////item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
			//m_Model->setItem(i, 0, item);

			item = new QStandardItem("b123456789");
			//item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			m_Model->setItem(i, 1, item);

			item = new QStandardItem("谁动了我的奶酪");
			//item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			m_Model->setItem(i, 2, item);
		}
		//for (int i = 0; i < 20; i++)
		//    this->setRowHeight(i, 110);

		//this->setColumnWidth(0, 180);
		//this->setColumnWidth(1, 450);
		//this->setColumnWidth(2, 930);
		//this->setColumnWidth(3, 150);

		this->verticalHeader()->hide();
		//this->horizontalHeader()->setStretchLastSection(true); //最后一列充满表格
		this->setShowGrid(false); //隐藏网格
		this->setAlternatingRowColors(true);
		this->setSelectionBehavior(QAbstractItemView::SelectRows);
		this->horizontalHeader()->setHighlightSections(false);
		this->setEditTriggers(QAbstractItemView::NoEditTriggers);

		//不使用滚动条，使可拖拽下拉
		QScroller* sroller = QScroller::scroller(this);
		sroller->grabGesture(this, QScroller::LeftMouseButtonGesture);
		QScrollerProperties properties = sroller->scrollerProperties();
		properties.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0);
		properties.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0);
		sroller->setScrollerProperties(properties);

	}

	QStandardItemModel* m_Model;
};

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Widget w;
	w.show();

	return a.exec();
}

#include "main.moc"