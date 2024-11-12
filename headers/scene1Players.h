#ifndef SCENE1PLAYERS_H
#define SCENE1PLAYERS_H
#include<AIplayer.h>

class Harry:public AI//通过类的派生写每个角色，便于自定义，形成角色不同行为特征，增加游戏性，scene2players等相同
{
public:
    Harry(QString n,int i,QObject *parent=0);

};

class Hermione:public AI
{
public:
    Hermione(QString n,int i,QObject *parent=0);

};

class Ron:public AI
{
public:
    Ron(QString n,int i,QObject *parent=0);

};

class Malfoy:public AI
{
public:
    Malfoy(QString n,int i,QObject *parent=0);

};

#endif // SCENE1PLAYERS_H
