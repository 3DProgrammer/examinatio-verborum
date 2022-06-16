#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <bibliotheca.h>
#include <iostream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QSettings>
#include "wordChooser.h"

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
        } else {
            ui->hint_label->setText(QString::fromStdString(choice.noun->getLatin()));
        }
    });
    connect(ui->actionOpen_Wordlist, &QAction::triggered, [=]() {
#ifdef __wasm__
        QFileDialog::getOpenFileContent(tr("Word lists (*.wordList)"),[=](const QString &fileName, const QByteArray &fileContent){
            std::cout<<"File data is "<<fileContent.toStdString()<<std::endl;
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
                                                            tr("Word lists (*.wordList)")).toStdString();
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
    choice = chooseNoun(&wordList.nouns, &cases, &numbers);
    if (choice.noun != nullptr) {
        ui->question_label->setText(QString::fromStdString(
                "Translate *" + choice.noun->getEnglish() + "* in the " + cases[choice.nounCase] + " " +
                numbers[choice.nounNumber] + "."));
        answer = choice.noun->noun(choice.nounCase, choice.nounNumber);
        ui->answer_input->setText("");
        ui->hint_label->setText("");
    }
}

