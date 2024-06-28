#ifndef BIGIN_H
#define BIGIN_H

#include <QWidget>
#include "mainwindow.h"
#include "forl.h"
namespace Ui {
class bigin;
}

class bigin : public QWidget
{
    Q_OBJECT

public:
    explicit bigin(QWidget *parent = nullptr);
    ~bigin();
    MainWindow *main;
    forl *fol;

private slots:
    void on_pushButton_clicked();

private:
    Ui::bigin *ui;
};

#endif // BIGIN_H
