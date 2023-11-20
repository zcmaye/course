#include "mainwindow.h"
#include"itemDataDef.h"
#include<QVariant>
#include"itemdelegate.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,m_listView(new QListView)
    ,m_model(new QStandardItemModel)
{
    this->setCentralWidget(m_listView);
    m_listView->setModel(m_model);
    m_listView->setItemDelegate(new ItemDelegate(this));
    m_listView->setSpacing(10);

    m_listView->setViewMode(QListView::IconMode);
    m_listView->setFlow(QListView::Flow::LeftToRight);          //设置流布局方向
    m_listView->setResizeMode(QListView::ResizeMode::Adjust);   //每次调整大小
   
    m_listView->setDragEnabled(false);  //禁止拖动项
    //m_listView->setMovement(QListView::Movement::Snap);     //设置移动手段
    //m_listView->setGridSize(QSize(160+10, 60+10));          //设置移动对齐的格子大小

    m_listView->setSelectionMode(QListView::SelectionMode::MultiSelection); //设置选择模式->多选
    m_listView->setSelectionRectVisible(true);                              //设置是否显示选择矩形

    initData();   
}

void MainWindow::initData()
{
    for (size_t i = 0; i < 10; i++)
    {
        QStandardItem* item = new QStandardItem;
        ItemData itemData;
        itemData.name = QString("Name %1").arg(i);
        itemData.tel = QString("Tel:13123416991");

        item->setData(QVariant::fromValue(itemData));
        m_model->appendRow(item);
    }
}
