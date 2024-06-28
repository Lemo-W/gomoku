#include "bigin.h"
#include "ui_bigin.h"

bigin::bigin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bigin)
{
    ui->setupUi(this);

}

bigin::~bigin()
{
    delete ui;
}

void bigin::on_pushButton_clicked()
{
    fol = new forl;
    fol->show();
    this->close();
}

