#include "playerwin.h"
#include "ui_playerwin.h"

playerwin::playerwin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playerwin)
{
    ui->setupUi(this);
}

playerwin::~playerwin()
{
    delete ui;
}
