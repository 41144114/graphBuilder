#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("Fusion");
    QCoreApplication::setApplicationName("graphBuilder");
    QCoreApplication::setOrganizationName("AbakshinDima");

    MainWindow w;
    w.show();

    return a.exec();
}
