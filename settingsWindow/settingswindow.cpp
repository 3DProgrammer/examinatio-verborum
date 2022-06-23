#include "settingswindow.h"
#include "style/NoxStyle.h"
#include "ui_settingswindow.h"
#include "style/NeonStyle.h"
#include <QAbstractButton>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>
#include <iostream>
#include <QFontDialog>


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
    ui->themeSelectionBox->addItem("Neon");
    ui->themeSelectionBox->setCurrentIndex(-1);
    ui->font_select_button->setText(ui->themeSelectionLabel->font().family());
    connect(ui->themeSelectionBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
        QSettings settings;
        std::cout<<"Combo box changed to item #"<<index<<std::endl;
        std::cout<<"New theme is "<<ui->themeSelectionBox->itemText(index).toStdString()<<"."<<std::endl;
        if (index<numStyles) {
            QApplication::setStyle(ui->themeSelectionBox->itemText(index));
            QApplication::setPalette(QApplication::style()->standardPalette());
            settings.setValue(SETTINGS_THEME_TYPE_KEY, SETTINGS_THEME_TYPE_NAME);
            settings.setValue(SETTINGS_THEME_NAME_KEY, ui->themeSelectionBox->itemText(index));
        }
        else {
            if (ui->themeSelectionBox->itemText(index)=="Nox") {
                QApplication::setStyle(new NoxStyle);
                QApplication::setPalette(QApplication::style()->standardPalette());
                settings.setValue(SETTINGS_THEME_TYPE_KEY, SETTINGS_THEME_TYPE_BUILTIN);
                settings.setValue(SETTINGS_THEME_NAME_KEY, "Nox");
            }
            else if (ui->themeSelectionBox->itemText(index)=="Neon") {
                QApplication::setStyle(new NeonStyle);
                QApplication::setPalette(QApplication::style()->standardPalette());
                settings.setValue(SETTINGS_THEME_TYPE_KEY, SETTINGS_THEME_TYPE_BUILTIN);
                settings.setValue(SETTINGS_THEME_NAME_KEY, "Neon");
            }
        }
    });
    connect(ui->exitButton, &QPushButton::pressed, [=](){
        deleteLater();
    });
    connect(ui->font_select_button, &QPushButton::pressed, [=](){
        QFont font = QFontDialog::getFont(nullptr, ui->themeSelectionLabel->font());
        std::cout<<font.family().toStdString()<<std::endl;
        ui->font_select_button->setText(font.family());
        QApplication::setFont(font);
    });
}

SettingsWindow::~SettingsWindow() {
    delete ui;
}
