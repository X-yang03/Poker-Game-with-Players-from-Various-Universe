#include"card.h"



QVector<Card*> Card::allCards = {};

QVector<Card*> Card::nowCards = {};

void Card::iniAllCards()
{
    QVector<Card*> tmpCards={
                            new Card(Card::Color::spade,"0",":/cardimages/image/cards/pokerBack.jpg",0),

                            new Card(Card::Color::spade,"2",":/cardimages/image/cards/spade2 .jpg",1),
                            new Card(Card::Color::heart,"2",":/cardimages/image/cards/heart2.jpg",1),
                            new Card(Card::Color::diamond,"2",":/cardimages/image/cards/square2.jpg",1),
                            new Card(Card::Color::club,"2",":/cardimages/image/cards/club2.jpg",1),

                            new Card(Card::Color::spade,"3",":/cardimages/image/cards/spade3.jpg",2),
                            new Card(Card::Color::heart,"3",":/cardimages/image/cards/heart3.jpg",2),
                            new Card(Card::Color::diamond,"3",":/cardimages/image/cards/square3.jpg",2),
                            new Card(Card::Color::club,"3",":/cardimages/image/cards/club3.jpg",2),

                            new Card(Card::Color::spade,"4",":/cardimages/image/cards/spade4.jpg",3),
                            new Card(Card::Color::heart,"4",":/cardimages/image/cards/heart4.jpg",3),
                            new Card(Card::Color::diamond,"4",":/cardimages/image/cards/square4.jpg",3),
                            new Card(Card::Color::club,"4",":/cardimages/image/cards/club4.jpg",3),

                            new Card(Card::Color::spade,"5",":/cardimages/image/cards/spade5.jpg",4),
                            new Card(Card::Color::heart,"5",":/cardimages/image/cards/heart5.jpg",4),
                            new Card(Card::Color::diamond,"5",":/cardimages/image/cards/square5.jpg",4),
                            new Card(Card::Color::club,"5",":/cardimages/image/cards/club5.jpg",4),

                            new Card(Card::Color::spade,"6",":/cardimages/image/cards/spade6.jpg",5),
                            new Card(Card::Color::heart,"6",":/cardimages/image/cards/heart6.jpg",5),
                            new Card(Card::Color::diamond,"6",":/cardimages/image/cards/square6.jpg",5),
                            new Card(Card::Color::club,"6",":/cardimages/image/cards/club6.jpg",5),

                            new Card(Card::Color::spade,"7",":/cardimages/image/cards/spade7.jpg",6),
                            new Card(Card::Color::heart,"7",":/cardimages/image/cards/heart7.jpg",6),
                            new Card(Card::Color::diamond,"7",":/cardimages/image/cards/square7.jpg",6),
                            new Card(Card::Color::club,"7",":/cardimages/image/cards/club7.jpg",6),

                            new Card(Card::Color::spade,"8",":/cardimages/image/cards/spade8.jpg",7),
                            new Card(Card::Color::heart,"8",":/cardimages/image/cards/heart8.jpg",7),
                            new Card(Card::Color::diamond,"8",":/cardimages/image/cards/square8.jpg",7),
                            new Card(Card::Color::club,"8",":/cardimages/image/cards/club8.jpg",7),

                            new Card(Card::Color::spade,"9",":/cardimages/image/cards/spade9.jpg",8),
                            new Card(Card::Color::heart,"9",":/cardimages/image/cards/heart9.jpg",8),
                            new Card(Card::Color::diamond,"9",":/cardimages/image/cards/square9.jpg",8),
                            new Card(Card::Color::club,"9",":/cardimages/image/cards/club9.jpg",8),

                            new Card(Card::Color::spade,"10",":/cardimages/image/cards/spade10.jpg",9),
                            new Card(Card::Color::heart,"10",":/cardimages/image/cards/heart10.jpg",9),
                            new Card(Card::Color::diamond,"10",":/cardimages/image/cards/square10.jpg",9),
                            new Card(Card::Color::club,"10",":/cardimages/image/cards/club10.jpg",9),

                            new Card(Card::Color::spade,"J",":/cardimages/image/cards/spadeJ.jpg",10),
                            new Card(Card::Color::heart,"J",":/cardimages/image/cards/heartJ.jpg",10),
                            new Card(Card::Color::diamond,"J",":/cardimages/image/cards/squareJ.jpg",10),
                            new Card(Card::Color::club,"J",":/cardimages/image/cards/clubJ.jpg",10),

                            new Card(Card::Color::spade,"Q",":/cardimages/image/cards/spadeQ.jpg",11),
                            new Card(Card::Color::heart,"Q",":/cardimages/image/cards/heartQ.jpg",11),
                            new Card(Card::Color::diamond,"Q",":/cardimages/image/cards/squareQ.jpg",11),
                            new Card(Card::Color::club,"Q",":/cardimages/image/cards/clubQ.jpg",11),

                            new Card(Card::Color::spade,"K",":/cardimages/image/cards/spadeK.jpg",12),
                            new Card(Card::Color::heart,"K",":/cardimages/image/cards/heartK.jpg",12),
                            new Card(Card::Color::diamond,"K",":/cardimages/image/cards/squareK.jpg",12),
                            new Card(Card::Color::club,"K",":/cardimages/image/cards/clubK.jpg",12),


                            new Card(Card::Color::spade,"A",":/cardimages/image/cards/spadeA.jpg",13),
                            new Card(Card::Color::heart,"A",":/cardimages/image/cards/heartA.jpg",13),
                            new Card(Card::Color::diamond,"A",":/cardimages/image/cards/squareA.jpg",13),
                            new Card(Card::Color::club,"A",":/cardimages/image/cards/clubA.jpg",13),


    };


 Card::allCards=tmpCards;

};

Card::Card(Color color,QString Type,QString p,int value)
{
    this->color=color;
    this->Type=Type;
    this->value=value;
    this->imgPath=p;

//    this->index=n;
    this->index=(value-1)*4+color+1;
};

QString Card::getCardType()
{
    return Type;
}

int Card::getCardValue()
{
    return value;
}

void Card::shuffle()
{
    nowCards.push_back(allCards[0]);
    int cnt[53] = { 0 };
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 1; i < 53; i++)
    {
        int tmp = qrand() % 52 + 1;
        while (cnt[tmp] == 1)
        {
            tmp = qrand() % 52 + 1;
        }
        cnt[tmp] = 1;

        nowCards.push_back(allCards[tmp]);
    }

}

bool singlecmp(Card *a, Card *b)
{
    return a->value < b->value;
}

Card::Card()
{

}

Card::~Card()
{

}
