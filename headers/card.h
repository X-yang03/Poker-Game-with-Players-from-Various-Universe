#ifndef CARD_H
#define CARD_H
#include<QVector>
#include<QString>
#include <QtGlobal>
#include<QTime>
class Card
{
public:

    int index;
    enum Color{spade,heart,diamond,club};               //花色
  
    static QVector<Card*> allCards;                     //按初始排列顺序排列的新牌
    static QVector<Card*> nowCards;                     //洗过之后的牌组


    Color color;                                      //牌的属性
    QString Type;
    int value;
    QString imgPath;


    int getCardValue();
    QString getCardType();
    static void iniAllCards();                                 //初始化allcards
    static void shuffle();                                     //洗牌 给
    static bool singlecmp(Card a, Card b);   //卡牌比较函数

    Card(Color color,QString Type,QString p=0,int value=-1);

    Card();
    ~Card();

};

#endif // CARD_H
