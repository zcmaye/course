#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include"EmailSender.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnMin_released();
    void on_btnMax_released();
    void on_btnClose_released();

    void on_btnSend_released();

    void on_btnAddatt_released();

    void on_btnAddImage_released();

private:
    Ui::MainWindow *ui;
    EmailSender emailSender;
};
#endif // MAINWINDOW_H
