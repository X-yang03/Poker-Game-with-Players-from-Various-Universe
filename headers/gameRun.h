#ifndef GAMERUN_H
#define GAMERUN_H
#include"playerSelf.h"
#include"scene1Players.h"
#include"scene2Players.h"
#include<scene3Players.h>
#include<scene4Players.h>
#include"gameStartWidget.h"
#include"welcomscene.h"
#include"sceneChoose.h"
#include"help.h"
#include<math.h>
#include<QMouseEvent>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include"server.h"
#include<QMessageBox>
#include"Data.h"
class gameRun:public QObject
{
    Q_OBJECT
public:


    Data *dt;
    bool isServer=false;
    bool netState=false;
    int *playerState;

    int playerIndex=1;
    QVector<QString> name;
    int nowOnlinePlayers=1;

    QByteArray *rec;
    QByteArray *sed;

    server *myServer;
    help *helpWidget; //帮助界面
    gameStartWidget *gameWidget;
    welcomeScene *welcomeWidget;
    sceneChoose *chooseScene;

    QMediaPlaylist *bgmList;
    QMediaPlayer *bgm;

    gameRun(QObject *parent);

    AI *player1;
    AI *player2;
    AI *player3;
    AI *player4;

    QPixmap *p1out;
    QPixmap *p2out;
    QPixmap *p3out;
    QPixmap *p4out;

    playerSelf *self;

    int scene=0;  //游戏场景序号
    bool ifEnd=0; //是否结束
    int myMoney=100; //我的初始金钱
    int moneypool=0; //钱池
    bool win1=0;  //是否通过第一关
    bool win2=0;   //是否通过第二关
    bool win3=0;

    int valSeen=8;   //看牌后的注
    int valUnseen=3; //未看牌的注

    bool eventFilter(QObject *obj, QEvent *event);

    void ifWon();  //判断是否获胜
    void valueCmp(AI *choose,AI *chosen);  //进行比牌
    int cmpOnline(int choose,int chosen);
    AI * maxUnseenCmp(AI* choose);
    AI * maxSeenCmp(AI* choose);
    static bool unseenCmpPossibilityCmp(AI* a,AI* b);
    static bool seenCmpPossibilityCmp(AI *a,AI* b);
    void playerSet(AI *player);  //根据手牌大小第二次改变ai的属性
    void showCards(AI *player);
    void setBtns();
    void btnsSetTrue();
    void btnsSetFalse();
    void setBgm();

    void Distribute(int n);

    void sendDate();
    void NextTurn();

    void playerOut(int n);

signals:
    void myTurnOver();
public slots:

    void welcomeToGame();   //界面切换
    void player1TurnBegin();
    void player2TurnBegin();
    void player3TurnBegin();
    void player4TurnBegin();
    void player1TurnOver();
    void player2TurnOver();
    void player3TurnOver();
    void player4TurnOver();
    void myTurnBegin();
    void showResult();

    void chooseUnseenCmpPlayer(AI* choose);  //ai筛选比牌对象
    void chooseSeenCmpPlayer(AI *choose);

    void holdClicked();
    void checkClicked();
    void passClicked();
    void unseenCmpClicked();
    void seenCmpClicked();
    void addMoneyClicked();
    void backClicked();
    void againClicked();

    void holdOnline();
    void check();
    void passOnline();
    void unseenCmpOnline();
    void seenCmpOnline();


    void loadScene1();  //场景加载函数
    void loadScene2();
    void loadScene3();
    void loadScene4();
    void loadOnline();

    void stop();

    void connectCliked();
    void joinCliked();

    void newConnection();

    void serverRecieve();

    void clintRecieve();


};


#endif // GAMERUN_H
