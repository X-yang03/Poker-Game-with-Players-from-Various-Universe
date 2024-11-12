#ifndef AIPLAYER_H
#define AIPLAYER_H
#include"card.h"
#include<QTimer>
#include<algorithm>
#include<QDebug>
class AI:public QObject//作为所有角色的基类
{
    Q_OBJECT
  public:
    QTimer *roundTime=nullptr;
    QString name;
    int index;                                          //每一个ai的序号
    Card *ownCard[3]={NULL};                            //持有手牌

    bool isActive=1;                                    //是否在场
    double pokerValue=0;                                //手牌的大小
    bool ifSeen=0;                                      //是否看牌

    static int nowPlayers;
    static int nowRound;

    QVector<QString> holdWords;
    QString passWords;
    QVector<QString> goOnWords;
    QVector<QString> checkWords;

    int possibility_unseenCmp=0;                       //事先设计,在player构造函数中定义
    int possibility_seenCmp=0;                         //随pokerValue变化，在gameRun的playerSet中定义
    int possibility_hold=0;                           //事先设计，在player构造函数中定义
    int possibility_beenUnseenCmp=0;                   //随行为变化，在gameRun的valuecmp中定义，在player构造函数中赋初值
    int possibility_beenSeenCmp=0;                     //随行为变化，在gameRun的valuecmp中定义，在player构造函数中赋初值
    int possibility_addMoney=0;                        //随pokerVlue变化,在playe构造函数中定义，
    int possibility_seenPass=0;                        //随pokerValue变化，在player构造函数中定义，同时在playerSet中改变
    int gamblerLevel=0;

    AI(QString n,int i,QObject* parent=0);
    ~AI();
    
    void checkValue();                                  //为手牌评定大小
    void getCards();                                    //发牌函数
    void cardSort();                                    //手牌从小到大排列
    QString act();
    
    QString speak_hold();
    QString speak_pass();
    QString speak_cmp();
    QString speak_check();
    QString speak_goOn();
    void enterGamblerMode();

signals:
    void unseenCmp(AI* choose);                      //进行闷开
    void seenCmp(AI *choose);                    //进行开


public slots:

};



#endif // AIPLAYER_H
