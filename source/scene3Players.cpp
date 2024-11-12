#include"scene3Players.h"
Guda::Guda(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=50;//中庸选手
    this->possibility_unseenCmp=50;
    this->possibility_seenPass=20;
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=50;
    this->possibility_addMoney=60;
    gamblerLevel=4;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷一把");
    holdWords.push_back("我闷");
    holdWords.push_back("你的第一关就是我!(闷)");

    goOnWords.push_back("我的跟牌和我的军体拳一样强!");
    goOnWords.push_back("还记得与我战斗的次数吗灰烬（跟）");
    goOnWords.push_back("我的跟牌你可不能弹反（跟）");

    passWords="我的魂！……（出局）";

}

Wuniang::Wuniang(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=65;//神经型玩家
    this->possibility_unseenCmp=20;
    this->possibility_seenPass=20;
    this->possibility_beenSeenCmp=30;
    this->possibility_beenUnseenCmp=30;
    this->possibility_seenCmp=30;
     this->possibility_addMoney=60;
    gamblerLevel=8;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷！");
    holdWords.push_back("闷一局");
    holdWords.push_back("还是闷");

    goOnWords.push_back("舞动青春！跟！");
    goOnWords.push_back("洛斯里克的加注");
    goOnWords.push_back("走着！");

    passWords="征战骑士的荣耀……（出局）";
}

Falan::Falan(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=30;
    this->possibility_unseenCmp=40;
    this->possibility_seenPass=35;
    this->possibility_beenSeenCmp=30;
    this->possibility_beenUnseenCmp=30;
    this->possibility_seenCmp=40;
    this->possibility_addMoney=20;
    gamblerLevel=7;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("不死队之闷牌！");
    holdWords.push_back("我的闷牌无人可敌");
    holdWords.push_back("薪王的闷牌！");

    goOnWords.push_back("你要跳舞吗（跟）");
    goOnWords.push_back("再来一回合！（跟）");
    goOnWords.push_back("打牌不如街舞（跟）");

    passWords="火已将熄（出局）";
}

Wuming::Wuming(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=40;//财产殷实
    this->possibility_unseenCmp=20;
    this->possibility_seenPass=10;
    this->possibility_beenSeenCmp=10;//没人敢开
    this->possibility_beenUnseenCmp=10;
    this->possibility_seenCmp=20;
    this->possibility_addMoney=90;
    gamblerLevel=7;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷");
    holdWords.push_back("王者的闷牌");
    holdWords.push_back("还闷！");

    goOnWords.push_back("奉陪到底！跟！");
    goOnWords.push_back("王者跟牌！");
    goOnWords.push_back("GO ON!（跟）");

    passWords="。。。。（无名出局）";
}

