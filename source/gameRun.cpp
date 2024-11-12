#include"gameRun.h"
gameRun::gameRun(QObject *parent):QObject(parent)
{
    bgmList=new QMediaPlaylist(); //设置bgm
    bgm =new QMediaPlayer(this);
    bgm->setVolume(30);
    setBgm();
    bgm->play();

    playerState=nullptr;
    dt=nullptr;

    name={};

    gameWidget=nullptr;    //gamewidget未加载，设置为空指针

    welcomeWidget=new welcomeScene;  //新建欢迎界面
    welcomeWidget->startGame->installEventFilter(this);
    welcomeWidget->quitGame->installEventFilter(this);
    welcomeWidget->help->installEventFilter(this);
    welcomeWidget->cNt->installEventFilter(this);
    welcomeWidget->show();

    myServer=new server;
    chooseScene=new sceneChoose;       //新建选择关卡界面
    chooseScene->btn1->installEventFilter(this);
    chooseScene->btn2->installEventFilter(this);
    chooseScene->btn3->installEventFilter(this);

    chooseScene->btn4->setEnabled(false);//第四关在赢得前三关后解锁
//    chooseScene->btn4->installEventFilter(this);

    helpWidget=new help();
    helpWidget->back->installEventFilter(this);

    Card::iniAllCards();//初始化纸牌

    player1=nullptr;
    player2=nullptr;
    player3=nullptr;
    player4=nullptr;


    QObject::connect(welcomeWidget->startGame,&myButton::clicked,this,&gameRun::welcomeToGame);
    QObject::connect(welcomeWidget->quitGame,&myButton::clicked,[=]()
    {
        welcomeWidget->quitGame->zoomIn();
        welcomeWidget->quitGame->zoomOut();
        QTimer::singleShot(400,this,[=](){
            welcomeWidget->close();
            delete this;

        });
    });//gamma函数的运用

    QObject::connect(welcomeWidget->help,&myButton::clicked,[=]()
    {
        welcomeWidget->help->zoomIn();
        welcomeWidget->help->zoomOut();
        QTimer::singleShot(400,this,[=](){

            welcomeWidget->close();
            helpWidget->show();


        });
    });

    QObject::connect(helpWidget->back,&myButton::clicked,[=]()
    {
        helpWidget->back->zoomIn();
        helpWidget->back->zoomOut();
        QTimer::singleShot(400,this,[=](){

            helpWidget->close();
            welcomeWidget->show();


        });
    });

    QObject::connect(welcomeWidget->cNt,&myButton::clicked,[=]()
    {
        welcomeWidget->cNt->zoomIn();
        welcomeWidget->cNt->zoomOut();
        QTimer::singleShot(400,this,[=](){

            welcomeWidget->close();
            myServer->show();


        });
    });
    QObject::connect(chooseScene->btn1,&QPushButton::clicked,this,&gameRun::loadScene1);//每个按钮对应一关
    QObject::connect(chooseScene->btn2,&QPushButton::clicked,this,&gameRun::loadScene2);
    QObject::connect(chooseScene->btn3,&QPushButton::clicked,this,&gameRun::loadScene3);
    QObject::connect(chooseScene->btn4,&QPushButton::clicked,this,&gameRun::loadScene4);

    QObject::connect(this,&gameRun::myTurnOver,this,&gameRun::player1TurnBegin);

    QObject::connect(myServer,&server::cnt_clicked,this,&gameRun::connectCliked);
    QObject::connect(myServer,&server::join_clicked,this,&gameRun::joinCliked);
}


void gameRun::player1TurnOver()
{
    player1->roundTime->stop();  //计时器停止
    gameWidget->roundInfo->addItem(player1->act());//录入ai的语言
    if(player1->isActive&&player1->ifSeen)   //根据ai的状态判定其下注
    {
        moneypool+=valSeen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));   //信息更新
    }
    if(player1->isActive&&!player1->ifSeen)
    {
        moneypool+=valUnseen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(!player1->isActive) //出局后设置头像，只会进行一次
    {
        gameWidget->player1->setPixmap(*p1out);
    }
    ifWon(); //判断该ai进行了相应操作后游戏是否结束
    gameWidget->roundInfo->setCurrentRow(gameWidget->roundInfo->count()-1);
    if(!ifEnd)
      player2TurnBegin();
}

