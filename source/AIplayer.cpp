#include<AIplayer.h>

int AI::nowPlayers=5;
int AI::nowRound=1;
AI::AI(QString n,int i,QObject *parent):QObject(parent)
{
    name= n;
    index=i;
    roundTime=new QTimer;
    roundTime->setInterval(2500);
    roundTime->setSingleShot(true);

    holdWords.append("我要闷一回合");
    holdWords.append("走着！");
    holdWords.append("闷");

    goOnWords.append("我跟！");
    goOnWords.append("奉陪到底！");
    goOnWords.append("硬碰硬！");

    checkWords.append("我看看牌");
    checkWords.append("我看一眼");
    checkWords.append("let me check my cards now");
    checkWords.append("来点好牌！");
    checkWords.append("来点好运吧……");


    passWords=" ";




};

QString AI::speak_hold()
{

   return holdWords[qrand()%3];

}

QString AI::speak_cmp()
{
    return "来一决雌雄！";
}

QString AI::speak_pass()
{
    return passWords;
}

QString AI::speak_check()
{
    return checkWords[qrand()%5];
}

QString AI::speak_goOn()
{
    return goOnWords[qrand()%3];
}

void AI::checkValue()
{
    this->cardSort();          //先对手牌排序
    if (ownCard[0]->color == ownCard[1]->color && ownCard[1]->color == ownCard[2]->color) //事先对花色判断是否为清一色
    {
        this->pokerValue += 80;
    }

    if (ownCard[0]->value< ownCard[1]->value || ownCard[1]->value < ownCard[2]->value)//非豹子牌（也称金花牌，即三张牌数值相同）

    {
        if (ownCard[0]->value == ownCard[1]->value || ownCard[1]->value == ownCard[2]->value)//评判对子牌大小
        {
            this->pokerValue += 30;//单牌value最高不超过30
            this->pokerValue += (2 * ownCard[1]->value + (ownCard[0]->value == ownCard[1]->value ? ownCard[2]->value : ownCard[0]->value) / 10.0);
            //中间ownCard[1]必为对子牌中一张，因此对子牌数值=30+对子牌值*2+单牌值/10，范围在（32.3（223）~57.2（AAK））
            return;
        }
        else
            if (ownCard[1]->value - ownCard[0]->value > 1 || ownCard[2]->value - ownCard[1]->value > 1)//单牌的大小评判

            {
                this->pokerValue += (2 * ownCard[2]->value+ownCard[1]->value/10.0+ownCard[0]->value/1000.0);
                //赋予每张牌不同权重，范围在（10.302（235）~27.21（JKA））
                return;
            }
            else //此时是顺子牌
            {
                this->pokerValue += 60;//比顺子低等级牌最高value不超过60
                this->pokerValue += (ownCard[2]->value);//加中值比较合理，范围在（62（234）~72（QKA））

                return;
            }

    }
    else//此时为豹子
    {
        this->pokerValue = 200;//非豹子牌最大为同花QKA，value=152
        this->pokerValue += ownCard[2]->value;//范围在（201（222）~213（AAA））
        return;
    }


}

void AI::getCards()
{
    for (int i = 0; i < 3; i++)
        {
            this->ownCard[i] = Card::nowCards[this->index + 5 * i];
        }
}

void AI::cardSort()
{
    for(int i=0;i<2;i++)
    {
        for(int j=i+1;j<3;j++)
        {
            if(ownCard[i]->value>ownCard[j]->value)
            {
                Card *tmp=ownCard[i];
                ownCard[i]=ownCard[j];
                ownCard[j]=tmp;

            }
        }
    }
}

int getPossibility()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    qDebug()<<rand();
    return rand() % 100;
}

QString AI::act()
{
    if(AI::nowPlayers==2&&this->isActive&&this->gamblerLevel>5)
       enterGamblerMode();

    if (!ifSeen) //没有看之前可以选择 闷 闷开 看牌
    {
        if (getPossibility() <= possibility_hold)    //先判断是否看牌
        {

            if(getPossibility()<=possibility_hold)   //判断是否闷开
            {

               return this->name+this->speak_hold();
            }
            else if(nowRound>1)
            {
                            emit unseenCmp(this);
                            return " 闷开结束 ";
               }
            else
            {
                 return this->name+this->speak_hold();
            }


        }


            else             //进行看牌
            {
                ifSeen=1;
                if(getPossibility()<=possibility_seenPass) //是否弃牌
                {
                    this->isActive=0;
                    nowPlayers--;
                    return this->name+this->speak_pass();
                }
                else
                {

                    if(getPossibility()<=possibility_addMoney)   //是否跟牌
                        return this->name+this->speak_goOn();
                    else
                    {
                        emit seenCmp(this);         //进行开牌
                        return "开牌结束 ";
                    }
                }
            }



    }

    else
    {
        if(getPossibility()<=possibility_seenPass) //是否弃牌
        {
            this->isActive=0;
            nowPlayers--;
            return this->name+this->speak_pass();
        }
        else
        {
            if(getPossibility()<=possibility_addMoney)   //是否跟牌
                return this->name+this->speak_goOn();
            else
            {
                emit seenCmp(this);         //进行开牌
                return "开牌结束";
            }
        }


        }
    return this->act();
    }

void AI::enterGamblerMode()
{
    if(ifSeen)
    {
        if(this->possibility_seenPass>30)
            this->possibility_seenPass=30-2*this->gamblerLevel;
        if(this->possibility_addMoney<50&&AI::nowRound<10)
        {
            this->possibility_addMoney=50+this->pokerValue/2+2*this->gamblerLevel-AI::nowRound;
        }
        if(AI::nowRound>9)
        {
            this->possibility_seenCmp=this->gamblerLevel*(-27)+253;
        }

    }
    if(!ifSeen)
    {
        if(this->possibility_seenPass>30)
            this->possibility_seenPass=30-2*this->gamblerLevel;
        if(this->possibility_hold<50&&AI::nowRound<10)
        {
            this->possibility_hold=50+this->gamblerLevel*2-AI::nowRound;
            this->possibility_unseenCmp=(-20)*this->gamblerLevel+210;
            this->possibility_addMoney=50+this->pokerValue/2+2*this->gamblerLevel-AI::nowRound;

        }
        if(AI::nowRound>9)
        {
            this->possibility_hold=30+4*this->gamblerLevel;
            this->possibility_seenCmp=this->gamblerLevel*(-27)+253;
        }
    }

}


AI::~AI()
{
    this->roundTime->stop();
    delete this->roundTime;
}

