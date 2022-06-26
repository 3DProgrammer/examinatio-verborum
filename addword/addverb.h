#ifndef EXAMINATIO_VERBORUM_ADDVERB_H
#define EXAMINATIO_VERBORUM_ADDVERB_H

#include "bibliotheca.h"
#include <QDialog>
#include <QStringListModel>
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
    class addverb;
}
QT_END_NAMESPACE

class addverb : public QDialog {
    Q_OBJECT

public:
    explicit addverb(QWidget *parent = nullptr);
    ~addverb() override;
    QStringListModel * stringListModel;
    std::string spelling1;
    std::string spelling2;
    std::string spelling3;
    std::string spelling4;
private:
    Ui::addverb *ui;
};


#endif//EXAMINATIO_VERBORUM_ADDVERB_H
