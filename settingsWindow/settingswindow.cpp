#include <QStyleFactory>
#include <iostream>
#include <QAbstractButton>
#include <QPushButton>
#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "style/NoxStyle.h"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
    ui->setupUi(this);
    auto styles = QStyleFactory::keys();
    qsizetype numStyles=styles.size();
    std::cout<<styles.size()<<" styles available."<<std::endl;
    for (const auto& style:styles) {
        std::cout<<style.toStdString()<<std::endl;
        ui->themeSelectionBox->addItem(style);
    }
    ui->themeSelectionBox->addItem("Nox");
    ui->themeSelectionBox->setCurrentIndex(0);
    connect(ui->themeSelectionBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
        std::cout<<"Combo box changed to item #"<<index<<std::endl;
        std::cout<<"New theme is "<<ui->themeSelectionBox->itemText(index).toStdString()<<"."<<std::endl;
        if (index<numStyles) {
            QApplication::setStyle(ui->themeSelectionBox->itemText(index));
            QApplication::setPalette(QApplication::style()->standardPalette());
        }
        else {
            if (ui->themeSelectionBox->itemText(index)=="Nox") {
                QApplication::setStyle(new NoxStyle);
                QApplication::setPalette(QApplication::style()->standardPalette());
            }
        }
    });
    connect(ui->exitButton, &QPushButton::pressed, [=](){
        deleteLater();
    });
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}
