#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wordChooser.h"
#include <QFileDialog>
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
        for (auto tense:{bibliotheca::Tense::pluperfect,bibliotheca::Tense::perfect,bibliotheca::Tense::imperfect,bibliotheca::Tense::present}) {
            for (auto mood:{bibliotheca::Mood::indicative,bibliotheca::Mood::subjunctive}) {
                for (auto number:{bibliotheca::Number::singular,bibliotheca::Number::plural}) {
                    for (auto person:{1,2,3}) {
                        verbOptionWeights.emplace_back(VerbOption(person, number, tense, voice, mood),1);
                    }
                }
            }
        }
        for (auto tense:{bibliotheca::Tense::future,bibliotheca::Tense::futureperfect}) {
            for (auto number:{bibliotheca::Number::singular,bibliotheca::Number::plural}) {
                for (auto person:{1,2,3}) {
                    verbOptionWeights.emplace_back(VerbOption(person, number, tense, voice, bibliotheca::Mood::indicative),1);
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
                    if (ui->open_vocab_list_button) {
                        ui->open_vocab_list_button->deleteLater();
                        ui->open_vocab_list_button = nullptr;
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
#ifndef __wasm__
    ui->menuFile->addMenu(&recentFiles);
#endif
    connect(ui->answer_button, &QPushButton::pressed, [=]() {
        if (ui->answer_input->text().toStdString() == answer) {
            std::cout << "Correct!" << std::endl;
            nextWord();
        }
        else if (ui->answer_input->text().toStdString()=="OVERRIDE_PRINT_ANSWER") {
            std::cout<<answer<<std::endl;
        }
        else {

            if (wordChoice == WordChoice::Noun) {
                ui->hint_label->setText(QString::fromStdString(nounChoice.noun->getLatin()));
            }
            else if (wordChoice == WordChoice::Verb) {
                ui->hint_label->setText(QString::fromStdString(verbChoice.verb->getLatin()));
            }
        }
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
                if (ui->open_vocab_list_button) {
                    ui->open_vocab_list_button->deleteLater();
                    ui->open_vocab_list_button = nullptr;
                }
#endif
    });
    connect(ui->answer_input, &QLineEdit::returnPressed, ui->answer_button, &QPushButton::pressed);
    connect(ui->open_vocab_list_button, &QPushButton::pressed, [=]() { ui->actionOpen_Wordlist->trigger(); });
    nextWord();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::nextWord() {
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
