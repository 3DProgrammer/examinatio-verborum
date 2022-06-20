#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bibliotheca.h>
#include <QActionGroup>
#include <QMenu>
#include <QSettings>
#include "wordChooser.h"
#include "wordlistParser.h"
#define SETTINGS_KEY_RECENT_FILES "recentFiles"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void nextWord();
    //std::vector<bibliotheca::Noun> nouns;
    std::map<bibliotheca::Case, std::string> cases = {{bibliotheca::Case::nom, "nominative"},
                                                      {bibliotheca::Case::acc, "accusative"},
                                                      {bibliotheca::Case::gen, "genitive"},
                                                      {bibliotheca::Case::dat, "dative"},
                                                      {bibliotheca::Case::abl, "ablative"},
                                                      {bibliotheca::Case::voc, "vocative"}};
    std::map<bibliotheca::Number, std::string> numbers = {{bibliotheca::Number::singular, "singular"},
                                                          {bibliotheca::Number::plural,   "plural"}};
    std::string answer;
    NounChoice nounChoice;
    VerbChoice verbChoice;
    WordChoice wordChoice;
    WordList wordList;
    std::vector<std::pair<VerbOption,int>> verbOptionWeights;
    QMenu recentFiles;
    void setupRecentFiles();
    QList<QString> recentFileList;
    QSettings settings;
    void buildOptionWeights();
};
#endif // MAINWINDOW_H
