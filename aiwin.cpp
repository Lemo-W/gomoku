#include "aiwin.h"
#include "ui_aiwin.h"

aiwin::aiwin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aiwin)
{
    ui->setupUi(this);
}

aiwin::~aiwin()
{
    delete ui;
}
