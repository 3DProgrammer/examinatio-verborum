#include "mainwindow.h"
#include "settingsWindow/settingswindow.h"
#include "style/NoxStyle.h"
#include "style/NeonStyle.h"
#include <QApplication>
#include <QDirIterator>
#include <QStyle>
#include <QStyleFactory>
#include <iostream>
int main(int argc, char *argv[])
{
    srand(time(nullptr));
    std::cout<<"QT version is "<<QT_VERSION_MAJOR<<"."<<QT_VERSION_MINOR<<std::endl;
    std::cout<<"Examinatio verborum version is "<<PROJECT_VERSION_MAJOR<<"."<<PROJECT_VERSION_MINOR<<std::endl;
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        std::cout<<it.next().toStdString()<<std::endl;
    }
//    auto styles = QStyleFactory::keys();
//    std::cout<<styles.size()<<" styles available."<<std::endl;
//    for (const auto& style:styles) {
//        std::cout<<style.toStdString()<<std::endl;
//    }
    QApplication a(argc, argv);
    a.setApplicationName("examinatio-verborum");
    a.setApplicationDisplayName("Examinatio Verborum");
    a.setApplicationVersion(PROJECT_VERSION_STRING);
    a.setOrganizationName("greatcactus");
    a.setOrganizationName("greatcactus.org");
    QSettings settings;
    QVariant customThemeType=settings.value(SETTINGS_THEME_TYPE_KEY);
    if (!customThemeType.isNull()) {
        if (customThemeType.toString()==SETTINGS_THEME_TYPE_NAME) {
            a.setStyle(settings.value(SETTINGS_THEME_NAME_KEY, QVariant(a.style()->objectName())).toString());
        }
        else if (customThemeType.toString()==SETTINGS_THEME_TYPE_BUILTIN) {
            QString themeName=settings.value(SETTINGS_THEME_NAME_KEY, QVariant("Nox")).toString();
            if (themeName=="Nox") {
                a.setStyle(new NoxStyle);
            }
            else if (themeName=="Neon") {
                a.setStyle(new NeonStyle);
            }
        }

        QApplication::setPalette(QApplication::style()->standardPalette());
    }
    MainWindow w;
    w.defaultStyle=a.style();
    w.show();
    return QApplication::exec();
}
