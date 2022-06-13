#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->answer_button, &QPushButton::pressed, [=](){
        std::cout<<"Button pressed"<<std::endl;
    });
    connect(ui->answer_input, &QLineEdit::returnPressed, ui->answer_button, &QPushButton::pressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

