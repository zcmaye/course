#include "mainwindow.h"

#include<QVariant>
#include"itemdelegate.h"
#include<QDebug>
#include<QHBoxLayout>
#include<QRandomGenerator>
#include<QContextMenuEvent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(new QWidget)
    , m_listView(new QListView(this))
    , m_model(new QStandardItemModel(this))
    , m_filterProxyModel(new QSortFilterProxyModel(this))

{
    this->resize(640, 480);
    this->setCentralWidget(m_centralWidget);
    //m_listView->setModel(m_model);
    m_filterProxyModel->setSourceModel(m_model);    //指定要过滤的模型
    m_filterProxyModel->setFilterRole(Qt::UserRole + 2);
    m_listView->setModel(m_filterProxyModel);

    m_listView->setItemDelegate(new ItemDelegate(this));
    m_listView->setSpacing(10);
    m_listView->setFrameStyle(QFrame::NoFrame);

    m_listView->setViewMode(QListView::IconMode);
    m_listView->setFlow(QListView::Flow::LeftToRight);          //设置流布局方向
    m_listView->setResizeMode(QListView::ResizeMode::Adjust);   //每次调整大小
   
   // m_listView->setDragEnabled(false);  //禁止拖动项
    //m_listView->setMovement(QListView::Movement::Snap);     //设置移动手段
    //m_listView->setGridSize(QSize(160+10, 60+10));          //设置移动对齐的格子大小

    m_listView->setSelectionMode(QListView::SelectionMode::MultiSelection); //设置选择模式->多选
    m_listView->setSelectionRectVisible(true);                              //设置是否显示选择矩形

    initData();   
    initBtn();
    updateNum();
    initLayout();

    initContextMenu();
    connect(m_listView, &QListView::pressed, this, [=](const QModelIndex& index)
        {
           // m_model->removeRow(0);
            //qDebug() << index<<"\n" << m_listView->currentIndex();
        });
}

void MainWindow::initData()
{
    for (size_t i = 0; i < 10; i++)
    {
        QStandardItem* item = new QStandardItem;
        ItemData itemData;
        itemData.name = QString("Name %1").arg(i);
        itemData.tel = QString("Tel:13123416991");
        //生成状态
        ItemStatus itemStatus = (ItemStatus)QRandomGenerator::global()->bounded(0, 3);
        switch (itemStatus)
        {
        case S_Red:
            ++redNum;
            break;
        case S_Blue:
            ++blueNum;
            break;
        case S_Yellow:
            ++yellowNum;
            break;
        }

        item->setData(QVariant::fromValue(itemData), Qt::UserRole + 1);
        item->setData(itemStatus, Qt::UserRole + 2);
        m_model->appendRow(item);
    }
}

void MainWindow::initBtn()
{
    m_allBtn = new QPushButton;
    m_allBtn->setCheckable(true);
    m_allBtn->setChecked(true);
    m_allBtn->setText("All");

    m_redBtn = new QPushButton;
    m_redBtn->setCheckable(true);
    m_redBtn->setText("Red");

    m_yellowBtn = new QPushButton;
    m_yellowBtn->setCheckable(true);
    m_yellowBtn->setText("Yellow");

    m_blueBtn = new QPushButton;
    m_blueBtn->setCheckable(true);
    m_blueBtn->setText("Blue");

    m_btnGroup = new QButtonGroup;
    m_btnGroup->setExclusive(true); 
    m_btnGroup->addButton(m_allBtn);
    m_btnGroup->addButton(m_redBtn);
    m_btnGroup->addButton(m_yellowBtn);
    m_btnGroup->addButton(m_blueBtn);

    this->setStyleSheet(".QWidget{background-color:white;}QPushButton{border-radius:5px;min-width:100;min-height:30;font:normal 16px \"楷体\";}QPushButton:hover{background-color:rgb(194,195,201);}");
    m_allBtn->setStyleSheet("QPushButton{border:1px solid gray;}"
                            "QPushButton:checked{background-color:gray;}");
    
    m_redBtn->setStyleSheet("QPushButton{border:1px solid red;}"
                            "QPushButton:checked{background-color:red;}");

    m_yellowBtn->setStyleSheet("QPushButton{border:1px solid yellow;}"
                            "QPushButton:checked{background-color:yellow;}");

    m_blueBtn->setStyleSheet("QPushButton{border:1px solid blue;}"
                            "QPushButton:checked{background-color:blue;}");

    connect(m_allBtn, &QPushButton::released, this, [=]() {m_filterProxyModel->setFilterFixedString(QString()); });
    connect(m_redBtn, &QPushButton::released, this, [=]() {m_filterProxyModel->setFilterFixedString(QString::number(S_Red)); });
    connect(m_yellowBtn, &QPushButton::released, this, [=]() {m_filterProxyModel->setFilterFixedString(QString::number(S_Yellow)); });
    connect(m_blueBtn, &QPushButton::released, this, [=]() {m_filterProxyModel->setFilterFixedString(QString::number(S_Blue)); });
}

