#ifndef EXAMINATIO_VERBORUM_ADDNOUN_H
#define EXAMINATIO_VERBORUM_ADDNOUN_H

#include "bibliotheca.h"
#include <QDialog>
#include <QStringListModel>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
    class addnoun;
}
QT_END_NAMESPACE

class addnoun : public QDialog {
    Q_OBJECT

public:
    explicit addnoun(QWidget *parent = nullptr);
    ~addnoun() override;
    std::string nomSing;
    std::string genSing;
    int declension;
    bibliotheca::Gender gender;
    QStringListModel * stringListModel;
private:
    Ui::addnoun *ui;
};


#endif//EXAMINATIO_VERBORUM_ADDNOUN_H
