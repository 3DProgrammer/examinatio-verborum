#include "addnoun.h"
#include "ui_addnoun.h"
#include <iostream>


addnoun::addnoun(QWidget *parent) : QDialog(parent), ui(new Ui::addnoun) {
    ui->setupUi(this);
    stringListModel = new QStringListModel;
    ui->translationsListView->setModel(stringListModel);
    ui->declension->addItem("1", 1);
    ui->declension->addItem("2", 2);
    ui->declension->addItem("3", 3);
    ui->declension->addItem("4", 4);
    ui->declension->addItem("5", 5);
    ui->declension->setCurrentIndex(-1);
    ui->gender->addItem("m", QVariant::fromValue(bibliotheca::Gender::m));
    ui->gender->addItem("f", QVariant::fromValue(bibliotheca::Gender::f));
    ui->gender->addItem("n", QVariant::fromValue(bibliotheca::Gender::n));
    ui->gender->setCurrentIndex(-1);
    connect(ui->declension, &QComboBox::currentIndexChanged, [=](int index){
        declension=ui->declension->itemData(index).toInt();
    });
    connect(ui->gender, &QComboBox::currentIndexChanged, [=](int index){
        gender=ui->gender->itemData(index).value<bibliotheca::Gender>();
    });
    connect (ui->nomSing, &QLineEdit::textChanged, [=](const QString&text){
        nomSing=text.toStdString();
    });
    connect (ui->genSing, &QLineEdit::textChanged, [=](const QString&text){
        genSing=text.toStdString();
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

addnoun::~addnoun() {
    delete ui;
}
