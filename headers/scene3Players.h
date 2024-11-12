#ifndef SCENE3PLAYERS_H
#define SCENE3PLAYERS_H
#include<AIplayer.h>
class Guda:public AI
{
public:
     Guda(QString n,int i,QObject *parent=0);
};


class Wuniang:public AI
{
public:
     Wuniang(QString n,int i,QObject *parent=0);
};

class Falan:public AI
{
public:
     Falan(QString n,int i,QObject *parent=0);
};

class Wuming:public AI
      {
public:
     Wuming(QString n,int i,QObject *parent=0);
};

#endif // SCENE3PLAYERS_H
