#ifndef EXAMINATIO_VERBORUM_SETTINGSWINDOW_H
#define EXAMINATIO_VERBORUM_SETTINGSWINDOW_H

#include <QWidget>
#define SETTINGS_THEME_TYPE_KEY "theme_type"
#define SETTINGS_THEME_TYPE_NAME "name"
#define SETTINGS_THEME_TYPE_BUILTIN "builtin"
#define SETTINGS_THEME_NAME_KEY "theme_name"

QT_BEGIN_NAMESPACE
namespace Ui {
    class SettingsWindow;
}
QT_END_NAMESPACE

class SettingsWindow : public QWidget {
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow() override;
    QString defaultStyle;
private:
    Ui::SettingsWindow *ui;
};


#endif//EXAMINATIO_VERBORUM_SETTINGSWINDOW_H
