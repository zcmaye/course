#ifndef EXPANDABLEDIALOG_H
#define EXPANDABLEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ExpandableDialog; }
QT_END_NAMESPACE

class ExpandableDialog : public QDialog
{
    Q_OBJECT

public:
    ExpandableDialog(QWidget *parent = nullptr);
    ~ExpandableDialog();

private:
    Ui::ExpandableDialog *ui;
};
#endif // EXPANDABLEDIALOG_H
