#ifndef GAMESTARTWIDGET_H
#define GAMESTARTWIDGET_H
#include<widget.h>
#include<QLabel>
#include<QPixmap>
#include<QPushButton>
#include<QGridLayout>
#include<QListWidget>
#include<QString>
#include"AIplayer.h"
#include<QMovie>
#include<QKeyEvent>
#include"mybutton.h"

class gameStartWidget:public QWidget
{
 Q_OBJECT

   public:
    gameStartWidget();
    ~gameStartWidget();
    QLabel *money;  //
    QLabel *coin;  //
    QLabel *moneypool;   //
    QLabel *nowMoney;   //


    QMovie *background;   //
    QLabel *bac;          //
    QLabel *player1;
    QLabel *player2;
    QLabel *player3;
    QLabel *player4;
    QLabel *self;

    QLabel *card1;    //我的卡牌
    QLabel *card2;
    QLabel *card3;

    QLabel *p1card1;
    QLabel *p1card2;
    QLabel *p1card3;

    QLabel *p2card1;
    QLabel *p2card2;
    QLabel *p2card3;

    QLabel *p3card1;
    QLabel *p3card2;
    QLabel *p3card3;

    QLabel *p4card1;
    QLabel *p4card2;
    QLabel *p4card3;

    QPixmap *player1_icon;           //头像
    QPixmap *player2_icon;
    QPixmap *player3_icon;
    QPixmap *player4_icon;
    QPixmap *self_icon;

    myButton *hold;             //按钮
    myButton *check;
    myButton *unseen_cmp;
    myButton *seen_cmp;
    myButton *pass;
    myButton *addMoney;

    QGridLayout *gameLayout;

    QListWidget *roundInfo;         //表示回合信息

    Widget *esc;                   //按下esc后的选项窗口

    void keyPressEvent(QKeyEvent *event);

    bool ifSeen=0;
signals:

public slots:


};
#endif // GAMESTARTWIDGET_H
