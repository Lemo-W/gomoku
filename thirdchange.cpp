#include "thirdchange.h"
#include "ui_thirdchange.h"
#include <QDebug>
thirdchange::thirdchange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thirdchange)
{
    ui->setupUi(this);
}

thirdchange::~thirdchange()
{
    delete ui;
}


void thirdchange::on_pushButton_2_clicked()
{
    this->close();
}

