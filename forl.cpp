#include "forl.h"
#include "ui_forl.h"
#include "mainwindow.h"

forl::forl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forl)
{
    ui->setupUi(this);
    fl = 0;
    tc = 0;
    ui->radioButton->setChecked(1);
    ui->radioButton_3->setChecked(1);
}

forl::~forl()
{
    delete ui;
}


void forl::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        fl = 1;
    }
    if(ui->radioButton_2->isChecked())
    {
        fl = 2;
    }
    if(ui->radioButton_3->isChecked())
    {
        tc = 0;
    }
    if(ui->radioButton_4->isChecked())
    {
        tc = 1;
    }

    main = new MainWindow;
    main->show();
    this->close();
}

