#ifndef SCENE4PLAYERS_H
#define SCENE4PLAYERS_H
#include<AIplayer.h>
class vdm:public AI
{
public:
     vdm(QString n,int i,QObject *parent=0);
};


class jj:public AI
{
public:
    jj(QString n,int i,QObject *parent=0);
};

class xw:public AI
{
public:
     xw(QString n,int i,QObject *parent=0);
};

class ds:public AI
      {
public:
     ds(QString n,int i,QObject *parent=0);
};
#endif // SCENE4PLAYERS_H
