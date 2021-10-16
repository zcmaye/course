#include "loginwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Maye");
    QApplication::setApplicationName("login");

    LoginWidget w;
    w.show();
    return a.exec();
}
