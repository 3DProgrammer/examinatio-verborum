//
// Created by miles on 21/6/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SettingsWindow.h" resolved

#include <QStyleFactory>
#include <iostream>
#include "settingswindow.h"
#include "ui_settingswindow.h"


SettingsWindow::SettingsWindow(QStyle *_defaultStyle, QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
    ui->setupUi(this);
    std::string defaultStyleText="Default (";
    defaultStyle=_defaultStyle->objectName();
    defaultStyleText+=defaultStyle.toStdString();
    defaultStyleText+=")";
    ui->themeSelectionBox->addItem(QString::fromStdString(defaultStyleText));
    auto styles = QStyleFactory::keys();
    std::cout<<styles.size()<<" styles available."<<std::endl;
    for (const auto& style:styles) {
        std::cout<<style.toStdString()<<std::endl;
        ui->themeSelectionBox->addItem(style);
    }
    ui->themeSelectionBox->setCurrentIndex(0);
    connect(ui->themeSelectionBox, &QComboBox::currentIndexChanged, [=](int index){
        std::cout<<"Combo box changed to item #"<<index<<std::endl;
        std::cout<<"New theme is "<<ui->themeSelectionBox->itemText(index).toStdString()<<"."<<std::endl;
        if (index>0) {
            QApplication::setStyle(ui->themeSelectionBox->itemText(index));
        }
        else {
            QApplication::setStyle(defaultStyle);
        }
    });
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}
