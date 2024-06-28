#ifndef FORL_H
#define FORL_H

#include <QWidget>
#include "mainwindow.h"
namespace Ui {
class forl;
}

class forl : public QWidget
{
    Q_OBJECT

public:
    explicit forl(QWidget *parent = nullptr);
    ~forl();
    MainWindow *main;
    static int fl;
    static int tc;
private slots:

//    void on_first_clicked();

//    void on_last_clicked();

    void on_pushButton_clicked();

private:
    Ui::forl *ui;
};

#endif // FORL_H
