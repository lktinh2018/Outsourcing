#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Change b/*ackground color
//    w.setStyleSheet("background-color: rgb(64, 67, 74)");
//    w.setSty*/leSheet("color: rgb(214,214,214)");

    w.show();

    return a.exec();
}
