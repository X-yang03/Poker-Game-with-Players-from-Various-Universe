#ifndef DATA_H
#define DATA_H

#define ccard 0
#define HHold 1
#define DDistribute 2
#define CCheck 3
#define UUnseenCmp 4
#define AAddMoney 5
#define SSeenCmp 6
#define PPass 7
#define OOut 8
#define TurnBegein 9

#include<QByteArray>
#include<QString>
class Data
{
public:

    QString data;
    Data(int type,int tar=0,int from=0);

    Data(char c,int tar=0);
    ~Data();

};


#endif // DATA_H
