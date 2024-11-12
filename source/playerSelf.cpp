#include"playerSelf.h"
playerSelf::playerSelf(QString n,int i,QObject *parent):AI(n,i,parent)
{
    index=i;
    getCards();
    checkValue();
    possibility_beenSeenCmp=35;
    possibility_beenUnseenCmp=30;

}


