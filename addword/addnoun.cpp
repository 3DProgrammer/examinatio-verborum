#include "addnoun.h"
#include "ui_addnoun.h"
#include <iostream>


addnoun::addnoun(QWidget *parent) : QDialog(parent), ui(new Ui::addnoun) {
    ui->setupUi(this);
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
}

addnoun::~addnoun() {
    delete ui;
}
