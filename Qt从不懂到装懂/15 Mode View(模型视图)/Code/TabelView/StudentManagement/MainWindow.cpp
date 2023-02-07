#include "MainWindow.h"
#include<QMenuBar>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,m_tableView(new QTableView)
    ,m_model(new QStandardItemModel)
{
    this->setCentralWidget(m_tableView);
    m_tableView->setModel(m_model);
    resize(860, 520);
    initMenuBar();
    onOpenFile();
}

void MainWindow::initMenuBar()
{
    auto *menubar = menuBar();
    auto *fileMenu = menubar->addMenu("文件");
    fileMenu->addAction("打开",this,&MainWindow::onOpenFile)->setShortcut(QKeySequence("Ctrl+O"));
    fileMenu->addAction("保存",this,&MainWindow::onSaveFile)->setShortcut(QKeySequence("Ctrl+S"));
    fileMenu->addAction("另存为",this,&MainWindow::onSaveAsFile)->setShortcut(QKeySequence("Ctrl+Shift+S"));
}

void MainWindow::initModelFromStringList(QStringList& list)
{
    //第一行是表头
    QString header =  list.at(0);
    //以空格，\t等空白分隔符分隔字符串，并跳过空字段
    QStringList headerList = header.split(QRegExp("\\s+"), QString::SplitBehavior::SkipEmptyParts);
    //设置表头
    m_model->setHorizontalHeaderLabels(headerList);
    
    //表头已经设置，从list把表头数据删掉
    list.removeFirst();

    //设置表格数据
    for (QString lineData : list)
    {
        QStringList dataList = lineData.split(QRegExp("\\s"), QString::SkipEmptyParts);
        //把一行数据保存进items
        QList<QStandardItem*> items;
        for (QString data : dataList)
        {
            items.append(new QStandardItem(data));
        }      
        //直接设置一行数据
        m_model->appendRow(items);
    }
}

QStringList MainWindow::getModelRows(int row)
{
    QStringList dataList;
    //获取列数
    int cols = m_model->columnCount();
    //把指定行的数据获取出来，保存到dataList
    for (int c = 0; c < cols; c++)
    {
        QString itemText =  m_model->item(row, c)->text();
        dataList.append(itemText);
    }
    return dataList;
}

void MainWindow::onOpenFile()
{
    QString filename = "./student - 副本.txt";//= QFileDialog::getOpenFileName(this, "选择文件", "./", "txt (*.txt);;csv (*.csv)");
    if (filename.isEmpty())
        return;
    m_srcFileName = filename;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QStringList content;        //读取到的内容列表
    QTextStream stream(&file);
    while (!stream.atEnd())
    {
        content.append(stream.readLine());
    }
    file.close();
    initModelFromStringList(content);
}

void MainWindow::onSaveFile()
{    
    saveToTxtFile(m_srcFileName);
}

void MainWindow::onSaveAsFile()
{
    auto filename = QFileDialog::getSaveFileName(this, "选择文件", "./", "txt (*.txt);;csv (*.csv)");
    if (filename.isEmpty())
        return;
    if (filename.endsWith(".txt", Qt::CaseSensitivity::CaseInsensitive))
    {
        saveToTxtFile(filename);
    }    
    else if (filename.endsWith(".csv", Qt::CaseSensitivity::CaseInsensitive))
    {
        saveToCsvFile(filename);
    } 
}

void MainWindow::saveToTxtFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream stream(&file);
    //写表头
    QStringList header;
    for (size_t i = 0; i < m_model->columnCount(); i++)
    {
        QString field = m_model->horizontalHeaderItem(i)->text();
        header << field;
    }  
    stream<< header.join("\t")<<"\n";
   
    //写数据
    for (int r = 0; r < m_model->rowCount(); r++)
    {
        //获取一行数据
        QStringList dataList = getModelRows(r);
        //把字符串列表，以\t为分隔符连接成一个字符串
        QString lineData = dataList.join("\t");
        //保存到文件
        stream << lineData << "\n";
    }
}

void MainWindow::saveToCsvFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream stream(&file);
    //写表头
    QStringList header;
    for (size_t i = 0; i < m_model->columnCount(); i++)
    {
        QString field = m_model->horizontalHeaderItem(i)->text();
        header << field;
    }
    stream << header.join(",") << "\n";

    //写数据
    for (int r = 0; r < m_model->rowCount(); r++)
    {
        //获取一行数据
        QStringList dataList = getModelRows(r);
        //把字符串列表，以\t为分隔符连接成一个字符串
        QString lineData = dataList.join(",");
        //保存到文件
        stream << lineData << "\n";
    }
}

/*模型使用 http://c.biancheng.net/view/1869.html
 行列交换 https://blog.csdn.net/gongjianbo1992/article/details/106932706/
*/