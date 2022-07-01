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
#define addSetting(name, signal, setter, argType) {QSettings settings; if (settings.contains(QString::fromStdString(std::string("AUTO_SETTING")+#name))) {ui->name->setter(settings.value(QString::fromStdString(std::string("AUTO_SETTING")+#name)).value<argType>());} connect(ui->name, &std::remove_pointer<decltype(ui->name)>::type::signal, [=](argType value){std::cout<<#name<<" set to "<<value<<std::endl;QSettings newSettings;newSettings.setValue(QString::fromStdString(std::string("AUTO_SETTING")+#name),value);});}

SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SettingsWindow) {
    ui->setupUi(this);

    addSetting(n_w, valueChanged, setValue, int);
    addSetting(v_w, valueChanged, setValue, int);

    addSetting(enable_nouns, stateChanged, setChecked, bool);
    addSetting(n_w_sing, valueChanged, setValue, int);
    addSetting(n_w_plur, valueChanged, setValue, int);
    addSetting(n_w_nom, valueChanged, setValue, int);
    addSetting(n_w_acc, valueChanged, setValue, int);
    addSetting(n_w_gen, valueChanged, setValue, int);
    addSetting(n_w_dat, valueChanged, setValue, int);
    addSetting(n_w_abl, valueChanged, setValue, int);
    addSetting(n_w_voc, valueChanged, setValue, int);
    addSetting(enable_verbs, stateChanged, setChecked, bool);
    addSetting(v_w_s, valueChanged, setValue, int);
    addSetting(v_w_p, valueChanged, setValue, int);
    addSetting(v_w_1, valueChanged, setValue, int);
    addSetting(v_w_2, valueChanged, setValue, int);
    addSetting(v_w_3, valueChanged, setValue, int);
    addSetting(v_w_ac, valueChanged, setValue, int);
    addSetting(v_w_pa, valueChanged, setValue, int);
    addSetting(v_w_inf, valueChanged, setValue, int);
    addSetting(v_w_imperative, valueChanged, setValue, int);
    addSetting(v_w_ind, valueChanged, setValue, int);
    addSetting(v_w_sub, valueChanged, setValue, int);
    addSetting(v_w_plu, valueChanged, setValue, int);
    addSetting(v_w_per, valueChanged, setValue, int);
    addSetting(v_w_imperfect, valueChanged, setValue, int);
    addSetting(v_w_pre, valueChanged, setValue, int);
    addSetting(v_w_fut, valueChanged, setValue, int);
    addSetting(v_w_futper, valueChanged, setValue, int);
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
