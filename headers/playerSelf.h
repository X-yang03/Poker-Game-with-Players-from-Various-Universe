#ifndef PLAYERSELF_H
#define PLAYERSELF_H
#include"AIplayer.h"

class playerSelf:public AI //玩家自己
{
public:
    int index=5;
    playerSelf(QString n,int i,QObject *parent);
};

#endif // PLAYERSELF_H
