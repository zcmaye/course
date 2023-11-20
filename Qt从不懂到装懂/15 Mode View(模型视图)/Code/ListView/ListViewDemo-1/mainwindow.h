#pragma once

#include <QtWidgets/QMainWindow>
#include<QListView>
#include<QStandardItemModel>
#include<QPushButton>
#include<QButtonGroup>
#include<QSortFilterProxyModel>
#include<QMenu>
#include"itemDataDef.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void initData();
    void initBtn();
    void initLayout();
    void updateNum();
    void initContextMenu();
    void contextMenuEvent(QContextMenuEvent* ev)override;

    void setCurrentClickedStatus(ItemStatus status);
    void setAllSelectStatus(ItemStatus status);
private:
    QWidget* m_centralWidget;

    QListView* m_listView;
    QStandardItemModel* m_model;

    QPushButton*  m_allBtn;
    QPushButton*  m_redBtn;
    QPushButton*  m_yellowBtn;
    QPushButton*  m_blueBtn;
    QButtonGroup* m_btnGroup;

    int redNum = 0;
    int yellowNum = 0;
    int blueNum = 0;

    QSortFilterProxyModel* m_filterProxyModel;

    QMenu* m_contextMenu;
};
