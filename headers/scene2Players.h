#ifndef SCENE2PLAYERS_H
#define SCENE2PLAYERS_H
#include<AIplayer.h>

class Eren:public AI
{
public:
    Eren(QString n,int i,QObject *parent=0);



};

class Mikasa:public AI
{
public:
    Mikasa(QString n,int i,QObject *parent=0);

};

class Reiner:public AI
{
public:
    Reiner(QString n,int i,QObject *parent=0);

};

class Rivaille:public AI
{
public:
    Rivaille(QString n,int i,QObject *parent=0);

};



#endif // SCENE2PLAYERS_H
