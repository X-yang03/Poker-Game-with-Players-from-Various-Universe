#include"scene1Players.h"


Harry::Harry(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=65;//喜爱闷牌型玩家
    this->possibility_unseenCmp=20;
    this->possibility_seenPass=20;//由于playerSet函数，seenPass要大于等于20
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=30;
    this->possibility_addMoney=50;
    gamblerLevel=7;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("敢闷才会赢！");
    holdWords.push_back("我要闷一手！");
    holdWords.push_back("Hmmm闷！");

    passWords="唉什么破牌……(出局)";

    goOnWords.push_back("走一局");
    goOnWords.push_back("拼一拼！");
    goOnWords.push_back("跟！");


}

Hermione::Hermione(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=35;//比较稳妥型玩家
    this->possibility_unseenCmp=60;
    this->possibility_seenPass=20;
    this->possibility_beenSeenCmp=10;
    this->possibility_beenUnseenCmp=10;
    this->possibility_seenCmp=30;
     this->possibility_addMoney=40;
    gamblerLevel=4;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("我闷一回");
    holdWords.push_back("还是闷吧……");
    holdWords.push_back("好烦啊还是闷吧");

    goOnWords.push_back("走");
    goOnWords.push_back("还行，走");
    goOnWords.push_back("Hmm走一轮");

    passWords="按照概率来该我赢了啊。。（弃牌出局）";
}

Ron::Ron(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=30;//人物比较胆小
    this->possibility_unseenCmp=70;
    this->possibility_seenPass=30;
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=50;
     this->possibility_addMoney=30;
    gamblerLevel=3;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("我闷一局");
    holdWords.push_back("我闷");
    holdWords.push_back("还是闷好了");

    goOnWords.push_back("我跟！");
    goOnWords.push_back("高风险高回报！（跟牌）");
    goOnWords.push_back("也该我赢了吧（跟牌）");

    passWords="珀西知道了会揍我的。。（弃牌出局）";
}

Malfoy::Malfoy(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=20;//喜爱看牌，人傻钱多
    this->possibility_unseenCmp=80;
    this->possibility_seenPass=20;//由于playerSet函数，seenPass要大于等于20
    this->possibility_beenSeenCmp=40;//易被针对
    this->possibility_beenUnseenCmp=40;
    this->possibility_seenCmp=10;
    this->possibility_addMoney=80;
    gamblerLevel=9;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷！");
    holdWords.push_back("COME ON！（闷）");
    holdWords.push_back("就这？闷！");

    goOnWords.push_back("奉陪到底！（跟牌）");
    goOnWords.push_back("我有的是钱！（跟牌）");
    goOnWords.push_back("赶紧的，走！（跟牌）");

    passWords="小输一局，不怕！（弃牌出局）";
}

