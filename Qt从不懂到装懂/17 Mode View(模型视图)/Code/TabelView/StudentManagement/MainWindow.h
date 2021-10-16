#pragma once

#include <QtWidgets/QMainWindow>
#include<QStandardItemModel>
#include<QTableView>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    void initMenuBar();
    void initModelFromStringList(QStringList& list);
    QStringList getModelRows(int row); //从model中获取一行数据
public slots:
    void onOpenFile();      //打开
    void onSaveFile();      //保存
    void onSaveAsFile();    //另存为
private:
    void saveToTxtFile(const QString& filename);
    void saveToCsvFile(const QString& filename);
private:
    QTableView* m_tableView;
    QStandardItemModel* m_model;

    QString m_srcFileName;  //打开的文件的路径
};
