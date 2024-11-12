#include"scene4Players.h"
vdm::vdm(QString n,int i,QObject *parent):AI(n,i,parent)//最终关卡中所有ai进行开牌操作的概率都极低
{
    name=n;
    index=i;
    this->possibility_hold=65;//属性与harry几乎一致
    this->possibility_unseenCmp=10;
    this->possibility_seenPass=10;
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=10;
    this->possibility_addMoney=60;
    gamblerLevel=7;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("老夫我闷一把");
    holdWords.push_back("我的魔法将把你撕成碎片！（闷）");
    holdWords.push_back("我的牌法出神入化！（闷）");

    goOnWords.push_back("打的不错（跟）");
    goOnWords.push_back("回家哭鼻子去吧！（跟）");
    goOnWords.push_back("哈哈哈哈哈（跟）");

    passWords="阿瓦达……（出局）";

}

jj::jj(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=60;//莽撞型玩家
    this->possibility_unseenCmp=10;
    this->possibility_seenPass=0;
    this->possibility_beenSeenCmp=20;
    this->possibility_beenUnseenCmp=20;
    this->possibility_seenCmp=10;
     this->possibility_addMoney=40;
    gamblerLevel=9;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("Rumbling！（闷）");
    holdWords.push_back("巨人闷牌！");
    holdWords.push_back("还是闷");

    goOnWords.push_back("塔塔开，一直摸塔塔开！（跟）");
    goOnWords.push_back("一个不留的，都驱逐出去！（跟）");
    goOnWords.push_back("走着！");

    passWords="海的那边……（出局）";
}

xw::xw(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=30;
    this->possibility_unseenCmp=10;
    this->possibility_seenPass=10;
    this->possibility_beenSeenCmp=30;
    this->possibility_beenUnseenCmp=30;
    this->possibility_seenCmp=10;
    this->possibility_addMoney=60;
    gamblerLevel=3;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("闷");
    holdWords.push_back("闷！");
    holdWords.push_back("薪王的闷牌！");

    goOnWords.push_back("颤抖吧灰烬（跟）");
    goOnWords.push_back("跟注！");
    goOnWords.push_back("继续！（跟）");

    passWords="火已将熄……（出局）";
}

ds::ds(QString n,int i,QObject *parent):AI(n,i,parent)
{
    name=n;
    index=i;
    this->possibility_hold=70;
    this->possibility_unseenCmp=10;
    this->possibility_seenPass=0;
    this->possibility_beenSeenCmp=0;
    this->possibility_beenUnseenCmp=0;
    this->possibility_seenCmp=10;
    this->possibility_addMoney=80;
    gamblerLevel=8;

    holdWords.clear();
    goOnWords.clear();

    holdWords.push_back("重开吧小伙子（闷）");
    holdWords.push_back("你将输的一干二净！（闷）");
    holdWords.push_back("我的赌技出神入化！");

    goOnWords.push_back("奉陪到底！跟！");
    goOnWords.push_back("我继续加注！（跟）");
    goOnWords.push_back("玩的起吗！（跟）");

    passWords="我可是赌神。。（出局）";
}

