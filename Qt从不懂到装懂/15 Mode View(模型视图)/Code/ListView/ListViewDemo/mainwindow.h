#pragma once

#include <QtWidgets/QMainWindow>
#include<QListView>
#include<QStandardItemModel>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void initData();
private:
    QListView* m_listView;
    QStandardItemModel* m_model;
};
