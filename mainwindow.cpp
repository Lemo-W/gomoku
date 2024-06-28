#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <math.h>
#include "forl.h"
#include <QTime>

//#include "thirdchange.h"
int forl::fl;
//int thirdchange::ifchange;
int forl::tc;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            gamemap[i][j]=0;
        }
    }
    winflag = 0;
    numberoftime = 0;
    if(forl::fl==2)
    {
        gamemap[7][7]=2;
        update();
        numberoftime++;
    }
    ui->pushButton_2->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::scex(int a, int s)
{//电脑棋子得分
    if(a==-1) s+=0;
    if(a==0)  s+=7;
    if(a==1)  s+=15;
    if(a==2)  s+=400;
    if(a==3)  s+=1800;
    if(a==4)  s+=100000;
    return s;
}

int MainWindow::scey(int a, int s)
{//玩家棋子得分
    if(a==-1) s+=0;
    if(a==0)  s+=7;
    if(a==1)  s+=35;
    if(a==2)  s+=800;
    if(a==3)  s+=15000;
    if(a==4)  s+=800000;
    return s;
}

int MainWindow::judgeai(int s1,int s2)
{//2为ai
    int tot=0;
    for(int i=s1+1;i<15;i++)
    {//右边相同棋子数
        if(gamemap[i][s2]==2)tot++;
        else break;
    }
    for(int i=s1-1;i>=0;i--)
    {//左边...
        if(gamemap[i][s2]==2)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    //2.判断竖直线
    tot=0;
    for(int i=s2+1;i<15;i++)
    {//下方相同棋子数
        if(gamemap[s1][i]==2)tot++;
        else break;
    }
    for(int i=s2-1;i>=0;i--)
    {//上方...
        if(gamemap[s1][i]==2)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    //3.判断斜线（左）
    tot=0;
    for(int i=1;i<5;i++)
    {//左上方相同棋子数
        if(s1-i<0||s2-i<0)break;

        if(gamemap[s1-i][s2-i]==2)tot++;
        else break;
    }
    for(int i=1;i<5;i++)
    {//右下方...
        if(s1+i>=15||s2+i>=15)break;

        if(gamemap[s1+i][s2+i]==2)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    //4.判断斜线（右）
    tot=0;
    for(int i=1;i<5;i++)
    {//右上方相同棋子数
        if(s1-i<0||s2+i>=15)break;

        if(gamemap[s1-i][s2+i]==2)tot++;
        else break;
    }
    for(int i=1;i<5;i++)
    {//右下方...
        if(s1+i>=15||s2-i<0)break;

        if(gamemap[s1+i][s2-i]==2)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    return 1;
}

int MainWindow::judgepeo()
{//1为人
    int tot=0;
    for(int i=clickposr+1;i<15;i++)
    {//右边相同棋子数
        if(gamemap[i][clickposc]==1)tot++;
        else break;
    }
    for(int i=clickposr-1;i>=0;i--)
    {//左边...
        if(gamemap[i][clickposc]==1)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    //2.判断竖直线
    tot=0;
    for(int i=clickposc+1;i<15;i++)
    {//下方相同棋子数
        if(gamemap[clickposr][i]==1)tot++;
        else break;
    }
    for(int i=clickposc-1;i>=0;i--)
    {//上方...
        if(gamemap[clickposr][i]==1)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    //3.判断斜线（左）
    tot=0;
    for(int i=1;i<5;i++)
    {//左上方相同棋子数
        if(clickposr-i<0||clickposc-i<0)break;

        if(gamemap[clickposr-i][clickposc-i]==1)tot++;
        else break;
    }
    for(int i=1;i<5;i++)
    {//右下方...
        if(clickposr+i>=15||clickposc+i>=15)break;

        if(gamemap[clickposr+i][clickposc+i]==1)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    //4.判断斜线（右）
    tot=0;
    for(int i=1;i<5;i++)
    {//右上方相同棋子数
        if(clickposr-i<0||clickposc+i>=15)break;

        if(gamemap[clickposr-i][clickposc+i]==1)tot++;
        else break;
    }
    for(int i=1;i<5;i++)
    {//右下方...
        if(clickposr+i>=15||clickposc-i<0)break;

        if(gamemap[clickposr+i][clickposc-i]==1)tot++;
        else break;
    }
    if(tot>=4)
    {
        return 0;//获胜
    }

    return 1;
}

void MainWindow::gameover()
{
    if(winflag==1)
    {
        ui->pushButton_2->setEnabled(0);
        playerw = new playerwin;
        playerw->show();
    }else if(winflag==2)
    {
        ui->pushButton_2->setEnabled(0);
        aiw = new aiwin;
        aiw->show();
    }
}

int MainWindow::AI()
{
    //算法概述：
    //将每一组相连的五个点位单独提出来化为一组，计算他的得分。
    //例如，000x0中，只含有一个x，得分就低。
    //0xxxx中，含有四个x，得分最高。
    //0xxyx中，既含有x又含有y，得分为0，因为他不能连成相同的五子。
    //以此类推...
    //最后将每个点位所有包含它的五元组的得分相加，得分最高的点位就是对自己最有利的点位，在该点落子胜率最高


    //得分概述：
    //将ai棋类设为y，玩家棋类为x
    //五元组里没有x得7分 一个x得15分 两个x得400分 三个x得1800分 四个x得100000分
    //一个y得 35 两个y得800 三个y得15000 四个y得800000
    //ai棋类4个时，必须落子（胜利），所以他的得分最高而且差距大

    //算法实现：

    int max=0;//确定最大值
    int s1=0,s2=0;//确定最大值点的位置

    if(numberoftime == 1)
    {
        if(gamemap[7][7]==0)
        {gamemap[7][7]=2;
            update();
            return judgeai(7,7);
        }else if(gamemap[6][6]==0)
        {
            gamemap[6][6]=2;
            update();
            return judgeai(6,6);
        }
    }
    for(int i=0;i<15;i++)//先遍历每一个点位
    {
        for(int j=0;j<15;j++)
        {
            int totx=0;
            int toty=0;
            int score=0;
            if(gamemap[i][j]!=0)continue;

            //水平线
            if(j-2<0||j+2>=15)//xx0xx的情况
            {
                totx=-1;//错误，该五元组不存在
                toty=-1;
            }else{
                for(int m=2;m>=-2;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i][j+m]==2)toty++;
                    if(gamemap[i][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            if(j-1<0||j+3>=15)//x0xxx的情况
            {
                totx=-1;//错误，该五元组不存在
                toty=-1;
            }else{
                for(int m=3;m>=-1;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i][j+m]==2)toty++;
                    if(gamemap[i][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            if(j+4>=15)//0xxxx的情况
            {
                totx=-1;
                toty=-1;//错误，该五元组不存在
            }else{
                for(int m=4;m>=0;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i][j+m]==2)toty++;
                    if(gamemap[i][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            if(j-3<0||j+1>=15)//xxx0x的情况
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=1;m>=-3;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i][j+m]==1)totx++;
                    if(gamemap[i][j+m]==2)toty++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            if(j-4<0)//xxxx0的情况
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=0;m>=-4;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i][j+m]==1)totx++;
                    if(gamemap[i][j+m]==2)toty++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //竖直线
            //0
            //x
            //x
            //x
            //x
            //情况
            if(i+4>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=4;m>=0;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j]==2)toty++;
                    if(gamemap[i+m][j]==1)totx++;

                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x
            //0
            //x
            //x
            //x
            //情况
            if(i-1<0||i+3>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=3;m>=-1;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j]==2)toty++;
                    if(gamemap[i+m][j]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x
            //x
            //0
            //x
            //x
            //情况
            if(i-2<0||i+2>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=2;m>=-2;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j]==2)toty++;
                    if(gamemap[i+m][j]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x
            //x
            //x
            //0
            //x
            //情况
            if(i-3<0||i+1>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=1;m>=-3;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j]==2)toty++;
                    if(gamemap[i+m][j]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x
            //x
            //x
            //x
            //0
            //情况
            if(i-4<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=0;m>=-4;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j]==2)toty++;
                    if(gamemap[i+m][j]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //左斜线
            //00000
            //0x000
            //00x00
            //000x0
            //0000x
            //的情况
            if(i+4>=15||j+4>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=4;m>=0;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j+m]==2)toty++;
                    if(gamemap[i+m][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x0000
            //00000
            //00x00
            //000x0
            //0000x
            //的情况
            if(i+3>=15||j+3>=15||i-1<0||j-1<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=3;m>=-1;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j+m]==2)toty++;
                    if(gamemap[i+m][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x0000
            //0x000
            //00000
            //000x0
            //0000x
            //的情况
            if(i+2>=15||j+2>=15||i-2<0||j-2<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=2;m>=-2;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j+m]==2)toty++;
                    if(gamemap[i+m][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x0000
            //0x000
            //00x00
            //00000
            //0000x
            //的情况
            if(i+1>=15||j+1>=15||i-3<0||j-3<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=1;m>=-3;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j+m]==2)toty++;
                    if(gamemap[i+m][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //x0000
            //0x000
            //00x00
            //000x0
            //00000
            //的情况
            if(i-4<0||j-4<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=0;m>=-4;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j+m]==2)toty++;
                    if(gamemap[i+m][j+m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //右斜线
            //00000
            //000x0
            //00x00
            //0x000
            //x0000
            if(i+4>=15||j-4<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=4;m>=0;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j-m]==2)toty++;
                    if(gamemap[i+m][j-m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //0000x
            //00000
            //00x00
            //0x000
            //x0000
            if(i+3>=15||j-3<0||i-1<0||j+1>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=3;m>=-1;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j-m]==2)toty++;
                    if(gamemap[i+m][j-m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //0000x
            //000x0
            //00000
            //0x000
            //x0000
            if(i+2>=15||j-2||j+2>=15||i-2<0)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=2;m>=-2;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j-m]==2)toty++;
                    if(gamemap[i+m][j-m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //0000x
            //000x0
            //00x00
            //00000
            //x0000
            if(i+1>=15||j-1<0||i-3<0||j+3>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=4;m>=0;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j-m]==2)toty++;
                    if(gamemap[i+m][j-m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            //0000x
            //000x0
            //00x00
            //0x000
            //00000
            if(i-4<0||j+4>=15)
            {
                toty=-1;//错误，该五元组不存在
                totx=-1;
            }else{
                for(int m=0;m>=-4;m--)
                {
                    if(m==0)continue;

                    if(gamemap[i+m][j-m]==2)toty++;
                    if(gamemap[i+m][j-m]==1)totx++;
                }
            }

            if(toty!=0&&totx!=0)
            {//既有x又有y
                score = scex(-1 , score );
            }else if(toty==0)
            {//仅有x
            score = scex(totx,score);
            }else if(totx==0)
            {//仅有y
                score = scey(toty,score);
            }
            totx=0;
            toty=0;

            if(score>max)
            {
                max=score;
                s1=i;
                s2=j;
            }
        }
    }


    gamemap[s1][s2]=2;
//    qDebug()<<s1<<" "<<s2;
    pointai p2={s1,s2};
    q1.push(p2);
//    if(numberoftime == 2)
//    {
//        thirdflagex = s1;
//        thirdflagey = s2;
//    }
    update();

    return judgeai(s1,s2);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    for(int i = 0;i<15;i++)
    {//横线
        painter.drawLine(20,20+40*i,20+40*14,20+40*i);
    }
    for(int i=0;i<15;i++)
    {//竖线
        painter.drawLine(20+40*i,20,20+40*i,20+40*14);
    }

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    for (int i = 0; i < 15; i++)
        for (int j = 0; j <15; j++)
        {
            if (gamemap[i][j] == 1)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(20 + 40 * j -10, 20 + 40 * i-10, 20, 20);
            }
            else if (gamemap[i][j] == 2)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(20 + 40 * j - 10,20 + 40 * i - 10, 20, 20);
            }
        }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(winflag == 0){
    int x=event->pos().x();
    int y=event->pos().y();
    torightsite(x,y);

    if(gamemap[clickposr][clickposc]==0)
    {
        gamemap[clickposr][clickposc]=1;
        numberoftime++;
        pointper p1 = {clickposr,clickposc};
        q2.push(p1);
        if(numberoftime==2)
        {
                if(forl::tc == 1)
                {
                    third = new thirdchange;
                    third->show();
                    update();
                    return;
                }
        }
        if(judgepeo()==0)winflag = 1;
        gameover();
        update();
        if(winflag!=0)return;
        if(AI()==0)winflag = 2;
        numberoftime++;
        gameover();


        if(numberoftime==2)
        {
            if(forl::tc == 1)
            {
            third = new thirdchange;
            third->show();
            AI();
            numberoftime++;
            }
        }
        if(forl::tc==0)
        {
            ui->pushButton_2->setEnabled(1);
        }else if(numberoftime>3)
        {
            ui->pushButton_2->setEnabled(1);
        }
        if(winflag!=0){
        ui->pushButton_2->setEnabled(0);
        }
    }
    update();
    }
}

void MainWindow::torightsite(int x,int y)
{
    if(x>=20&&x<=580&&y>=20&&y<=580)
    {
        int col=x/40;
        int row=y/40;

        int theleftlast = 20+40*col;
        int theunderlast = 20+40*row;

        clickposr = -1;
        clickposc = -1;

        int len = 0; // 计算完后取整就可以了

        // 确定一个误差在范围内的点，且只可能确定一个出来
        len = (x - theleftlast) * (x - theleftlast) + (y - theunderlast) * (y - theunderlast);
        if (len < 800)
        {
            clickposr = row;
            clickposc = col;
        }
        len = (x - theleftlast - theleftlast) * (x - theleftlast - 40) + (y - theunderlast) * (y - theunderlast);
        if (len < 800)
        {
            clickposr = row;
            clickposc = col + 1;
        }
        len = (x - theleftlast) * (x - theleftlast) + (y - theunderlast - 40) * (y - theunderlast - 40);
        if (len < 800)
        {
            clickposr = row + 1;
            clickposc = col;
        }
        len = (x - theleftlast - 40) * (x - theleftlast - 40) + (y - theunderlast - 40) * (y - theunderlast - 40);
        if (len < 800)
        {
            clickposr = row + 1;
            clickposc = col + 1;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            gamemap[i][j]=0;
        }
    }
    winflag = 0;
    numberoftime = 0;
//    thirdchange::ifchange = 0;
    ui->pushButton_2->setEnabled(0);
    if(forl::fl==2)
    {
        gamemap[7][7]=2;
        update();
        numberoftime++;
    }
    update();
}


void MainWindow::on_pushButton_2_clicked()
{
    pointai ai;
    pointper per;
    ai = q1.top();
    q1.pop();
    per = q2.top();
    q2.pop();
    int x1 = ai.dataxai,x2 = per.dataxper;
    int y1 = ai.datayai,y2 = per.datayper;
    gamemap[x1][y1] = 0;
    gamemap[x2][y2] = 0;
    numberoftime -= 2;
    if(numberoftime==0&&forl::tc==0)
        ui->pushButton_2->setEnabled(0);
    if(numberoftime==3&&forl::tc==1)
        ui->pushButton_2->setEnabled(0);
    if(forl::tc==1&&forl::fl==2&&numberoftime==2)
        ui->pushButton_2->setEnabled(0);
    if(forl::fl==2&&forl::tc==0&&numberoftime==1)
        ui->pushButton_2->setEnabled(0);
    qDebug()<<numberoftime;
    update();

}


void MainWindow::on_pushButton_3_clicked()
{
    he = new help;
    he->show();
}

