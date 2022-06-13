#include "mainwindow.h"

#include <QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    std::cout<<"QT version is "<<QT_VERSION_MAJOR<<"."<<QT_VERSION_MINOR<<std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
