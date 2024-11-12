#include<scene2Players.h>

Eren::Eren(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=60;//喜爱闷牌型玩家
    this->possibility_unseenCmp=20;
    this->possibility_seenPass=20;//由于playerSet函数，seenPass要大于等于20
    this->possibility_beenSeenCmp=30;
    this->possibility_beenUnseenCmp=30;
    this->possibility_seenCmp=50;
    this->possibility_addMoney=50;
    gamblerLevel=7;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷！");
    holdWords.push_back("闷！ttk！");
    holdWords.push_back("我要把你们的币一个不留的都赢走！（闷）");

    goOnWords.push_back("看好了，跟注之力是这么用的!");
    goOnWords.push_back("跟!");
    goOnWords.push_back("跟牌!战斗!");

    passWords="我还是一点都没变啊。。（出局）";

}

Mikasa::Mikasa(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=35;//比较稳妥型玩家
    this->possibility_unseenCmp=70;
    this->possibility_seenPass=20;
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=50;
     this->possibility_addMoney=45;
    gamblerLevel=7;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷吧");
    holdWords.push_back("艾伦，你觉得我闷是不是比较好（闷）");
    holdWords.push_back("这把闷");

    goOnWords.push_back("阿克曼的跟牌");
    goOnWords.push_back("跟吧");
    goOnWords.push_back("走");

    passWords="下把必赢！(出局)";
}

Reiner::Reiner(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=25;//人物比较胆小
    this->possibility_unseenCmp=60;
    this->possibility_seenPass=40;
    this->possibility_beenSeenCmp=40;
    this->possibility_beenUnseenCmp=40;
    this->possibility_seenCmp=40;
     this->possibility_addMoney=40;
    gamblerLevel=4;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷！");
    holdWords.push_back("我闷！");
    holdWords.push_back("哈哈我要闷");

    goOnWords.push_back("跟一把牌");
    goOnWords.push_back("加注!");
    goOnWords.push_back("奉陪到底!(跟)");

    passWords="那个回不去的家乡。。（出局）";
}

Rivaille::Rivaille(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=60;//喜爱闷牌型玩家
    this->possibility_unseenCmp=40;
    this->possibility_seenPass=20;
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=10;
    this->possibility_addMoney=60;
    gamblerLevel=4;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷");
    holdWords.push_back("我闷");
    holdWords.push_back("下一个（闷）");

    goOnWords.push_back("小心（跟）");
    goOnWords.push_back("有趣，继续（跟）");
    goOnWords.push_back("做一个不让自己后悔的选择（跟）");

    passWords="。。。（出局）";
}

