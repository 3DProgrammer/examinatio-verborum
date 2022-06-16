#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <iostream>
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    std::cout<<"QT version is "<<QT_VERSION_MAJOR<<"."<<QT_VERSION_MINOR<<std::endl;
    std::cout<<"Examinatio verborum version is "<<PROJECT_VERSION_MAJOR<<"."<<PROJECT_VERSION_MINOR<<std::endl;
    auto styles = QStyleFactory::keys();
    std::cout<<styles.size()<<" styles available."<<std::endl;
    for (const auto& style:styles) {
        std::cout<<style.toStdString()<<std::endl;
    }
    QApplication a(argc, argv);
    a.setApplicationName("examinatio-verborum");
    a.setApplicationDisplayName("Examinatio Verborum");
    a.setApplicationVersion(PROJECT_VERSION_STRING);
    a.setOrganizationName("greatcactus");
    a.setOrganizationName("greatcactus.org");
    MainWindow w;
    w.show();
    return QApplication::exec();
}