void gameRun::player2TurnOver()
{
    player2->roundTime->stop();
    gameWidget->roundInfo->addItem(player2->act());
    if(player2->isActive&&player2->ifSeen)
    {
        moneypool+=valSeen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(player2->isActive&&!player2->ifSeen)
    {
        moneypool+=valUnseen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(!player2->isActive)
    {
        gameWidget->player2->setPixmap(*p2out);
    }
    ifWon();
    gameWidget->roundInfo->setCurrentRow(gameWidget->roundInfo->count()-1);
    if(!ifEnd)
        player3TurnBegin();
}

void gameRun::player3TurnOver()
{
    player3->roundTime->stop();
    gameWidget->roundInfo->addItem(player3->act());
    if(player3->isActive&&player3->ifSeen)
    {
        moneypool+=valSeen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(player3->isActive&&!player3->ifSeen)
    {
        moneypool+=valUnseen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(!player3->isActive)
    {
        gameWidget->player3->setPixmap(*p3out);
    }
    ifWon();
    gameWidget->roundInfo->setCurrentRow(gameWidget->roundInfo->count()-1);
    if(!ifEnd)
        player4TurnBegin();

}

void gameRun::player4TurnOver()
{
    player4->roundTime->stop();
    gameWidget->roundInfo->addItem(player4->act());
    if(player4->isActive&&player4->ifSeen)
    {
        moneypool+=valSeen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(player4->isActive&&!player4->ifSeen)
    {
        moneypool+=valUnseen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    }
    if(!player4->isActive)
    {
        gameWidget->player4->setPixmap(*p4out);
    }
    ifWon();
    gameWidget->roundInfo->setCurrentRow(gameWidget->roundInfo->count()-1);
    if(AI::nowPlayers>1)
        myTurnBegin();
}

void gameRun::myTurnBegin()
{
    AI::nowRound++;
    gameWidget->roundInfo->addItem("这是第"+QString::number(AI::nowRound)+"回合");
    if(self->isActive&&myMoney>0) //判断是否出局
    {
        gameWidget->roundInfo->addItem("你的回合");
        btnsSetTrue();
        if(self->ifSeen)  //已看牌后不可闷牌
        {
           gameWidget->hold->setEnabled(false);
           gameWidget->hold->removeEventFilter(this);
        }
        return;
    }
    else
    {
        if(!ifEnd)
        {gameWidget->roundInfo->addItem("你已出局");

         emit myTurnOver();}
    }

}

void gameRun::player1TurnBegin()
{
    ifWon(); //在玩家进行操作后判断游戏是否结束
    if(self->isActive&&myMoney<0)
    {
        self->isActive=0;
        gameWidget->roundInfo->addItem("哟哟哟，没钱啦？重开吧！");//进行嘲讽
    }
    if(player1->isActive) //判断ai是否出局
   {
        player1->roundTime->start();
   }
    else
    {
        if(!ifEnd)
        player2TurnBegin();
    }
}

void gameRun::player2TurnBegin()
{
//    ifWon();
    if(player2->isActive)
    {
        player2->roundTime->start();
    }
    else
    {
        if(!ifEnd)
        player3TurnBegin();
    }
}

void gameRun::player3TurnBegin()
{
//    ifWon();
    if(player3->isActive)
    {
       player3->roundTime->start();
    }
    else
         if(!ifEnd)
        player4TurnBegin();
}

void gameRun::player4TurnBegin()
{
    ifWon();
    if(player4->isActive)
    {
       player4->roundTime->start();
    }
    else
        if(!ifEnd)
        myTurnBegin();
}

void gameRun::holdClicked()
{
    gameWidget->hold->zoomIn();
    gameWidget->hold->zoomOut();
    myMoney-=valUnseen;
    moneypool+=valUnseen;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

    btnsSetFalse();
    emit myTurnOver();
}

void gameRun::holdOnline()
{
    gameWidget->hold->zoomIn();
    gameWidget->hold->zoomOut();

    myMoney-=valUnseen;
    moneypool+=valUnseen;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
     btnsSetFalse();

     if(isServer)
     {


      dt=new Data(HHold,0,1);
         for(int i=0;i<myServer->ClientList.size();i++)
         {
             myServer->ClientList.at(i)->write(dt->data.toUtf8());

         }
         delete dt;

        NextTurn();
     }

     else
     {
          Data data(HHold,0,playerIndex);
          myServer->Socket->write(data.data.toUtf8());

          NextTurn();

     }
}


void gameRun::checkClicked()
{
    self->ifSeen=1;
    gameWidget->check->zoomIn();
    gameWidget->check->zoomOut();
    showCards(self);
    QTimer::singleShot(400,this,[=](){

        gameWidget->seen_cmp->pix->load(":/button/image/buttons/seenCmp.png");
        *gameWidget->seen_cmp->pix = gameWidget->seen_cmp->pix->scaled(100, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->seen_cmp->pixHover->load(":/button/image/buttons/seenCmpHover.png");
        *gameWidget->seen_cmp->pixHover = gameWidget->seen_cmp->pixHover->scaled(100*1.1, 90*1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->check->setIcon(*gameWidget->seen_cmp->pix);

        gameWidget->addMoney->pix->load(":/button/image/buttons/addMoney.png");
       *gameWidget->addMoney->pix = gameWidget->addMoney->pix->scaled(100, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->addMoney->pixHover->load(":/button/image/buttons/addMoneyHover.png");
        *gameWidget->addMoney->pixHover = gameWidget->addMoney->pixHover->scaled(100*1.1, 90*1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->unseen_cmp->setIcon(*gameWidget->addMoney->pix);

           });


    QObject::disconnect(gameWidget->unseen_cmp,&QPushButton::clicked,this,&gameRun::unseenCmpClicked);//因为闷开按钮和加注按钮为同一按钮，需要重新连接信号和槽
    QObject::disconnect(gameWidget->check,&QPushButton::clicked,this,&gameRun::checkClicked);
    QObject::connect(gameWidget->check,&myButton::clicked,this,&gameRun::seenCmpClicked);
    QObject::connect(gameWidget->addMoney,&myButton::clicked,this,&gameRun::addMoneyClicked);

    gameWidget->addMoney->setEnabled(true);
    gameWidget->addMoney->installEventFilter(this);
    gameWidget->hold->setEnabled(false);
    gameWidget->hold->removeEventFilter(this);
    gameWidget->roundInfo->addItem("your card:"+self->ownCard[0]->Type+self->ownCard[1]->Type+self->ownCard[2]->Type);

}

void gameRun::check()
{
    self->ifSeen=true;
    gameWidget->check->zoomIn();
    gameWidget->check->zoomOut();
    showCards(self);
    QTimer::singleShot(400,this,[=](){

        gameWidget->seen_cmp->pix->load(":/button/image/buttons/seenCmp.png");
        *gameWidget->seen_cmp->pix = gameWidget->seen_cmp->pix->scaled(100, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->seen_cmp->pixHover->load(":/button/image/buttons/seenCmpHover.png");
        *gameWidget->seen_cmp->pixHover = gameWidget->seen_cmp->pixHover->scaled(100*1.1, 90*1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->check->setIcon(*gameWidget->seen_cmp->pix);

        gameWidget->addMoney->pix->load(":/button/image/buttons/addMoney.png");
       *gameWidget->addMoney->pix = gameWidget->addMoney->pix->scaled(100, 90, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->addMoney->pixHover->load(":/button/image/buttons/addMoneyHover.png");
        *gameWidget->addMoney->pixHover = gameWidget->addMoney->pixHover->scaled(100*1.1, 90*1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        gameWidget->unseen_cmp->setIcon(*gameWidget->addMoney->pix);

         QObject::disconnect(gameWidget->unseen_cmp,&QPushButton::clicked,this,&gameRun::unseenCmpOnline);
         QObject::connect(gameWidget->addMoney,&myButton::clicked,this,&gameRun::addMoneyClicked);

         QObject::disconnect(gameWidget->check,&QPushButton::clicked,this,&gameRun::check);
         QObject::connect(gameWidget->check,&myButton::clicked,this,&gameRun::seenCmpOnline);

           });
    if(isServer)
    {
     Data data(CCheck,0,1);
    for(int i=2;i<myServer->ClientList.size();i++)
    {
        myServer->ClientList.at(i)->write(data.data.toUtf8());
    }
    }

    else
    {
         Data data(CCheck,0,playerIndex);
        myServer->Socket->write(data.data.toUtf8());
    }

}

void gameRun::ifWon()
{
    if(!netState)
    {
        if(AI::nowPlayers==1)
    {
        ifEnd=true;  //设置游戏结束
        showResult();
        stop();
    }
    else
        return;
    }
    else
    {
        if(self->nowPlayers==1)
        {

            int winner;
            if(player1->isActive)
                winner=2;
            else if(player2->isActive)
                winner=3;
            else if(player3->isActive)
                winner=4;
            else if(player4->isActive)
                winner=5;
            else winner=1;
            Data data('w',winner);
            for(int i=0;i<myServer->ClientList.size();i++)
            {
                myServer->ClientList.at(i)->write(data.data.toUtf8());
            }
            if(winner==1)
            {
                myMoney+=moneypool;//钱池中金币归玩家所有
                moneypool=0;
                gameWidget->coin->setText("你的金币："+QString::number(myMoney));
                gameWidget->nowMoney->setText("钱池："+QString::number(moneypool));
            }
            else
            {
                moneypool=0;
                gameWidget->nowMoney->setText("钱池："+QString::number(moneypool));
                gameWidget->roundInfo->addItem(name[winner]+"获得了胜利！");
                gameWidget->roundInfo->scrollToBottom();
            }

        }
        else
            return;
    }
}

void gameRun::showResult()
{
    QString winner;
    if(player1->isActive)winner=player1->name;
    if(player2->isActive)winner=player2->name;
    if(player3->isActive)winner=player3->name;
    if(player4->isActive)winner=player4->name;
    if(self->isActive){

        winner=self->name;
        myMoney+=moneypool;//钱池中金币归玩家所有
        moneypool=0;
        gameWidget->coin->setText("你的金币："+QString::number(myMoney));
        gameWidget->nowMoney->setText("钱池："+QString::number(moneypool));
        if(scene==1)
            win1=true;
        else  if(scene==2)
                win2=true;
        else  if(scene==3)
                win3=true;

    }

    gameWidget->roundInfo->addItem(winner+"获胜！！！");


    if(win1&&win2&&win3)
    {
        chooseScene->btn4->setEnabled(true);
        chooseScene->btn4->installEventFilter(this);
    }
    moneypool=0;
   showCards(self);
   showCards(player1);
   showCards(player2);
   showCards(player3);
   showCards(player4);
   btnsSetFalse();
   gameWidget->roundInfo->setCurrentRow(gameWidget->roundInfo->count()-1);

}

void gameRun::passClicked()
{
    gameWidget->pass->zoomIn();
    gameWidget->pass->zoomOut();
    AI::nowPlayers--;
    self->isActive=0;
    gameWidget->roundInfo->addItem("你选择了弃牌 出局");
    btnsSetFalse();
    emit myTurnOver();
}

void gameRun::passOnline()
{
    gameWidget->pass->zoomIn();
    gameWidget->pass->zoomOut();
    nowOnlinePlayers--;
    if(isServer)
        {
        Data data(PPass,0,1);
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(data.data.toUtf8());
        }
        self->nowPlayers--;
        gameWidget->roundInfo->addItem("你选择弃牌出局！");
        gameWidget->roundInfo->scrollToBottom();

        }

        else
        {
             Data data(PPass,0,playerIndex);
            myServer->Socket->write(data.data.toUtf8());
        }
    self->isActive=false;
    btnsSetFalse();
    NextTurn();
}

void gameRun::unseenCmpClicked()
{
    gameWidget->roundInfo->addItem("请选择你要比牌的对象（点击头像）");

    myMoney-=valUnseen;
    moneypool+=valUnseen;

    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

    gameWidget->unseen_cmp->zoomIn();
    gameWidget->unseen_cmp->zoomOut();

    if(player1->isActive)
           gameWidget->player1->installEventFilter(this);
    if(player2->isActive)
           gameWidget->player2->installEventFilter(this);
    if(player3->isActive)
           gameWidget->player3->installEventFilter(this);
    if(player4->isActive)
           gameWidget->player4->installEventFilter(this);
    btnsSetFalse();

}

void gameRun::unseenCmpOnline()
{
    gameWidget->roundInfo->addItem("请选择你要比牌的对象（点击头像）");


    myMoney-=valUnseen;
    moneypool+=valUnseen;

    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

    gameWidget->unseen_cmp->zoomIn();
    gameWidget->unseen_cmp->zoomOut();

    if(player1->isActive)
           gameWidget->player1->installEventFilter(this);
    if(player2->isActive)
           gameWidget->player2->installEventFilter(this);
    if(player3->isActive)
           gameWidget->player3->installEventFilter(this);
    if(player4->isActive)
           gameWidget->player4->installEventFilter(this);
    btnsSetFalse();

}

void gameRun::seenCmpClicked()
{
    gameWidget->roundInfo->addItem("请选择你要比牌的对象（点击头像）");
    myMoney-=valSeen;
    moneypool+=valSeen;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    gameWidget->seen_cmp->zoomIn();
    gameWidget->seen_cmp->zoomOut();
    if(player1->isActive)
           gameWidget->player1->installEventFilter(this);
    if(player2->isActive)
           gameWidget->player2->installEventFilter(this);
    if(player3->isActive)
           gameWidget->player3->installEventFilter(this);
    if(player4->isActive)
           gameWidget->player4->installEventFilter(this);
   btnsSetFalse();
}

void gameRun::seenCmpOnline()
{
    gameWidget->roundInfo->addItem("请选择你要比牌的对象（点击头像）");

    myMoney-=valSeen;
    moneypool+=valSeen;

    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));



    gameWidget->unseen_cmp->zoomIn();
    gameWidget->unseen_cmp->zoomOut();

    if(player1->isActive)
           gameWidget->player1->installEventFilter(this);
    if(player2->isActive)
           gameWidget->player2->installEventFilter(this);
    if(player3->isActive)
           gameWidget->player3->installEventFilter(this);
    if(player4->isActive)
           gameWidget->player4->installEventFilter(this);
    btnsSetFalse();
}

void gameRun::addMoneyClicked()
{

        myMoney-=valSeen;
    moneypool+=valSeen;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));


    gameWidget->addMoney->zoomIn();
    gameWidget->addMoney->zoomOut();
    btnsSetFalse();

    if(netState)
    {
        if(isServer)
        {

            Data data(AAddMoney,0,1);
            for(int i=0;i<myServer->ClientList.size();i++)
            {
                myServer->ClientList.at(i)->write(data.data.toUtf8());

            }

           NextTurn();
            return;

        }
        else
        {
            Data data(AAddMoney,0,playerIndex);
            myServer->Socket->write(data.data.toUtf8());
            NextTurn();
            return;
        }

    }


    emit myTurnOver();
}


void gameRun::backClicked()
{
    gameWidget->esc->back->zoomIn();
    gameWidget->esc->back->zoomOut();
    QTimer::singleShot(400,this,[=](){

        gameWidget->esc->close();

        stop();

        gameWidget->close();
        delete gameWidget;

        delete player1;
        delete player2;
        delete player3;
        delete player4;
        delete self;

        player1=nullptr;
        player2=nullptr;
        player3=nullptr;
        player4=nullptr;

        delete p1out;
        delete p2out;
        delete p3out;
        delete p4out;
        p1out =nullptr;
        p2out =nullptr;
        p3out =nullptr;
        p4out =nullptr;

        self=nullptr;

        Card::nowCards={};//需要重新洗牌
        welcomeWidget->show();
        bgm->setMedia(bgmList->media(0));
        bgm->play();

        if(netState)
        {
            if(isServer)
            {
                Data data('c',1);
                for(int i=0;i<myServer->ClientList.size();i++)
                {
                    myServer->ClientList.at(i)->write(data.data.toUtf8());
                }
                for(int i=0;i<myServer->ClientList.size();i++)
                {
                    myServer->ClientList.at(i)->close();
                }
                myServer->ClientList.clear();
                myServer->Server->disconnect();
                myServer->close();

                netState=false;

            }
            else
            {
                Data data('c',playerIndex);
                myServer->Socket->write(data.data.toUtf8());




            }
        }
});
}

void gameRun::againClicked()
{
    gameWidget->esc->again->zoomIn();
    gameWidget->esc->again->zoomOut();
    if(!netState)
    {
    QTimer::singleShot(400,this,[=](){

        gameWidget->close();
        delete gameWidget;

        delete self;
        delete player1;
        delete player2;
        delete player3;
        delete player4;

        delete p1out;
        delete p2out;
        delete p3out;
        delete p4out;
        p1out =nullptr;
        p2out =nullptr;
        p3out =nullptr;
        p4out =nullptr;

        self=nullptr;

        player1=nullptr;
        player2=nullptr;
        player3=nullptr;
        player4=nullptr;
        Card::nowCards={};
        switch (this->scene) {
        case 1:loadScene1();break;
        case 2:loadScene2();break;
        case 3:loadScene3();break;
        case 4:loadScene4();break;
        default:break;

        }







});
   }
    else
    {
        if(isServer)
        {
        QTimer::singleShot(400,this,[=](){

            gameWidget->close();
            delete gameWidget;

            delete self;
            delete player1;
            delete player2;
            delete player3;
            delete player4;

            delete p1out;
            delete p2out;
            delete p3out;
            delete p4out;
            p1out =nullptr;
            p2out =nullptr;
            p3out =nullptr;
            p4out =nullptr;

            self=nullptr;

            player1=nullptr;
            player2=nullptr;
            player3=nullptr;
            player4=nullptr;
            Card::nowCards={};
            loadOnline();
            for(int i=0;i<myServer->ClientList.size();i++)
            {
                Data data('a');
                myServer->ClientList.at(i)->write(data.data.toUtf8());
                if(i==0)
                {
                    player1->getCards();
                    player1->checkValue();
                    for(int k=0;k<3;k++)
                    {
                        Data  cdt(ccard,k,player1->ownCard[k]->index);
                        myServer->ClientList.at(0)->write(cdt.data.toUtf8());
                    }
                }
                else if(i==1)
                {
                    player2->getCards();
                    player2->checkValue();
                    for(int k=0;k<3;k++)
                    {
                        Data  cdt(ccard,k,player2->ownCard[k]->index);
                        myServer->ClientList.at(1)->write(cdt.data.toUtf8());
                    }
                }
                else if(i==2)
                {
                    player3->getCards();
                    player3->checkValue();
                    for(int k=0;k<3;k++)
                    {
                        Data  cdt(ccard,k,player3->ownCard[k]->index);
                        myServer->ClientList.at(2)->write(cdt.data.toUtf8());
                    }
                }
                else if(i==3)
                {
                    player4->getCards();
                    player4->checkValue();
                    for(int k=0;k<3;k++)
                    {
                        Data  cdt(ccard,k,player4->ownCard[k]->index);
                        myServer->ClientList.at(3)->write(cdt.data.toUtf8());
                    }
                }


            }


            btnsSetTrue();


    });
        }
        else
        {
            gameWidget->esc->close();
        }
    }


}


bool gameRun::eventFilter(QObject *obj, QEvent *event) //事件过滤器，实现悬停以及label可被点击
{
    if(obj==welcomeWidget->startGame)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            welcomeWidget->startGame->primeHover();
            return true;
        }
        if(event->type()==QEvent::HoverLeave)
        {

            welcomeWidget->startGame->rev();
            return true;
        }
    }
    else if(obj==welcomeWidget->quitGame)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            welcomeWidget->quitGame->primeHover();
            return true;
        }
        if(event->type()==QEvent::HoverLeave)
        {

            welcomeWidget->quitGame->rev();
            return true;
        }
    }

    else if(obj==welcomeWidget->help)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            welcomeWidget->help->primeHover();
            return true;
        }
        if(event->type()==QEvent::HoverLeave)
        {

            welcomeWidget->help->rev();
            return true;
        }
    }

    else if(obj==welcomeWidget->cNt)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            welcomeWidget->cNt->primeHover();
            return true;
        }
        if(event->type()==QEvent::HoverLeave)
        {

            welcomeWidget->cNt->rev();
            return true;
        }
    }

    else if(obj==chooseScene->btn1)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                chooseScene->btn1->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                chooseScene->btn1->rev();
                return true;
            }
        }
    else if(obj==chooseScene->btn3)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                chooseScene->btn3->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                chooseScene->btn3->rev();
                return true;
            }
        }
    else if(obj==chooseScene->btn2)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                chooseScene->btn2->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                chooseScene->btn2->rev();
                return true;
            }
        }

    else if(obj==chooseScene->btn4)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                chooseScene->btn4->primeHover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                chooseScene->btn4->rev();
                return true;
            }
        }

    else if(obj==helpWidget->back)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                helpWidget->back->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                helpWidget->back->rev();
                return true;
            }
        }



    else if(obj==gameWidget->hold)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            gameWidget->hold->hover();
            return true;
        }
        if(event->type()==QEvent::HoverLeave)
        {

            gameWidget->hold->rev();
            return true;
        }
    }

    else if(obj==gameWidget->check)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->check->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->check->rev();
                return true;
            }
        }

   else if(obj==gameWidget->pass)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->pass->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->pass->rev();
                return true;
            }
        }
    else if(obj==gameWidget->unseen_cmp)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->unseen_cmp->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->unseen_cmp->rev();
                return true;
            }
        }
    else if(obj==gameWidget->seen_cmp)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->seen_cmp->hover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->seen_cmp->rev();
                return true;
            }
        }
    else if(obj==gameWidget->player1)
    {
             if (event->type() == QEvent::MouseButtonPress) //鼠标点击
             {
                 QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

                 if(mouseEvent->button() == Qt::LeftButton)
                 {
                     if(!netState)
                     {
                     if(self->ifSeen)
                         showCards(player1);
                     gameWidget->roundInfo->addItem("你选择了"+player1->name);
                     valueCmp(self,gameRun::player1);
                     gameWidget->player1->removeEventFilter(this);
                     gameWidget->player2->removeEventFilter(this);
                     gameWidget->player3->removeEventFilter(this);
                     gameWidget->player4->removeEventFilter(this);
                     return true;
                     }
                     else
                     {
                         if(!isServer)
                         {

                         if(!self->ifSeen)
                         {
                             Data data(UUnseenCmp,(playerIndex+1),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         else
                         {
                             Data data(SSeenCmp,(playerIndex+1),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }

                          NextTurn();
                         }

                         else
                         {

                             if(!self->ifSeen)
                             {
                                 Data data2(UUnseenCmp,2,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }
                             else
                             {
                                 Data data2(SSeenCmp,2,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }


                             self->nowPlayers--;
                             int out=cmpOnline(1,2);
                             Data data1(OOut,out);
                             for(int i=0;i<myServer->ClientList.size();i++)
                             {
                                 myServer->ClientList.at(i)->write(data1.data.toUtf8());
                             }
                             btnsSetFalse();
                             if(out==1)
                             {self->isActive=0;
                                 gameWidget->roundInfo->addItem("你已出局");
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             else
                             {
                                 gameWidget->roundInfo->addItem(name[out]+"已出局！");
                                 playerOut(out-1);
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             NextTurn();

                         }
                         gameWidget->player1->removeEventFilter(this);
                         gameWidget->player2->removeEventFilter(this);
                         gameWidget->player3->removeEventFilter(this);
                         gameWidget->player4->removeEventFilter(this);
                         return true;
                     }
                 }
                 else
                 {
                     return false;
                 }
             }
             else
             {
                 return false;
             }
     }
    else if(obj==gameWidget->player2)
    {
             if (event->type() == QEvent::MouseButtonPress) //鼠标点击
             {
                 QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

                 if(mouseEvent->button() == Qt::LeftButton)
                 {
                     if(!netState)
                     {
                     if(self->ifSeen)
                         showCards(player2);
                     gameWidget->roundInfo->addItem("你选择了"+player2->name);
                     valueCmp(self,gameRun::player2);
                     gameWidget->player1->removeEventFilter(this);
                     gameWidget->player2->removeEventFilter(this);
                     gameWidget->player3->removeEventFilter(this);
                     gameWidget->player4->removeEventFilter(this);
                     return true;
                     }
                     else
                     {
                         if(!isServer)
                         {

                         {
//                         gameWidget->roundInfo->addItem("你选择了"+player2->name);
                         if(!self->ifSeen)
                         {
                             Data data(UUnseenCmp,(playerIndex+2),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         else
                         {
                             Data data(SSeenCmp,(playerIndex+2),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         NextTurn();
                         }
                         }

                         else
                         {

                             self->nowPlayers--;
                             if(!self->ifSeen)
                             {
                                 Data data2(UUnseenCmp,3,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }
                             else
                             {
                                 Data data2(SSeenCmp,3,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }


                             int out=cmpOnline(1,3);
                             Data data1(OOut,out);
                             for(int i=0;i<myServer->ClientList.size();i++)
                             {
                                 myServer->ClientList.at(i)->write(data1.data.toUtf8());
                             }
                             btnsSetFalse();
                             if(out==1)
                             {self->isActive=0;
                                 gameWidget->roundInfo->addItem("你已出局");
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             else
                             {
                                 gameWidget->roundInfo->addItem(name[out]+"已出局！");
                                 playerOut(out-1);
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             NextTurn();

                         }
                         gameWidget->player1->removeEventFilter(this);
                         gameWidget->player2->removeEventFilter(this);
                         gameWidget->player3->removeEventFilter(this);
                         gameWidget->player4->removeEventFilter(this);
                         return true;
                     }
                 }
                 else
                 {
                     return false;
                 }
             }
             else
             {
                 return false;
             }
     }
    else if(obj==gameWidget->player3)
    {
             if (event->type() == QEvent::MouseButtonPress) //鼠标点击
             {
                 QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

                 if(mouseEvent->button() == Qt::LeftButton)
                 {
                     if(!netState)
                     {
                     if(self->ifSeen)
                         showCards(player3);
                     gameWidget->roundInfo->addItem("你选择了"+player3->name);
                     valueCmp(self,gameRun::player3);
                     gameWidget->player1->removeEventFilter(this);
                     gameWidget->player2->removeEventFilter(this);
                     gameWidget->player3->removeEventFilter(this);
                     gameWidget->player4->removeEventFilter(this);
                     return true;
                     }
                     else
                     {
                         if(!isServer)
                         {
                         {
//                         gameWidget->roundInfo->addItem("你选择了"+player3->name);
                         if(!self->ifSeen)
                         {
                             Data data(UUnseenCmp,(playerIndex+3),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         else
                         {
                             Data data(SSeenCmp,(playerIndex+3),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         }
                             NextTurn();
                         }

                         else
                         {

                             self->nowPlayers--;
                             if(!self->ifSeen)
                             {
                                 Data data2(UUnseenCmp,4,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }
                             else
                             {
                                 Data data2(SSeenCmp,4,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }


                             int out=cmpOnline(1,4);
                             Data data1(OOut,out);
                             for(int i=0;i<myServer->ClientList.size();i++)
                             {
                                 myServer->ClientList.at(i)->write(data1.data.toUtf8());
                             }
                             btnsSetFalse();
                             if(out==1)
                             {self->isActive=0;
                                 gameWidget->roundInfo->addItem("你已出局");
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             else
                             {
                                 gameWidget->roundInfo->addItem(name[out]+"已出局！");
                                 playerOut(out-1);
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             NextTurn();

                         }
                         gameWidget->player1->removeEventFilter(this);
                         gameWidget->player2->removeEventFilter(this);
                         gameWidget->player3->removeEventFilter(this);
                         gameWidget->player4->removeEventFilter(this);
                         return true;
                     }
                 }
                 else
                 {
                     return false;
                 }
             }
             else
             {
                 return false;
             }
     }

    else if(obj==gameWidget->player4)
    {
             if (event->type() == QEvent::MouseButtonPress) //鼠标点击
             {
                 QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event); // 事件转换

                 if(mouseEvent->button() == Qt::LeftButton)
                 {
                     if(!netState)
                     {
                     if(self->ifSeen)
                         showCards(player4);
                     gameWidget->roundInfo->addItem("你选择了"+player4->name);
                     valueCmp(self,gameRun::player4);
                     gameWidget->player1->removeEventFilter(this);
                     gameWidget->player2->removeEventFilter(this);
                     gameWidget->player3->removeEventFilter(this);
                     gameWidget->player4->removeEventFilter(this);
                     return true;
                     }
                     else
                     {
                         if(!isServer)
                         {
                         {
//                         gameWidget->roundInfo->addItem("你选择了"+player4->name);
                         if(!self->ifSeen)
                         {
                             Data data(UUnseenCmp,(playerIndex+4),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         else
                         {
                             Data data(SSeenCmp,(playerIndex+4),playerIndex);
                             myServer->Socket->write(data.data.toUtf8());
                         }
                         }
                             NextTurn();
                         }

                         else
                         {

                             self->nowPlayers--;
                             if(!self->ifSeen)
                             {
                                 Data data2(UUnseenCmp,5,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }
                             else
                             {
                                 Data data2(SSeenCmp,5,1);
                                 for(int i=0;i<myServer->ClientList.size();i++)
                                 {
                                     myServer->ClientList.at(i)->write(data2.data.toUtf8());
                                 }
                             }


                             int out=cmpOnline(1,5);
                             Data data1(OOut,out);
                             for(int i=0;i<myServer->ClientList.size();i++)
                             {
                                 myServer->ClientList.at(i)->write(data1.data.toUtf8());
                             }
                             btnsSetFalse();
                             if(out==1)
                             {self->isActive=0;
                                 gameWidget->roundInfo->addItem("你已出局");
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             else
                             {
                                 gameWidget->roundInfo->addItem(name[out]+"已出局！");
                                 playerOut(out-1);
                                 gameWidget->roundInfo->scrollToBottom();
                             }
                             NextTurn();

                         }
                         gameWidget->player1->removeEventFilter(this);
                         gameWidget->player2->removeEventFilter(this);
                         gameWidget->player3->removeEventFilter(this);
                         gameWidget->player4->removeEventFilter(this);
                         return true;
                     }
                 }
                 else
                 {
                     return false;
                 }
             }
             else
             {
                 return false;
             }
     }
    else if(obj==gameWidget->esc->again)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->esc->again->primeHover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->esc->again->rev();
                return true;
            }
        }
    else if(obj==gameWidget->esc->back)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->esc->back->primeHover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->esc->back->rev();
                return true;
            }
        }
    else if(obj==gameWidget->esc->Continue)
        {
            if(event->type() == QEvent::HoverEnter)
            {
                gameWidget->esc->Continue->primeHover();
                return true;
            }
            if(event->type()==QEvent::HoverLeave)
            {

                gameWidget->esc->Continue->rev();
                return true;
            }
        }

    return false;

}

void gameRun::valueCmp(AI *choose,AI *chosen)
{
    if(choose->pokerValue>chosen->pokerValue)//发起比牌者获胜
    {
        gameWidget->roundInfo->addItem(chosen->name+"出局");
        if(chosen==player1)
            gameWidget->player1->setPixmap(*p1out);
        else if(chosen==player2)
            gameWidget->player2->setPixmap(*p2out);
        else if(chosen==player3)
            gameWidget->player3->setPixmap(*p3out);
        else if(chosen==player4)
            gameWidget->player4->setPixmap(*p4out);

        choose->possibility_beenSeenCmp+=7;
        choose->possibility_beenUnseenCmp+=7;

        AI::nowPlayers--;
        chosen->isActive=0;
        if(chosen==self&&!self->ifSeen)
            showCards(self);
    }
    else
    {

        gameWidget->roundInfo->addItem(choose->name+"出局");
        if(choose==player1)
            gameWidget->player1->setPixmap(*p1out);
        else if(choose==player2)
            gameWidget->player2->setPixmap(*p2out);
        else if(choose==player3)
            gameWidget->player3->setPixmap(*p3out);
        else if(choose==player4)
            gameWidget->player4->setPixmap(*p4out);
        if(choose->ifSeen&&choose!=self) //当是ai发起比牌时要判断是闷开还是开
        {
            moneypool+=valSeen;
            gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
        }
        else
        {
            if(choose!=self)
            {moneypool+=valUnseen;
            gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
            gameWidget->roundInfo->addItem(choose->name+"我要开"+chosen->name);}
        }

        chosen->possibility_beenSeenCmp+=7;
        chosen->possibility_beenUnseenCmp+=7;

        AI::nowPlayers--;
        choose->isActive=0;
        if(choose==self&&!self->ifSeen)
        {
            showCards(self);
        }
    }

        if(choose==self)
        {
            emit myTurnOver();
            btnsSetFalse();
        }


    return;
}

int gameRun::cmpOnline(int choose,int chosen)
{
    AI *player[5];
    player[0]=self;
    player[1]=player1;
    player[2]=player2;
    player[3]=player3;
    player[4]=player4;
    if(player[choose-1]->pokerValue>player[chosen-1]->pokerValue)
        return chosen;
    else
        return choose;


}

void gameRun::welcomeToGame()
{
    welcomeWidget->startGame->zoomIn();
    welcomeWidget->startGame->zoomOut();

    QTimer::singleShot(400,this,[=](){
               welcomeWidget->hide();
              chooseScene->show();

           });
}

void gameRun::chooseUnseenCmpPlayer(AI *choose)//相当于一个集成器，将筛选比牌对象，进行比牌和后续操作整合到一个函数
{


    AI *chosen=maxUnseenCmp(choose);
    gameWidget->roundInfo->addItem(choose->name+"我要闷开"+chosen->name);
    valueCmp(choose,chosen);

}

void gameRun::chooseSeenCmpPlayer(AI *choose)
{
    AI *chosen=maxSeenCmp(choose);
    gameWidget->roundInfo->addItem(choose->name+"我要开"+chosen->name);
    valueCmp(choose,chosen);
}

AI* gameRun::maxUnseenCmp(AI* choose)
{
    AI *rank[5];  //注：此处是一个指针数组，指向本次正在进行游戏的player的地址，如果只是一个单纯AI数组，则会导致无法对游戏中的player进行相应变更操作
    rank[0]=player1;
    rank[1]=player2;
    rank[2]=player3;
    rank[3]=player4;
    rank[4]=self;
    std::sort(rank,rank+5,unseenCmpPossibilityCmp);//用sort函数进行排序
    if(rank[0]->isActive&&rank[0]!=choose)
        return rank[0];
    else
    {
        if(rank[1]->isActive&&rank[1]!=choose)
            return rank[1];
        else
        {
            if(rank[2]->isActive&&rank[2]!=choose)
                return rank[2];
            else
                if(rank[3]->isActive&&rank[3]!=choose)
                    return rank[3];
            else
                    if(rank[4]->isActive&&rank[4]!=choose)
                        return rank[4];
            return self;
        }
    }
}

AI* gameRun::maxSeenCmp(AI *choose)
{
    AI *rank[5];
    rank[0]=player1;
    rank[1]=player2;
    rank[2]=player3;
    rank[3]=player4;
    rank[4]=self;
    std::sort(rank,rank+5,seenCmpPossibilityCmp);
    if(rank[0]->isActive&&rank[0]!=choose)
        return rank[0];
    else
    {
        if(rank[1]->isActive&&rank[1]!=choose)
            return rank[1];
        else
        {
            if(rank[2]->isActive&&rank[2]!=choose)
                return rank[2];
            else
                if(rank[3]->isActive&&rank[3]!=choose)
                    return rank[3];
            else
                    if(rank[4]->isActive&&rank[4]!=choose)
                        return rank[4];
            return self;
        }
    }
}

bool gameRun::unseenCmpPossibilityCmp(AI* a,AI* b)//自定义比较函数，用于sort
{
    return a->possibility_beenUnseenCmp>b->possibility_beenUnseenCmp;
}

bool gameRun::seenCmpPossibilityCmp(AI *a, AI *b)
{
    return a->possibility_beenSeenCmp>b->possibility_beenSeenCmp;
}

void gameRun::playerSet(AI *player)
{
    //一般而言，当手牌在清一色以及以上（80+）可以无脑跟牌，且摸到清一色以上概率很小，因此主要考虑value在80以下的牌（单牌，对子，顺子）
    //由于value的值并非线性增加，因此其开牌概率虽与value正相关但是不能用线性函数表示二者关系，只能用if分类讨论
    if(player->pokerValue<80)
    {
           if(player->pokerValue<24)//最大牌不超过K的单牌
              {
               player->possibility_seenCmp-=10;
               player->possibility_addMoney-=20;
               player->possibility_seenPass+=60-3*player->gamblerLevel;
              }
           else
           {
               if(player->pokerValue>24&&player->pokerValue<30)//最大牌是K和A的单牌
               {
                   player->possibility_seenCmp+=10;
                   player->possibility_addMoney+=10;
                   player->possibility_seenPass+=20-player->gamblerLevel;
               }
               else
               {
                   if(player->pokerValue>30&&player->pokerValue<44)//对3~对7 小对子
                      {
                       player->possibility_seenCmp+=30;
                       player->possibility_addMoney+=30;
                       player->possibility_seenPass-=7+player->gamblerLevel;

                      }
                   else
                   {
                       if(player->pokerValue>44&&player->pokerValue<60)//对8~对A，大对子
                          {
                           player->possibility_seenCmp+=50;
                           player->possibility_addMoney+=50;
                           player->possibility_seenPass=5;
                          }
                       else
                       {
                           player->possibility_seenCmp+=70;
                           player->possibility_addMoney+=70;
                           player->possibility_seenPass=0;
                       }
                   }

               }
           }
    }

    else
    {
        player->possibility_seenCmp=20;
        player->possibility_addMoney=99;
        player->possibility_seenPass=0;
    }


    return;
}

void gameRun::showCards(AI *player)
{
 if(player==self)
 {
     QPixmap p1(self->ownCard[0]->imgPath);
     QPixmap p2(self->ownCard[1]->imgPath);
     QPixmap p3(self->ownCard[2]->imgPath);

     gameWidget->card1->setPixmap(p1);
     gameWidget->card2->setPixmap(p2);
     gameWidget->card3->setPixmap(p3);
     return;
 }
    if(player==player1)
    {
        QPixmap p1c1(player1->ownCard[0]->imgPath);
        QPixmap p1c2(player1->ownCard[1]->imgPath);
        QPixmap p1c3(player1->ownCard[2]->imgPath);
        gameWidget->p1card1->setPixmap(p1c1);
        gameWidget->p1card2->setPixmap(p1c2);
        gameWidget->p1card3->setPixmap(p1c3);
        return;
    }
    if(player==player2)
    {
        QPixmap p2c1(player2->ownCard[0]->imgPath);
        QPixmap p2c2(player2->ownCard[1]->imgPath);
        QPixmap p2c3(player2->ownCard[2]->imgPath);
        gameWidget->p2card1->setPixmap(p2c1);
        gameWidget->p2card2->setPixmap(p2c2);
        gameWidget->p2card3->setPixmap(p2c3);
        return;
    }
    if(player==player3)
    {
        QPixmap p3c1(player3->ownCard[0]->imgPath);
        QPixmap p3c2(player3->ownCard[1]->imgPath);
        QPixmap p3c3(player3->ownCard[2]->imgPath);
        gameWidget->p3card1->setPixmap(p3c1);
        gameWidget->p3card2->setPixmap(p3c2);
        gameWidget->p3card3->setPixmap(p3c3);

    }
    if(player==player4)
    {
        QPixmap p4c1(player4->ownCard[0]->imgPath);
        QPixmap p4c2(player4->ownCard[1]->imgPath);
        QPixmap p4c3(player4->ownCard[2]->imgPath);
        gameWidget->p4card1->setPixmap(p4c1);
        gameWidget->p4card2->setPixmap(p4c2);
        gameWidget->p4card3->setPixmap(p4c3);

    }
}

void gameRun::setBtns() //设置按钮可用
{
    gameWidget->hold->installEventFilter(this);
    gameWidget->check->installEventFilter(this);
    gameWidget->pass->installEventFilter(this);
    gameWidget->addMoney->installEventFilter(this);
    gameWidget->unseen_cmp->installEventFilter(this);
    gameWidget->seen_cmp->installEventFilter(this);

    gameWidget->esc->back->installEventFilter(this);
    gameWidget->esc->again->installEventFilter(this);
    gameWidget->esc->Continue->installEventFilter(this);



    welcomeWidget->startGame->installEventFilter(this);
    welcomeWidget->quitGame->installEventFilter(this);
}

void gameRun::btnsSetTrue()
{
    gameWidget->hold->installEventFilter(this);
    gameWidget->check->installEventFilter(this);
    gameWidget->pass->installEventFilter(this);
    gameWidget->addMoney->installEventFilter(this);
    gameWidget->unseen_cmp->installEventFilter(this);
    gameWidget->seen_cmp->installEventFilter(this);

    gameWidget->hold->setEnabled(true);
    gameWidget->check->setEnabled(true);
    gameWidget->pass->setEnabled(true);
    gameWidget->addMoney->setEnabled(true);
    gameWidget->unseen_cmp->setEnabled(true);
    gameWidget->seen_cmp->setEnabled(true);

    if(self->ifSeen)
    {
        gameWidget->hold->setEnabled(false);
        gameWidget->hold->removeEventFilter(this);
    }
}

void gameRun::btnsSetFalse()
{
    gameWidget->hold->removeEventFilter(this);
    gameWidget->check->removeEventFilter(this);
    gameWidget->pass->removeEventFilter(this);
    gameWidget->addMoney->removeEventFilter(this);
    gameWidget->unseen_cmp->removeEventFilter(this);
    gameWidget->seen_cmp->removeEventFilter(this);

    gameWidget->hold->setEnabled(false);
    gameWidget->check->setEnabled(false);
    gameWidget->pass->setEnabled(false);
    gameWidget->addMoney->setEnabled(false);
    gameWidget->unseen_cmp->setEnabled(false);
    gameWidget->seen_cmp->setEnabled(false);
}

void gameRun::setBgm()
{
    bgmList->addMedia(QUrl("qrc:/bgm/audio/bgm/welcomescene.mp3"));
    bgmList->addMedia(QUrl("qrc:/bgm/audio/bgm/scene1.mp3"));
    bgmList->addMedia(QUrl("qrc:/bgm/audio/bgm/scene2.mp3"));
    bgmList->addMedia(QUrl("qrc:/bgm/audio/bgm/scene3.mp3"));
     bgmList->addMedia(QUrl("qrc:/bgm/audio/bgm/scene4.mp3"));

    bgmList->setPlaybackMode(QMediaPlaylist::Loop);
    bgm->setPlaylist(bgmList);

}

void gameRun::loadScene1()
{
    this->scene=1;
    valSeen=8;
    valUnseen=3;

    ifEnd=0;
    AI::nowRound=1;
    AI::nowPlayers=5;
    Card::shuffle(); //洗牌
    self=new playerSelf("你",5,nullptr);
    gameWidget=new gameStartWidget();
    setBtns();

    p1out=new QPixmap;
    p2out=new QPixmap;
    p3out=new QPixmap;
    p4out=new QPixmap;

    p1out->load(":/playerimages/image/players/harryOut.jpg");
    p2out->load(":/playerimages/image/players/hermioneOut.jpg");
    p3out->load(":/playerimages/image/players/ronOut.jpg");
    p4out->load(":/playerimages/image/players/malfoyOut.jpg");

    moneypool=10;
    myMoney-=2;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

    gameWidget->unseen_cmp->setEnabled(false);//第一回合不能闷开
    gameWidget->unseen_cmp->removeEventFilter(this);
    gameWidget->background->setFileName(":/gifs/image/background/sence.gif");
    gameWidget->bac->setMovie(gameWidget->background);
    gameWidget->background->start();

   gameWidget->player1_icon->load(":/playerimages/image/players/harry.jpg");
   gameWidget->player2_icon->load(":/playerimages/image/players/hermione.jpg");
   gameWidget-> player3_icon->load(":/playerimages/image/players/ron.jpg");
   gameWidget->player4_icon->load(":/playerimages/image/players/malfoy.jpg");

   gameWidget->player1->setPixmap(*gameWidget->player1_icon);
   gameWidget->player2->setPixmap(*gameWidget->player2_icon);
   gameWidget->player3->setPixmap(*gameWidget->player3_icon);
   gameWidget->player4->setPixmap(*gameWidget->player4_icon);

      player1=new Harry("哈利     ",1);
   player2=new Hermione("赫敏     ",2);
        player3=new Ron("罗恩     ",3);
     player4=new Malfoy("马尔福    ",4);


   player1->getCards();
   player2->getCards();
   player3->getCards();
   player4->getCards();

   player1->checkValue();
   player2->checkValue();
   player3->checkValue();
   player4->checkValue();

   playerSet(player1);
   playerSet(player2);
   playerSet(player3);
   playerSet(player4);

   gameWidget->roundInfo->addItem("游戏开始！");

   //接下来是一系列信号和槽的连接
   QObject::connect(player1->roundTime,&QTimer::timeout,this,&gameRun::player1TurnOver);
   QObject::connect(player2->roundTime,&QTimer::timeout,this,&gameRun::player2TurnOver);
   QObject::connect(player3->roundTime,&QTimer::timeout,this,&gameRun::player3TurnOver);
   QObject::connect(player4->roundTime,&QTimer::timeout,this,&gameRun::player4TurnOver);

   QObject::connect(gameWidget->esc->back,&myButton::clicked,this,&gameRun::backClicked);
   QObject::connect(gameWidget->esc->again,&myButton::clicked,this,&gameRun::againClicked);
   QObject::connect(gameWidget->hold,&QPushButton::clicked,this,&gameRun::holdClicked);
   QObject::connect(gameWidget->check,&QPushButton::clicked,this,&gameRun::checkClicked);
   QObject::connect(gameWidget->pass,&QPushButton::clicked,this,&gameRun::passClicked);
   QObject::connect(gameWidget->unseen_cmp,&QPushButton::clicked,this,&gameRun::unseenCmpClicked);

   QObject::connect(player1,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
   QObject::connect(player2,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
   QObject::connect(player3,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
   QObject::connect(player4,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
   QObject::connect(player1,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
   QObject::connect(player2,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
   QObject::connect(player3,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
   QObject::connect(player4,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);

   if(bgm->media()!=bgmList->media(1))//重开游戏时bgm不会重置
   {

       bgm->setMedia(bgmList->media(1));
       bgm->play();

   }

   chooseScene->hide();
   gameWidget->show();


}

void gameRun::loadScene2()
{
    this->scene=2;
    valSeen=8;
    valUnseen=3;
    ifEnd=0;
    AI::nowRound=1;
    AI::nowPlayers=5;
    Card::shuffle();
    self=new playerSelf("你",5,nullptr);
    gameWidget=new gameStartWidget();
    setBtns();
    p1out=new QPixmap;
    p2out=new QPixmap;
    p3out=new QPixmap;
    p4out=new QPixmap;

    p1out->load(":/playerimages/image/players/ErenOut.jpg");
    p2out->load(":/playerimages/image/players/mikasaOut.jpg");
    p3out->load(":/playerimages/image/players/rivilleOut.jpg");
    p4out->load(":/playerimages/image/players/reinerOut.jpg");

    moneypool=10;
    myMoney-=2;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
    gameWidget->unseen_cmp->setEnabled(false);
    gameWidget->unseen_cmp->removeEventFilter(this);
    gameWidget->background->setFileName(":/gifs/image/background/scene2.gif");
    gameWidget->bac->setMovie(gameWidget->background);
    gameWidget->background->start();

    gameWidget->player1_icon->load(":/playerimages/image/players/Eren.jpg");
    gameWidget->player2_icon->load(":/playerimages/image/players/mikasa.jpg");
    gameWidget-> player3_icon->load(":/playerimages/image/players/Rivaille.jpg");
    gameWidget->player4_icon->load(":/playerimages/image/players/reiner.jpg");

    gameWidget->player1->setPixmap(*gameWidget->player1_icon);
    gameWidget->player2->setPixmap(*gameWidget->player2_icon);
    gameWidget->player3->setPixmap(*gameWidget->player3_icon);
    gameWidget->player4->setPixmap(*gameWidget->player4_icon);

      player1=new Eren("艾伦耶格尔  ",1);
    player2=new Mikasa("三笠       ",2);
  player3=new Rivaille("利威尔     ",3);
    player4=new Reiner("莱纳       ",4);

    player1->getCards();
    player2->getCards();
    player3->getCards();
    player4->getCards();

    player1->checkValue();
    player2->checkValue();
    player3->checkValue();
    player4->checkValue();

    playerSet(player1);
    playerSet(player2);
    playerSet(player3);
    playerSet(player4);

    QObject::connect(player1->roundTime,&QTimer::timeout,this,&gameRun::player1TurnOver);
    QObject::connect(player2->roundTime,&QTimer::timeout,this,&gameRun::player2TurnOver);
    QObject::connect(player3->roundTime,&QTimer::timeout,this,&gameRun::player3TurnOver);
    QObject::connect(player4->roundTime,&QTimer::timeout,this,&gameRun::player4TurnOver);

    QObject::connect(gameWidget->esc->back,&myButton::clicked,this,&gameRun::backClicked);
    QObject::connect(gameWidget->esc->again,&myButton::clicked,this,&gameRun::againClicked);
    QObject::connect(gameWidget->hold,&QPushButton::clicked,this,&gameRun::holdClicked);
    QObject::connect(gameWidget->check,&QPushButton::clicked,this,&gameRun::checkClicked);
    QObject::connect(gameWidget->pass,&QPushButton::clicked,this,&gameRun::passClicked);
    QObject::connect(gameWidget->unseen_cmp,&QPushButton::clicked,this,&gameRun::unseenCmpClicked);

    QObject::connect(player1,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player2,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player3,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player4,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player1,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player2,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player3,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player4,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);

     gameWidget->roundInfo->addItem("游戏开始！");

    if(bgm->media()!=bgmList->media(2))
    {

        bgm->setMedia(bgmList->media(2));
        bgm->play();

    }

    chooseScene->hide();
    gameWidget->show();

}

void gameRun::loadScene3()
{
    this->scene=3;
    valSeen=8;
    valUnseen=3;
    ifEnd=0;
    AI::nowRound=1;
    AI::nowPlayers=5;
     Card::shuffle();
     self=new playerSelf("你",5,nullptr);

    gameWidget=new gameStartWidget();
    setBtns();

    p1out=new QPixmap;
    p2out=new QPixmap;
    p3out=new QPixmap;
    p4out=new QPixmap;

    p1out->load(":/playerimages/image/players/gudaOut.jpg");
    p2out->load(":/playerimages/image/players/wuniangOut.jpg");
    p3out->load(":/playerimages/image/players/falanOut.jpg");
    p4out->load(":/playerimages/image/players/wumingOut.jpg");

    moneypool=10;
    myMoney-=2;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

    gameWidget->unseen_cmp->setEnabled(false);
    gameWidget->unseen_cmp->removeEventFilter(this);
    gameWidget->background->setFileName(":/gifs/image/background/scene3.gif");
    gameWidget->bac->setMovie(gameWidget->background);
    gameWidget->background->start();

    gameWidget->player1_icon->load(":/playerimages/image/players/guda.jpg");
    gameWidget->player2_icon->load(":/playerimages/image/players/wuniang.jpg");
    gameWidget-> player3_icon->load(":/playerimages/image/players/falan.jpg");
    gameWidget->player4_icon->load(":/playerimages/image/players/wuming.jpg");

    gameWidget->player1->setPixmap(*gameWidget->player1_icon);
    gameWidget->player2->setPixmap(*gameWidget->player2_icon);
    gameWidget->player3->setPixmap(*gameWidget->player3_icon);
    gameWidget->player4->setPixmap(*gameWidget->player4_icon);

       player1=new Guda("英雄古达    ",1);
    player2=new Wuniang("舞娘       ",2);
      player3=new Falan("法兰不死队  ",3);
     player4=new Wuming("无名王者    ",4);

    player1->getCards();
    player2->getCards();
    player3->getCards();
    player4->getCards();

    player1->checkValue();
    player2->checkValue();
    player3->checkValue();
    player4->checkValue();

    playerSet(player1);
    playerSet(player2);
    playerSet(player3);
    playerSet(player4);

    QObject::connect(player1->roundTime,&QTimer::timeout,this,&gameRun::player1TurnOver);
    QObject::connect(player2->roundTime,&QTimer::timeout,this,&gameRun::player2TurnOver);
    QObject::connect(player3->roundTime,&QTimer::timeout,this,&gameRun::player3TurnOver);
    QObject::connect(player4->roundTime,&QTimer::timeout,this,&gameRun::player4TurnOver);

    QObject::connect(gameWidget->esc->back,&myButton::clicked,this,&gameRun::backClicked);
    QObject::connect(gameWidget->esc->again,&myButton::clicked,this,&gameRun::againClicked);
    QObject::connect(gameWidget->hold,&QPushButton::clicked,this,&gameRun::holdClicked);
    QObject::connect(gameWidget->check,&QPushButton::clicked,this,&gameRun::checkClicked);
    QObject::connect(gameWidget->pass,&QPushButton::clicked,this,&gameRun::passClicked);
    QObject::connect(gameWidget->unseen_cmp,&QPushButton::clicked,this,&gameRun::unseenCmpClicked);

    QObject::connect(player1,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player2,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player3,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player4,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player1,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player2,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player3,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player4,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);


    gameWidget->roundInfo->addItem("游戏开始！");

    if(bgm->media()!=bgmList->media(3))
    {

        bgm->setMedia(bgmList->media(3));
        bgm->play();

    }

    chooseScene->hide();

     gameWidget->show();

}

void gameRun::loadScene4()
{
    ifEnd=0;
    valSeen=15; //为增加难度会提高注
    valUnseen=5;
    scene=4;
    AI::nowRound=1;
    AI::nowPlayers=5;
     Card::shuffle();
     self=new playerSelf("你",5,nullptr);

    gameWidget=new gameStartWidget();
    setBtns();

    p1out=new QPixmap;
    p2out=new QPixmap;
    p3out=new QPixmap;
    p4out=new QPixmap;

    p1out->load(":/playerimages/image/players/voldmordOut.png");
    p2out->load(":/playerimages/image/players/szjrOut.png");
    p3out->load(":/playerimages/image/players/xinwangOut.jpg");
    p4out->load(":/playerimages/image/players/dsOut.jpg");

    moneypool=10;
    myMoney-=2;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

    gameWidget->unseen_cmp->setEnabled(false);
    gameWidget->unseen_cmp->removeEventFilter(this);
    gameWidget->background->setFileName(":/gifs/image/background/scene4.gif");
    gameWidget->bac->setMovie(gameWidget->background);
    gameWidget->background->start();

    gameWidget->player1_icon->load(":/playerimages/image/players/voldmord.png");
    gameWidget->player2_icon->load(":/playerimages/image/players/szjr.jpg");
    gameWidget-> player3_icon->load(":/playerimages/image/players/xinwang.jpg");
    gameWidget->player4_icon->load(":/playerimages/image/players/ds.jpg");

    gameWidget->player1->setPixmap(*gameWidget->player1_icon);
    gameWidget->player2->setPixmap(*gameWidget->player2_icon);
    gameWidget->player3->setPixmap(*gameWidget->player3_icon);
    gameWidget->player4->setPixmap(*gameWidget->player4_icon);

       player1=new vdm("伏地魔    ",1);
    player2=new jj("进击巨人   ",2);
      player3=new xw("薪王      ",3);
     player4=new ds("赌神      ",4);

    player1->getCards();
    player2->getCards();
    player3->getCards();
    player4->getCards();

    player1->checkValue();
    player2->checkValue();
    player3->checkValue();
    player4->checkValue();

    playerSet(player1);
    playerSet(player2);
    playerSet(player3);
    playerSet(player4);

    QObject::connect(player1->roundTime,&QTimer::timeout,this,&gameRun::player1TurnOver);
    QObject::connect(player2->roundTime,&QTimer::timeout,this,&gameRun::player2TurnOver);
    QObject::connect(player3->roundTime,&QTimer::timeout,this,&gameRun::player3TurnOver);
    QObject::connect(player4->roundTime,&QTimer::timeout,this,&gameRun::player4TurnOver);

    QObject::connect(gameWidget->esc->back,&myButton::clicked,this,&gameRun::backClicked);
    QObject::connect(gameWidget->esc->again,&myButton::clicked,this,&gameRun::againClicked);
    QObject::connect(gameWidget->hold,&QPushButton::clicked,this,&gameRun::holdClicked);
    QObject::connect(gameWidget->check,&QPushButton::clicked,this,&gameRun::checkClicked);
    QObject::connect(gameWidget->pass,&QPushButton::clicked,this,&gameRun::passClicked);
    QObject::connect(gameWidget->unseen_cmp,&QPushButton::clicked,this,&gameRun::unseenCmpClicked);

    QObject::connect(player1,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player2,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player3,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player4,&AI::unseenCmp,this,&gameRun::chooseUnseenCmpPlayer);
    QObject::connect(player1,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player2,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player3,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);
    QObject::connect(player4,&AI::seenCmp,this,&gameRun::chooseSeenCmpPlayer);



    gameWidget->roundInfo->addItem("游戏开始！");


    if(bgm->media()!=bgmList->media(4))
    {

        bgm->setMedia(bgmList->media(4));
        bgm->play();

    }

    chooseScene->hide();

     gameWidget->show();

}


void gameRun::loadOnline()
{
    ifEnd=false;
    netState=true;
    scene=0;
    Card::shuffle();
    self=new playerSelf("你",5,nullptr);
    gameWidget=new gameStartWidget();
    setBtns();

    p1out=new QPixmap;
    p2out=new QPixmap;
    p3out=new QPixmap;
    p4out=new QPixmap;


    name.push_back("null");
    name.push_back("李云龙");
    name.push_back("楚云飞");
    name.push_back("山本");
    name.push_back("孙德胜");
    name.push_back("祖安哥");

    p1out->load(":/playerimages/image/players/cyfOut.jpg");
    p2out->load(":/playerimages/image/players/sbOut.jpg");
    p3out->load(":/playerimages/image/players/sdsOut.jpg");
    p4out->load(":/playerimages/image/players/rnxrOut.jpg");

    moneypool=10;
    myMoney-=2;
    gameWidget->coin->setText("你的金币:"+QString::number(myMoney));
    gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));


    gameWidget->background->setFileName(":/gifs/image/background/scene4.gif");
    gameWidget->bac->setMovie(gameWidget->background);
    gameWidget->background->start();

    gameWidget->player1_icon->load(":/playerimages/image/players/cyf.jpg");
    gameWidget->player2_icon->load(":/playerimages/image/players/sb.jpg");
    gameWidget-> player3_icon->load(":/playerimages/image/players/wxs.jpg");
    gameWidget->player4_icon->load(":/playerimages/image/players/rnxr.jpg");

    gameWidget->player1->setPixmap(*gameWidget->player1_icon);
    gameWidget->player2->setPixmap(*gameWidget->player2_icon);
    gameWidget->player3->setPixmap(*gameWidget->player3_icon);
    gameWidget->player4->setPixmap(*gameWidget->player4_icon);

    player1=new AI("楚云飞    ",1);
    player2=new AI("山本   ",2);
    player3=new AI("孙德胜     ",3);
    player4=new AI("祖安哥      ",4);

    QObject::connect(gameWidget->esc->back,&myButton::clicked,this,&gameRun::backClicked);
    QObject::connect(gameWidget->esc->again,&myButton::clicked,this,&gameRun::againClicked);

    QObject::connect(gameWidget->hold,&myButton::clicked,this,&gameRun::holdOnline);
    QObject::connect(gameWidget->pass,&myButton::clicked,this,&gameRun::passOnline);
    QObject::connect(gameWidget->check,&myButton::clicked,this,&gameRun::check);
    QObject::connect(gameWidget->unseen_cmp,&myButton::clicked,this,&gameRun::unseenCmpOnline);

     gameWidget->show();

}

void gameRun::stop()
{
    player1->roundTime->stop();
    player2->roundTime->stop();
    player3->roundTime->stop();
    player4->roundTime->stop();
}

void gameRun::connectCliked()
{
    nowOnlinePlayers=1;
    if(!myServer->Server->listen(QHostAddress::Any, 8888))
    {
         QMessageBox::information(myServer, "QT网络通信", "服务器端监听失败！");
         return;
    }
    loadOnline();
    Card::shuffle();
    self=new playerSelf("你",5,nullptr);
    isServer=true;
    myServer->hide();
    gameWidget->show();
    bgm->setVolume(20);

    playerState=new int[4];
    for(int i=0;i<4;i++)
        playerState[i]=1;

    gameWidget->roundInfo->addItem("房间创建成功，等待玩家加入。。。");
    gameWidget->roundInfo->addItem("房间IP:"+QNetworkInterface().allAddresses().at(1).toString());

    QObject::connect(myServer->Server,&QTcpServer::newConnection,this,&gameRun::newConnection);


    rec=new QByteArray;
    sed=new QByteArray;
//    btnsSetFalse();

}

void gameRun::joinCliked()
{
    loadOnline();
    isServer=false;
    myServer->hide();
    gameWidget->show();
    bgm->setVolume(20);
     btnsSetFalse();
     QObject::connect(myServer->Socket,&QTcpSocket::readyRead,this,&gameRun::clintRecieve);


}


void gameRun::newConnection()
{

    nowOnlinePlayers++;

    QTcpSocket* tcpClient = myServer->Server->nextPendingConnection();        //保存套接字到容器
    myServer->ClientList.append(tcpClient);
    QObject::connect(tcpClient,&QTcpSocket::readyRead,this,&gameRun::serverRecieve);

    QString str("新玩家加入，当前有"+QString::number(myServer->ClientList.size()+1)+"位玩家！/");
    for(int i=0;i<myServer->ClientList.size();i++)
    {
        myServer->ClientList.at(i)->write(str.toUtf8());
    }
    gameWidget->roundInfo->addItem(str);

    Data dis(DDistribute,nowOnlinePlayers);
    myServer->ClientList.at(nowOnlinePlayers-2)->write(dis.data.toUtf8());

    if(nowOnlinePlayers==2)
    {
       player1->getCards();
       player1->checkValue();
       for(int i=0;i<3;i++)
       {
           Data  cdt(ccard,i,player1->ownCard[i]->index);
           myServer->ClientList.at(0)->write(cdt.data.toUtf8());

       }
    }
    else  if(nowOnlinePlayers==3)
    {

           player2->getCards();
           player2->checkValue();
           for(int i=0;i<3;i++)
           {
               Data  cdt(ccard,i,player2->ownCard[i]->index);
               myServer->ClientList.at(1)->write(cdt.data.toUtf8());
           }
    }
  else  if(nowOnlinePlayers==4)
    {
           player3->getCards();
           player3->checkValue();
           for(int i=0;i<3;i++)
           {
               Data  cdt(ccard,i,player3->ownCard[i]->index);
               myServer->ClientList.at(2)->write(cdt.data.toUtf8());
           }
    }
    else  if(nowOnlinePlayers==5)
    {

        player4->getCards();
        player4->checkValue();
        for(int i=0;i<3;i++)
        {
            Data  cdt(ccard,i,player4->ownCard[i]->index);
            myServer->ClientList.at(3)->write(cdt.data.toUtf8());
        }
    }


    if(nowOnlinePlayers==5)
    {
        gameWidget->roundInfo->addItem("游戏开始！");
        btnsSetTrue();
        for(int i=0;i<4;i++)
        {
            QString str("游戏开始！/");
            myServer->ClientList.at(i)->write(str.toUtf8());
        }
    }
}

void gameRun::Distribute(int n)//分配席位
{


    QPixmap p[5];
    p[0].load(":/playerimages/image/players/cyf.jpg");
    p[1].load(":/playerimages/image/players/sb.jpg");
    p[2].load(":/playerimages/image/players/wxs.jpg");
    p[3].load(":/playerimages/image/players/rnxr.jpg");
    p[4].load(":/playerimages/image/players/lyl.jpg");

    if(n==2)
    {
       gameWidget->self->setPixmap(p[0]);
       gameWidget->player1->setPixmap(p[1]);
       gameWidget->player2->setPixmap(p[2]);
       gameWidget->player3->setPixmap(p[3]);
       gameWidget->player4->setPixmap(p[4]);

       p1out->load(":/playerimages/image/players/sbOut.jpg");
       p2out->load(":/playerimages/image/players/sdsOut.jpg");
       p3out->load(":/playerimages/image/players/rnxrOut.jpg");
       p4out->load(":/playerimages/image/players/lylOut.jpg");

    }
    else  if(n==3)
    {
        gameWidget->self->setPixmap(p[1]);
        gameWidget->player1->setPixmap(p[2]);
        gameWidget->player2->setPixmap(p[3]);
        gameWidget->player3->setPixmap(p[4]);
        gameWidget->player4->setPixmap(p[0]);

        p1out->load(":/playerimages/image/players/sdsOut.jpg");
        p2out->load(":/playerimages/image/players/rnxrOut.jpg");
        p3out->load(":/playerimages/image/players/lylOut.jpg");
        p4out->load(":/playerimages/image/players/cyfOut.jpg");


    }
  else  if(n==4)
    {
        gameWidget->self->setPixmap(p[2]);
        gameWidget->player1->setPixmap(p[3]);
        gameWidget->player2->setPixmap(p[4]);
       gameWidget->player3->setPixmap(p[0]);
       gameWidget->player4->setPixmap(p[1]);

       p1out->load(":/playerimages/image/players/rnxrOut.jpg");
       p2out->load(":/playerimages/image/players/lylOut.jpg");
       p3out->load(":/playerimages/image/players/cyfOut.jpg");
       p4out->load(":/playerimages/image/players/sbOut.jpg");

    }
    else  if(n==5)
    {
        gameWidget->self->setPixmap(p[3]);
        gameWidget->player1->setPixmap(p[4]);
        gameWidget->player2->setPixmap(p[0]);
        gameWidget->player3->setPixmap(p[1]);
        gameWidget->player4->setPixmap(p[2]);

        p1out->load(":/playerimages/image/players/lylOut.jpg");
        p2out->load(":/playerimages/image/players/cyfOut.jpg");
        p3out->load(":/playerimages/image/players/sbOut.jpg");
        p4out->load(":/playerimages/image/players/sdsOut.jpg");


    }
     btnsSetFalse();

}

void gameRun::clintRecieve()
{

  QByteArray buffer= myServer->Socket->readAll();
  QString str=buffer;
  QStringList command;
  command=str.split("/");
  for(int i=0;i<command.size()-1;i++)
  {
          if(command[i][0]==QString::number(DDistribute))
          {
               if(command[i][1]=='2')
                   Distribute(2);
               else if(command[i][1]=='3')
                   Distribute(3);
               else if(command[i][1]=='4')
                   Distribute(4);
               else if(command[i][1]=='5')
                   Distribute(5);

               playerIndex=(command[i].toInt()/10)%10;

               gameWidget->roundInfo->addItem("你是第"+command[i][1]+"位玩家");
          }
          else if(command[i][0]==QString::number(HHold))
          {

           gameWidget->roundInfo->addItem(name[command[i].toInt()%10]+"选择闷牌");
           if(command[i][2]!=QString::number(playerIndex))
           {moneypool+=valUnseen;
           gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));}

          }
          else if(command[i][0]==QString::number(CCheck))
          {
           gameWidget->roundInfo->addItem(name[command[i].toInt()%10]+"选择看牌");
           name[command[i].toInt()%10]+="(已看牌)";
          }
          else if(command[i][0]==QString::number(UUnseenCmp))
          {
              int n=command[i].toInt();
              int choose=n%10;if(choose>5)choose-=5;
              int chose =(n/10)%10;if(chose>5)chose-=5;

              gameWidget->roundInfo->addItem(name[choose]+"选择闷开"+name[chose]);
              if(choose!=playerIndex)
              {moneypool+=valUnseen;
              gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));}

          }
          else if(command[i][0]==QString::number(SSeenCmp))
          {

              int n=command[i].toInt();
              int choose=n%10;if(choose>5)choose-=5;
              int chose =(n/10)%10;if(chose>5)chose-=5;

              gameWidget->roundInfo->addItem(name[choose]+"选择开"+name[chose]);
              if(choose!=playerIndex)
              {moneypool+=valSeen;
              gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));}
          }

          else if(command[i][0]==QString::number(AAddMoney))
          {
          gameWidget->roundInfo->addItem(name[command[i].toInt()%10]+"加注5币");
          if(command[i].toInt()%10!=playerIndex)
          {moneypool+=valSeen;
          gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));}
          }

          else if(command[i][0]==QString::number(ccard))
          {
              int n=command[i].toUInt();
              if(command[i][1]=="0")
              {
                  self->ownCard[0]=Card::allCards[n];

              }
              else if(command[i][1]=="1")
              {
                  if(n<100)
                  {self->ownCard[1]=Card::allCards[n%10];
                      }
                  else
                  {self->ownCard[1]=Card::allCards[n%100];
                     }
              }
              else if(command[i][1]=="2")
              {
                  if(n<100)
                      self->ownCard[2]=Card::allCards[n%10];
                  else
                      self->ownCard[2]=Card::allCards[n%100];
              }
          }

          else if(command[i][0]==QString::number(TurnBegein))
          {

              if(command[i][1]==QString::number(playerIndex))
             {
                          if(self->isActive)
                         { gameWidget->roundInfo->addItem("你的回合");
                             btnsSetTrue();

                          }
                          else
                          {
                              QString info(name[playerIndex]+"已出局/");

                              NextTurn();
                              return;
                          }

              }
              else
              {
                  gameWidget->roundInfo->addItem(name[(command[i].toInt()/10)%10]+"的回合");
              }

          }

          else if(command[i][0]==QString::number(PPass))
          {
              if(command[i][2]==QString::number(playerIndex))
              {
                  gameWidget->roundInfo->addItem("你选择弃牌出局");
                  self->isActive=0;
                  btnsSetFalse();
              }
              else
              {
                int n=command[i].toInt()%10;
                gameWidget->roundInfo->addItem(name[n]+"弃牌出局！");

                n=(n-playerIndex);//参考系变化
                if(n<0)n+=5;
                gameWidget->roundInfo->addItem("出局的是"+QString::number(n));

                playerOut(n);
              }

          }

          else if(command[i][0]==QString::number(OOut))
          {
              if(command[i][1]==QString::number(playerIndex))
             {
                  self->isActive=false;
                  gameWidget->roundInfo->addItem("你已出局");
                  btnsSetFalse();
              }
              else
              {
                  int n=(command[i].toInt()/10)%10;
                  if(n>5)n-=5;
                  gameWidget->roundInfo->addItem(name[n]+"已出局！");

                  n=(n-playerIndex);//参考系变化
                  if(n<0)n+=5;
                  gameWidget->roundInfo->addItem("出局的是"+QString::number(n));
                 playerOut(n);
              }
          }

          else if(command[i][0]=="w")
          {
              command[i].remove(0,1);
              int n=command[i].toInt();
              if(n==playerIndex)
              {
                  myMoney+=moneypool;//钱池中金币归玩家所有
                  moneypool=0;
                  gameWidget->coin->setText("你的金币："+QString::number(myMoney));
                  gameWidget->nowMoney->setText("钱池："+QString::number(moneypool));
                  gameWidget->roundInfo->addItem("你获得了胜利！");
              }
              else
              {
                  moneypool=0;
                   gameWidget->nowMoney->setText("钱池："+QString::number(moneypool));
                   gameWidget->roundInfo->addItem(name[n]+"获得了胜利！");
              }
          }

          else if(command[i][0]=="c")
          {
              command[i].remove(0,1);
              int n=command[i].toInt();
              if(n!=playerIndex)
             {
              QMessageBox::information(gameWidget, "QT网络通信", "玩家"+command[i][1]+"离开！");
              myServer->Socket->disconnectFromHost();
              gameWidget->close();
              delete gameWidget;
              gameWidget=nullptr;
              welcomeWidget->show();
              netState=false;
              }
              else
              {
                  gameWidget=nullptr;
                  welcomeWidget->show();
                  QMessageBox::information(welcomeWidget,"QT网络通信","您已经退出房间！");
                  myServer->Socket->disconnectFromHost();
                  netState=false;
              }
          }
          else if(command[i][0]=="a")
          {
              gameWidget->close();
              delete gameWidget;

              delete self;
              delete player1;
              delete player2;
              delete player3;
              delete player4;

              delete p1out;
              delete p2out;
              delete p3out;
              delete p4out;
              p1out =nullptr;
              p2out =nullptr;
              p3out =nullptr;
              p4out =nullptr;

              self=nullptr;

              player1=nullptr;
              player2=nullptr;
              player3=nullptr;
              player4=nullptr;


              loadOnline();
              Distribute(playerIndex);
              gameWidget->roundInfo->addItem("新一局游戏");

              btnsSetFalse();


          }
          else
          {
            gameWidget->roundInfo->addItem(command[i]);
          }

}
  command.clear();

}

void gameRun::serverRecieve()
{
    QByteArray buffer=0;
    for(int i=0;i<myServer->ClientList.size();i++)
    {
        buffer+=myServer->ClientList.at(i)->readAll();
    }
    QString str=buffer;

    QStringList command;
    command=str.split("/");

    for(int i=0;i<command.size()-1;i++)
    {
    if(command[i][0]==QString::number(HHold))
      {
        QString send=command[i]+"/";
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(send.toUtf8());
        }
        int n=command[i].toInt()%10;
        gameWidget->roundInfo->addItem(name[n]+"选择闷牌");
        moneypool+=valUnseen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));
      }
      else if(command[i][0]==QString::number(CCheck))
      {
         QString send=command[i]+"/";
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(send.toUtf8());
        }
        gameWidget->roundInfo->addItem(name[command[i].toInt()%10]+"选择看牌");
        name[command[i].toInt()%10]+="(已看牌)";

      }
      else if(command[i][0]==QString::number(UUnseenCmp))
      {

        int n=command[i].toInt();
        int choose=n%10;if(choose>5)choose-=5;
        int chose =(n/10)%10;if(chose>5)chose-=5;
        Data info(UUnseenCmp,chose,choose);
        gameWidget->roundInfo->addItem(name[choose]+"选择闷开"+name[chose]);
        gameWidget->roundInfo->scrollToBottom();
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(info.data.toUtf8());
        }

        int out=cmpOnline(choose,chose);
        self->nowPlayers--;
        if(out==1)
           { self->isActive=0;
            gameWidget->roundInfo->addItem("你已出局！");
        }
        else
        {
        playerOut(out-1);

        gameWidget->roundInfo->addItem(name[out]+"出局！");
        }
        gameWidget->roundInfo->scrollToBottom();
        Data data(OOut,out);

         for(int i=0;i<myServer->ClientList.size();i++)
         {
             myServer->ClientList.at(i)->write(data.data.toUtf8());
         }
         moneypool+=valUnseen;
         gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));


      }
      else if(command[i][0]==QString::number(SSeenCmp))
      {

        int n=command[i].toInt();

        int choose=n%10;if(choose>5)choose-=5;
        int chose =(n/10)%10;if(chose>5)chose-=5;
        gameWidget->roundInfo->addItem(name[choose]+"选择开"+name[chose]);
        gameWidget->roundInfo->scrollToBottom();
        Data info(SSeenCmp,chose,choose);
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(info.data.toUtf8());
        }

        int out=cmpOnline(choose,chose);
        self->nowPlayers--;
        if(out==1)
           { self->isActive=0;
            gameWidget->roundInfo->addItem("你已出局！");
        }
        else
        {
        playerOut(out-1);

        gameWidget->roundInfo->addItem(name[out]+"出局！");
        }
        gameWidget->roundInfo->scrollToBottom();

        Data data(OOut,out);
         for(int i=0;i<myServer->ClientList.size();i++)
         {
             myServer->ClientList.at(i)->write(data.data.toUtf8());
         }

         moneypool+=valSeen;
         gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

      }
      else if(command[i][0]==QString::number(AAddMoney))
      {
        gameWidget->roundInfo->addItem(name[command[i].toInt()%10]+"选择加注");
        QString info=command[i]+"/";
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(info.toUtf8());
        }
        moneypool+=valSeen;
        gameWidget->nowMoney->setText("钱池:"+QString::number(moneypool));

      }

      else if(command[i][0]==QString::number(TurnBegein))
      {
        int n=(command[i].toInt()/10)%10;
        if(n>5)
            n-=5;

        if(n==1)
        {
            if(self->isActive)
           {
            gameWidget->roundInfo->addItem("你的回合");
            btnsSetTrue();
            Data data(TurnBegein,1);
            for(int i=0;i<myServer->ClientList.size();i++)
            {
                myServer->ClientList.at(i)->write(data.data.toUtf8());
            }
            }
            else
                NextTurn();


        }
        else
        {
            Data data(TurnBegein,n);
            for(int i=0;i<myServer->ClientList.size();i++)
            {
                myServer->ClientList.at(i)->write(data.data.toUtf8());
            }
            gameWidget->roundInfo->addItem(name[n]+"的回合");
        }

      }
      else if(command[i][0]==QString::number(PPass))
      {
        int n=command[i].toInt();
        QString send(command[i]+"/");
        for(int i=0;i<myServer->ClientList.size();i++)
        {
            myServer->ClientList.at(i)->write(send.toUtf8());
        }
        gameWidget->roundInfo->addItem(name[n%10]+"弃牌出局！");
        playerOut(n%10-1);

        self->nowPlayers--;


      }
    else if(command[i][0]=="c")
    {
        QMessageBox::information(gameWidget, "QT网络通信", "玩家"+command[i][1]+"离开！");
        QString send=command[i]+"/";
        for(int i=0;i<myServer->ClientList.size();i++)
        {
                myServer->ClientList.at(i)->write(send.toUtf8());
        }
        gameWidget->close();
        delete gameWidget;
        gameWidget=nullptr;
        welcomeWidget->show();

        myServer->ClientList.clear();
        myServer->Server->disconnect();
        myServer->Server->close();
        netState=false;
    }
      else
      {
          gameWidget->roundInfo->addItem(command[i]);
      }

}
    ifWon();

}

void gameRun::NextTurn()
{
    if(isServer)
    {
    if(player1->isActive)
    {
        dt=new Data(TurnBegein,2);
    }
    else if(player2->isActive)
    {
        dt=new Data(TurnBegein,3);
    }
    else if(player3->isActive)
    {
        dt=new Data(TurnBegein,4);
    }
    else if(player4->isActive)
    {
        dt=new Data(TurnBegein,5);
    }
    for(int i=0;i<myServer->ClientList.size();i++)
    {
        myServer->ClientList.at(i)->write(dt->data.toUtf8());

    }
    delete dt;
    return;
    }
    else
    {
        if(player1->isActive)
        {
            dt=new Data(TurnBegein,(playerIndex+1));
        }
        else if(player2->isActive)
        {
            dt=new Data(TurnBegein,(playerIndex+2));
        }
        else if(player3->isActive)
        {
            dt=new Data(TurnBegein,(playerIndex+3));
        }
        else if(player4->isActive)
        {
            dt=new Data(TurnBegein,(playerIndex+4));
        }
        myServer->Socket->write(dt->data.toUtf8());
    }
    return;
}

void gameRun::playerOut(int n)
{
    if(n==1)
    {
        player1->isActive=false;
        gameWidget->player1->setPixmap(*p1out);
    }
    else if(n==2)
    {
        player2->isActive=false;
        gameWidget->player2->setPixmap(*p2out);
    }
    else if(n==3)
    {
        player3->isActive=false;
        gameWidget->player3->setPixmap(*p3out);
    }
    else if(n==4)
    {
        player4->isActive=false;
        gameWidget->player4->setPixmap(*p4out);
    }
}
