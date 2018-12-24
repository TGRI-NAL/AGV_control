#include <QApplication>
#include <QMessageBox>

#include "mywidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("TGRI");
    QCoreApplication::setOrganizationDomain("teco.com.tw");
    QCoreApplication::setApplicationName("AGV");

    MyWidget w;
    //w.showMaximized();
    w.show();

    return a.exec();
}
