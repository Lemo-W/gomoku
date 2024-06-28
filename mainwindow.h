#ifndef MAINWINDOW_H
#define MAINWINDOW_H
extern int fl;

#include <QMainWindow>
#include <QMouseEvent>
#include "aiwin.h"
#include "playerwin.h"
#include "thirdchange.h"
#include "help.h"
#include <QStack>
#define MAXSIZE 225
struct pointai{
    int dataxai;
    int datayai;
};
struct pointper{
    int dataxper;
    int datayper;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    int gamemap[15][15];
    int gameflag;//0为ai，1为人
    int numberoftime;
    void torightsite(int x,int y);
    int thirdflagex;
    int thirdflagey;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    aiwin *aiw;
    playerwin *playerw;
    thirdchange *third;
    help *he;

private:
    Ui::MainWindow *ui;
    int clickposr,clickposc;
    int AI();
    int scex(int a,int s);
    int scey(int a,int s);
    int judgeai(int s1,int s2);
    int judgepeo();
    int winflag;
    void gameover();


private:

    QStack<pointai> q1;
    QStack<pointper> q2;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};
#endif // MAINWINDOW_H
