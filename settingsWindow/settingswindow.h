//
// Created by miles on 21/6/22.
//

#ifndef EXAMINATIO_VERBORUM_SETTINGSWINDOW_H
#define EXAMINATIO_VERBORUM_SETTINGSWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
    class SettingsWindow;
}
QT_END_NAMESPACE

class SettingsWindow : public QWidget {
    Q_OBJECT

public:
    explicit SettingsWindow(QStyle * _defaultStyle, QWidget *parent = nullptr);
    ~SettingsWindow() override;
    QString defaultStyle;
private:
    Ui::SettingsWindow *ui;
};


#endif//EXAMINATIO_VERBORUM_SETTINGSWINDOW_H