void MainWindow::initLayout()
{
    QVBoxLayout* vlayout = new QVBoxLayout(m_centralWidget);
    vlayout->setMargin(0);

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->setMargin(0);

    hlayout->addStretch();
    hlayout->addWidget(m_allBtn);
    hlayout->addWidget(m_redBtn);
    hlayout->addWidget(m_blueBtn);
    hlayout->addWidget(m_yellowBtn);
    hlayout->addStretch();

    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_listView);

}

void MainWindow::updateNum()
{
    m_allBtn->setText(QString("All %1").arg(redNum + blueNum + yellowNum));
    m_redBtn->setText(QString("Red %1").arg(redNum));
    m_yellowBtn->setText(QString("Yellow %1").arg(yellowNum));
    m_blueBtn->setText(QString("Blue %1").arg(blueNum));
}

void MainWindow::initContextMenu()
{
    m_contextMenu = new QMenu(this);
    m_contextMenu->addAction("删除", [=]() {m_model->removeRow(m_listView->currentIndex().row()); qDebug() << m_listView->currentIndex(); });
    m_contextMenu->addSeparator();
    m_contextMenu->addAction("当前点击设为Red", [=]() {setCurrentClickedStatus(S_Red); });
    m_contextMenu->addAction("当前点击设为Yellow", [=]() {setCurrentClickedStatus(S_Yellow); });
    m_contextMenu->addAction("当前点击设为Blue", [=]() {setCurrentClickedStatus(S_Blue); });
    m_contextMenu->addSeparator();
    m_contextMenu->addAction("所有选择设为Red", [=]() {setAllSelectStatus(S_Red); });
    m_contextMenu->addAction("所有选择设为Yellow", [=]() {setAllSelectStatus(S_Yellow); });
    m_contextMenu->addAction("所有选择设为Blue", [=]() {setAllSelectStatus(S_Blue); });
}

void MainWindow::contextMenuEvent(QContextMenuEvent* ev)
{
    //是在项上面点击的
    if(m_listView->indexAt(m_listView->mapFromParent(ev->pos())).isValid())
       m_contextMenu->popup(ev->globalPos());
    qDebug() << "QContextMenuEvent";
}

void MainWindow::setCurrentClickedStatus(ItemStatus status)
{
    const QModelIndex& proxyIndex = m_listView->currentIndex();     //代理index
    const QModelIndex& index = m_filterProxyModel->mapToSource(proxyIndex); //把代理index转为源index
    int symbol = 1;

    switch (index.data(Qt::UserRole+2).value<ItemStatus>())
    {
    case S_Red:
        --redNum;
        break;
    case S_Blue:
        --blueNum;
        break;
    case S_Yellow:
        --yellowNum;
        break;
    }

    switch (status)
    {
    case S_Red:
        ++redNum;
        break;
    case S_Blue:
        ++blueNum;
        break;
    case S_Yellow:
        ++yellowNum;
        break;
    }
    m_model->setData(index, status, Qt::UserRole + 2);
    updateNum();
}

void MainWindow::setAllSelectStatus(ItemStatus status)
{
    const QModelIndexList& proxyIndexList = m_listView->selectionModel()->selectedIndexes();
    QModelIndexList indexList;
    for (const QModelIndex& index : proxyIndexList)
    {
        indexList.push_back(m_filterProxyModel->mapToSource(index));    ////获取源model的modelIndex
    }

    for (const auto& index : indexList)
    {
        switch (index.data(Qt::UserRole + 2).value<ItemStatus>())
        {
        case S_Red:
            --redNum;
            break;
        case S_Blue:
            --blueNum;
            break;
        case S_Yellow:
            --yellowNum;
            break;
        }

        switch (status)
        {
        case S_Red:
            ++redNum;
            break;
        case S_Blue:
            ++blueNum;
            break;
        case S_Yellow:
            ++yellowNum;
            break;
        }
        m_model->setData(index, status, Qt::UserRole + 2);      
    }
    updateNum();
}
