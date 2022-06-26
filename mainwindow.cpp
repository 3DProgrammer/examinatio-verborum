#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addword/addnoun.h"
#include "settingsWindow/settingswindow.h"
#include "style/NoxStyle.h"
#include "wordChooser.h"
#include <QDirIterator>
#include <QFileDialog>
#include <QPropertyAnimation>
#include <QSettings>
#include <QStandardPaths>
#include <bibliotheca.h>
#include <iostream>
void MainWindow::buildOptionWeights() {
    verbOptionWeights.clear();
    for (auto voice: {bibliotheca::Voice::active, bibliotheca::Voice::passive}) {//This line doesn't seem C++
        for (auto number: {bibliotheca::Number::singular, bibliotheca::Number::plural}) {
            verbOptionWeights.emplace_back(VerbOption(1, number, bibliotheca::Tense::present, voice, bibliotheca::Mood::imperative), 1);
        }
        for (auto tense: {bibliotheca::Tense::present, bibliotheca::Tense::perfect, bibliotheca::Tense::future}) {
            verbOptionWeights.emplace_back(VerbOption(1, bibliotheca::Number::singular, tense, voice, bibliotheca::Mood::infinitive), 1);
        }
        for (auto tense: {bibliotheca::Tense::pluperfect, bibliotheca::Tense::perfect, bibliotheca::Tense::imperfect, bibliotheca::Tense::present}) {
            for (auto mood: {bibliotheca::Mood::indicative, bibliotheca::Mood::subjunctive}) {
                for (auto number: {bibliotheca::Number::singular, bibliotheca::Number::plural}) {
                    for (auto person: {1, 2, 3}) {
                        verbOptionWeights.emplace_back(VerbOption(person, number, tense, voice, mood), 1);
                    }
                }
            }
        }
        for (auto tense: {bibliotheca::Tense::future, bibliotheca::Tense::futureperfect}) {
            for (auto number: {bibliotheca::Number::singular, bibliotheca::Number::plural}) {
                for (auto person: {1, 2, 3}) {
                    verbOptionWeights.emplace_back(VerbOption(person, number, tense, voice, bibliotheca::Mood::indicative), 1);
                }
            }
        }
    }
}
void MainWindow::setupRecentFiles() {
    while (!recentFiles.actions().empty()) {
        recentFiles.removeAction(recentFiles.actions()[0]);
    }
    recentFiles.setTitle("&Recent wordlists");
    recentFileList = settings.value(SETTINGS_KEY_RECENT_FILES, QVariant(QList<QString>())).value<QList<QString>>();
    for (int i = recentFileList.size() - 1; i >= 0; i--) {
        auto action = new QAction(recentFileList[i]);
        connect(action, &QAction::triggered,
                [=]() {
                    QString path = recentFileList[i];
                    std::cout << "Opening recent file " << path.toStdString() << std::endl;
                    recentFileList.removeAll(path);
                    recentFileList.append(path);
                    settings.setValue(SETTINGS_KEY_RECENT_FILES, QVariant(recentFileList));
                    setupRecentFiles();
                    wordList = WordList::fromFilename(path.toStdString());
                    nextWord();
                    ui->answer_input->show();
                    ui->answer_button->show();
                    if (ui->open_vocab_list_button_layout_widget) {
                        ui->open_vocab_list_button_layout_widget->deleteLater();
                        ui->open_vocab_list_button_layout_widget = nullptr;
                    }
                });
        recentFiles.addAction(action);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setupRecentFiles();
    buildOptionWeights();
    //    nouns.clear();
    //    nouns.push_back(bibliotheca::Noun("bibliotheca", "bibliothecae", bibliotheca::Gender::f, {"library"}, 1));
    //    nouns.push_back(bibliotheca::Noun("Quintus", "Quinti", bibliotheca::Gender::m, {"Quintus"}, 2));
    //    nouns.push_back(bibliotheca::Noun("Caecilius", "Caecilii", bibliotheca::Gender::m, {"Caecilius"}, 2));
    //    nouns.push_back(bibliotheca::Noun("templum", "templi", bibliotheca::Gender::n, {"temple"}, 2));
    //    nouns.push_back(
    //            bibliotheca::Noun("imperator", "imperatoris", bibliotheca::Gender::m, {"emperor", "general", "commander"},
    //                              3));
    //    nouns.push_back(bibliotheca::Noun("corpus", "corporis", bibliotheca::Gender::n, {"body", "corpse"}, 3));
    //    nouns.push_back(bibliotheca::Noun("manus", "manus", bibliotheca::Gender::f, {"hand"}, 4));
    //    nouns.push_back(bibliotheca::Noun("dies", "diei", bibliotheca::Gender::m, {"day"}, 5));
    ui->question_label->setText("");
    ui->answer_input->setText("");
    ui->hint_label->setText("");
    ui->answer_input->hide();
    ui->answer_button->hide();
    ui->skip_button->hide();
    ui->open_vocab_list_button_layout_widget->setFixedSize(ui->centralwidget->size());
    ui->stuff_layout_widget->setFixedSize(ui->centralwidget->size());

#ifndef __wasm__
    ui->menuFile->addMenu(&recentFiles);
#endif
    QDirIterator it(":/example-wordlists", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString name=it.next();
        examples.addAction(name, [=]() {
            std::cout<<name.toStdString()<<std::endl;
            QFile file(name);
            file.open(QIODeviceBase::ReadOnly);
            wordList = WordList::fromData(QString(file.read(file.size())).toStdString());
            file.close();
            setupRecentFiles();
            nextWord();
            ui->answer_input->show();
            ui->answer_button->show();
            if (ui->open_vocab_list_button_layout_widget) {

                ui->open_vocab_list_button_layout_widget->deleteLater();
                ui->open_vocab_list_button_layout_widget = nullptr;
            }
        });
    }
    examples.setTitle("&Example wordlists");
    ui->menuFile->addMenu(&examples);
    connect(ui->answer_button, &QPushButton::pressed, [=]() {
        if (ui->answer_input->text().toStdString() == answer) {
            std::cout << "Correct!" << std::endl;
            nextWord();
        }
        else if (ui->answer_input->text().toStdString() == "OVERRIDE_PRINT_ANSWER") {
            std::cout << answer << std::endl;
        }
        else {
            if (ui->hint_label->text().size() > 0) {
                ui->skip_button->show();
            }
            if (wordChoice == WordChoice::Noun) {
                ui->hint_label->setText(QString::fromStdString(nounChoice.noun->getLatin()));
            }
            else if (wordChoice == WordChoice::Verb) {
                ui->hint_label->setText(QString::fromStdString(verbChoice.verb->getLatin()));
            }
        }
    });
    connect(ui->skip_button, &QPushButton::pressed, [=]() {
        nextWord();
    });
    connect(ui->actionOpenSettings, &QAction::triggered, [=]() {
        auto dialogWindow = new SettingsWindow();
        dialogWindow->show();
    });
    connect(ui->actionOpen_Wordlist, &QAction::triggered, [=]() {
#ifdef __wasm__
        QFileDialog::getOpenFileContent(tr("Word lists (*.wordList)"), [=](const QString &fileName, const QByteArray &fileContent) {
            std::cout << "File data is " << fileContent.toStdString() << std::endl;
            wordList = WordList::fromData(std::string(fileContent));
            setupRecentFiles();
            nextWord();
            ui->answer_input->show();
            ui->answer_button->show();
            if (ui->open_vocab_list_button) {
                ui->open_vocab_list_button->deleteLater();
                ui->open_vocab_list_button = nullptr;
            }
        });

#else
                std::string fileName = QFileDialog::getOpenFileName(this, tr("Select Wordlist"),
                                                                    QStandardPaths::writableLocation(
                                                                            QStandardPaths::HomeLocation),
                                                                    tr("Word lists (*.wordList)"))
                                               .toStdString();
                std::cout << "Opening file " << fileName << std::endl;
                recentFileList.removeAll(QString::fromStdString(fileName));
                recentFileList.append(QString::fromStdString(fileName));
                settings.setValue(SETTINGS_KEY_RECENT_FILES, QVariant(recentFileList));
                wordList = WordList::fromFilename(fileName);

                setupRecentFiles();
                nextWord();
                ui->answer_input->show();
                ui->answer_button->show();
                if (ui->open_vocab_list_button_layout_widget) {

                    ui->open_vocab_list_button_layout_widget->deleteLater();
                    ui->open_vocab_list_button_layout_widget = nullptr;
                }
#endif
    });
    connect(ui->answer_input, &QLineEdit::returnPressed, ui->answer_button, &QPushButton::pressed);
    connect(ui->open_vocab_list_button, &QPushButton::pressed, [=]() {
        auto *buttonAnimation = new QPropertyAnimation(ui->open_vocab_list_button, "geometry");
        buttonAnimation->setDuration(500);
        buttonAnimation->setStartValue(ui->open_vocab_list_button->geometry());
        buttonAnimation->setEndValue(ui->open_vocab_list_button->geometry().adjusted(-10,-10,10,10));
        buttonAnimation->setEasingCurve(QEasingCurve::OutElastic);
        connect(buttonAnimation, &QAbstractAnimation::finished, [=](){
            std::cout<<"Animation finished"<<std::endl;
            ui->actionOpen_Wordlist->triggered();
            buttonAnimation->deleteLater();
        });
        buttonAnimation->start();
        std::cout<<"Animation started"<<std::endl;

    });
    connect(ui->actionAdd_Noun, &QAction::triggered, [=](){
        std::cout<<"Adding noun..."<<std::endl;
        auto *addNounWindow=new addnoun;
        addNounWindow->show();
        connect(addNounWindow, &QDialog::accepted, [=](){
                bibliotheca::Noun newNoun(addNounWindow->nomSing, addNounWindow->genSing, addNounWindow->gender, {"TODO: Get English."}, addNounWindow->declension);
                std::cout << "Adding noun " << newNoun.getLatin() << std::endl;
            addNounWindow->deleteLater();
        });
        connect(addNounWindow, &QDialog::rejected, addNounWindow, &QDialog::deleteLater);
    });
    nextWord();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::nextWord() {
    ui->skip_button->hide();
    if (rand() % 2 == 0) {
        wordChoice = WordChoice::Verb;
        verbChoice = chooseVerb(&wordList.verbs, verbOptionWeights);
        if (verbChoice.verb != nullptr) {
            std::string optionDescription;
            if (verbChoice.option.mood == bibliotheca::Mood::indicative || verbChoice.option.mood == bibliotheca::Mood::subjunctive) {
                optionDescription += verbChoice.option.person == 1 ? "1st" : verbChoice.option.person == 2 ? "2nd"
                                                                                                           : "3rd";
                optionDescription += " person ";
            }
            if (verbChoice.option.mood != bibliotheca::Mood::infinitive) {
                optionDescription += verbChoice.option.number == bibliotheca::Number::singular ? "singular" : "plural";
                optionDescription += " ";
            }
            if (verbChoice.option.mood != bibliotheca::Mood::imperative) {
                optionDescription += verbChoice.option.tense == bibliotheca::Tense::pluperfect ? "pluperfect" : verbChoice.option.tense == bibliotheca::Tense::perfect ? "perfect"
                                                                                                        : verbChoice.option.tense == bibliotheca::Tense::imperfect     ? "imperfect"
                                                                                                        : verbChoice.option.tense == bibliotheca::Tense::present       ? "present"
                                                                                                        : verbChoice.option.tense == bibliotheca::Tense::future        ? "future"
                                                                                                                                                                       : "future perfect";
                optionDescription += " ";
            }
            if (!verbChoice.verb->deponent) {
                optionDescription += verbChoice.option.voice == bibliotheca::Voice::active ? "active" : "passive";
                optionDescription += " ";
            }
            optionDescription += verbChoice.option.mood == bibliotheca::Mood::indicative ? "indicative" : verbChoice.option.mood == bibliotheca::Mood::imperative ? "imperative"
                                                                                                  : verbChoice.option.mood == bibliotheca::Mood::infinitive       ? "infinitive"
                                                                                                                                                                  : "subjunctive";
            ui->question_label->setText(QString::fromStdString("Translate *" + verbChoice.verb->getEnglish() + "* in the " + optionDescription + "."));
            answer = verbChoice.verb->verb(verbChoice.option.person, verbChoice.option.number, verbChoice.option.tense, verbChoice.option.mood, verbChoice.option.voice);
            ui->answer_input->setText("");
            ui->hint_label->setText("");
        }
    }
    else {
        wordChoice = WordChoice::Noun;
        nounChoice = chooseNoun(&wordList.nouns, &cases, &numbers);
        if (nounChoice.noun != nullptr) {
            ui->question_label->setText(QString::fromStdString(
                    "Translate *" + nounChoice.noun->getEnglish() + "* in the " + cases[nounChoice.nounCase] + " " +
                    numbers[nounChoice.nounNumber] + "."));
            answer = nounChoice.noun->noun(nounChoice.nounCase, nounChoice.nounNumber);
            ui->answer_input->setText("");
            ui->hint_label->setText("");
        }
    }
}
void MainWindow::resizeEvent(QResizeEvent *event) {
    if (ui->open_vocab_list_button_layout_widget) {
        ui->open_vocab_list_button_layout_widget->setFixedSize(ui->centralwidget->size());
    }
    ui->stuff_layout_widget->setFixedSize(ui->centralwidget->size());
    QWidget::resizeEvent(event);
}
