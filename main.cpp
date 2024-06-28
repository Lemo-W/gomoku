#include "mainwindow.h"
#include "bigin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    bigin x;
    x.show();
    return a.exec();
}
