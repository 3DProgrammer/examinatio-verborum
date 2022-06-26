#include "addverb.h"
#include "ui_addverb.h"
#include <iostream>


addverb::addverb(QWidget *parent) : QDialog(parent), ui(new Ui::addverb) {
    ui->setupUi(this);
    stringListModel = new QStringListModel;
    ui->translationsListView->setModel(stringListModel);
    connect (ui->present, &QLineEdit::textChanged, [=](const QString&text){
        spelling1=text.toStdString();
    });
    connect (ui->inf, &QLineEdit::textChanged, [=](const QString&text){
        spelling2=text.toStdString();
    });
    connect (ui->perfect, &QLineEdit::textChanged, [=](const QString&text){
        spelling3=text.toStdString();
    });
    connect (ui->participle, &QLineEdit::textChanged, [=](const QString&text){
        spelling4=text.toStdString();
    });
    connect(ui->dialogButtons, &QDialogButtonBox::accepted, [=]() {
        accept();
    });
    connect(ui->dialogButtons, &QDialogButtonBox::rejected, [=]() {
        reject();
    });
    connect(ui->addTranslationButton, &QPushButton::pressed, [=](){
        stringListModel->insertRows(0,1);
        ui->translationsListView->edit(stringListModel->index(0));
    });
    connect(ui->deleteTranslationButton, &QPushButton::pressed, [=](){
        if (stringListModel->rowCount()>0) {
            if (!ui->translationsListView->selectionModel()->selectedRows().empty()) {
                int selectedRow = ui->translationsListView->selectionModel()->selectedRows()[0].row();
                stringListModel->removeRow(selectedRow);
            }
        }
    });
}

addverb::~addverb() {
    delete ui;
}
