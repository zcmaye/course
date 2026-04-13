#include "ExpandableDialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExpandableDialog w;
    w.show();
    return a.exec();
}
