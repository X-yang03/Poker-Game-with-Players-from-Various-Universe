#include"gameStartWidget.h"

gameStartWidget::gameStartWidget()
{
    background=new QMovie; //加载gif
    bac = new QLabel(this);
    bac->showFullScreen();
    bac->setScaledContents(true);
    bac->setGeometry(0,0,1920,1080);

    esc=new Widget(this);  //按下esc后的窗口

   player1=new QLabel(this);  //头像用qlabel设置
   player2=new QLabel(this);
   player3=new QLabel(this);
   player4=new QLabel(this);
   self=new QLabel(this);

   card1=new QLabel(this);
   card2=new QLabel(this);
   card3=new QLabel(this);

   p1card1 =new QLabel(this);
   p1card2 =new QLabel(this);
   p1card3 =new QLabel(this);

   p2card1 =new QLabel(this);
   p2card2 =new QLabel(this);
   p2card3 =new QLabel(this);

   p3card1 =new QLabel(this);
   p3card2 =new QLabel(this);
   p3card3 =new QLabel(this);

   p4card1 =new QLabel(this);
   p4card2 =new QLabel(this);
   p4card3 =new QLabel(this);

   player1_icon=new QPixmap;
   player2_icon=new QPixmap;
   player3_icon=new QPixmap;
   player4_icon=new QPixmap;
   self_icon=new QPixmap(":/playerimages/image/players/lyl.jpg");

   QPixmap pokerBack(":/cardimages/image/cards/pokerBack.jpg");

   card1->setPixmap(pokerBack);
   card2->setPixmap(pokerBack);
   card3->setPixmap(pokerBack);
   p1card1->setPixmap(pokerBack);
   p1card2->setPixmap(pokerBack);
   p1card3->setPixmap(pokerBack);

   p2card1->setPixmap(pokerBack);
   p2card2->setPixmap(pokerBack);
   p2card3->setPixmap(pokerBack);

   p3card1->setPixmap(pokerBack);
   p3card2->setPixmap(pokerBack);
   p3card3->setPixmap(pokerBack);

   p4card1->setPixmap(pokerBack);
   p4card2->setPixmap(pokerBack);
   p4card3->setPixmap(pokerBack);

   card1->setFixedSize(150,225);card1->setScaledContents(true);
   card2->setFixedSize(150,225);card2->setScaledContents(true);
   card3->setFixedSize(150,225);card3->setScaledContents(true);

   p1card1 ->setFixedSize(90,135);  p1card1  ->setScaledContents(true);
   p1card2 ->setFixedSize(90,135);  p1card2  ->setScaledContents(true);
   p1card3 ->setFixedSize(90,135);  p1card3  ->setScaledContents(true);

   p2card1 ->setFixedSize(90,135);  p2card1  ->setScaledContents(true);
   p2card2 ->setFixedSize(90,135);  p2card2  ->setScaledContents(true);
   p2card3 ->setFixedSize(90,135);  p2card3  ->setScaledContents(true);

   p3card1 ->setFixedSize(90,135);  p3card1  ->setScaledContents(true);
   p3card2 ->setFixedSize(90,135);  p3card2  ->setScaledContents(true);
   p3card3 ->setFixedSize(90,135);  p3card3  ->setScaledContents(true);

   p4card1 ->setFixedSize(90,135);  p4card1  ->setScaledContents(true);
   p4card2 ->setFixedSize(90,135);  p4card2  ->setScaledContents(true);
   p4card3 ->setFixedSize(90,135);  p4card3  ->setScaledContents(true);


   self->setPixmap(*self_icon);

   player1->setFixedSize(200,200);player1->setScaledContents(true);
   player2->setFixedSize(200,200);player2->setScaledContents(true);
   player3->setFixedSize(200,200);player3->setScaledContents(true);
   player4->setFixedSize(200,200);player4->setScaledContents(true);
      self->setFixedSize(200,200);self->setScaledContents(true);

   hold=new myButton(":/button/image/buttons/hold.png",":/button/image/buttons/holdHover.png");
   check=new myButton(":/button/image/buttons/check.png",":/button/image/buttons/checkHover.png");
   unseen_cmp=new myButton(":/button/image/buttons/unseenCmp.png",":/button/image/buttons/unseenCmpHover.png");
   pass=new myButton(":/button/image/buttons/quit.png",":/button/image/buttons/quitHover.png");

   seen_cmp=check;
   addMoney=unseen_cmp;

   roundInfo=new QListWidget;
   roundInfo->setFixedSize(480,450);

   roundInfo->setStyleSheet("border-image:url(:/background/image/background/roundInfo.jpg);border-radius:30px;padding:4px 8px;font: 25 11pt 华文中宋;");
   roundInfo->setFrameShape(QListWidget::NoFrame);
   roundInfo->setGridSize(QSize(350,30));

   QPixmap m;
   m.load(":/background/image/background/coin1.jpg");
   money=new QLabel(this);
   money->setPixmap(m);
   money->setFixedSize(170,100);
   money->setScaledContents(true);

   QPixmap n;
   n.load(":/background/image/background/moneypool.png");
   moneypool=new QLabel(this);
   moneypool->setPixmap(n);
   moneypool->setFixedSize(180,180);
   moneypool->setScaledContents(true);

   coin=new QLabel;
   coin->setText("none");
   coin->setStyleSheet("color:rgb(192,192,192);font-size:30px;font-family: 华文中宋");

   nowMoney =new QLabel;
   nowMoney->setText("none");
   nowMoney->setStyleSheet("color:rgb(192,192,192);font-size:30px;font-family: 华文中宋");

   gameLayout=new QGridLayout;

   gameLayout->addWidget(player1,3,0,1,1,Qt::AlignLeft|Qt::AlignVCenter);
   gameLayout->addWidget(player2,0,2,1,1,Qt::AlignTop|Qt::AlignHCenter);
   gameLayout->addWidget(player3,0,6,1,1,Qt::AlignTop|Qt::AlignHCenter);
   gameLayout->addWidget(player4,3,8,1,1,Qt::AlignRight|Qt::AlignVCenter);
   gameLayout->addWidget(self,8,4,1,1,Qt::AlignBottom|Qt::AlignHCenter);

   gameLayout->addWidget(roundInfo,3,4,1,1,Qt::AlignCenter);

   gameLayout->addWidget(card1,8,0,1,1,Qt::AlignLeft);
   gameLayout->addWidget(card2,8,0,1,1,Qt::AlignHCenter);
   gameLayout->addWidget(card3,8,0,1,1,Qt::AlignRight);

   gameLayout->addWidget(money,8,8,1,1);
   gameLayout->addWidget(coin,8,8,1,1,Qt::AlignBottom|Qt::AlignHCenter);
   gameLayout->addWidget(moneypool,3,3,1,1,Qt::AlignBottom);
   gameLayout->addWidget(nowMoney,3,3,1,1,Qt::AlignHCenter);

   gameLayout->addWidget(hold,7,4,Qt::AlignBottom|Qt::AlignHCenter);
   gameLayout->addWidget(check,8,3,Qt::AlignRight);
   gameLayout->addWidget(unseen_cmp,8,5,Qt::AlignLeft);
   gameLayout->addWidget(pass,8,3,1,1,Qt::AlignBottom|Qt::AlignRight);

   gameLayout->addWidget(p1card1,3,1,Qt::AlignLeft);
   gameLayout->addWidget(p1card2,3,1,Qt::AlignHCenter);
   gameLayout->addWidget(p1card3,3,1,Qt::AlignRight);

   gameLayout->addWidget(p2card1,0,3,Qt::AlignLeft);
   gameLayout->addWidget(p2card2,0,3,Qt::AlignHCenter);
   gameLayout->addWidget(p2card3,0,3,Qt::AlignRight);

   gameLayout->addWidget(p3card1,0,5,Qt::AlignLeft);
   gameLayout->addWidget(p3card2,0,5,Qt::AlignHCenter);
   gameLayout->addWidget(p3card3,0,5,Qt::AlignRight);

   gameLayout->addWidget(p4card1,3,7,Qt::AlignLeft);
   gameLayout->addWidget(p4card2,3,7,Qt::AlignHCenter);
   gameLayout->addWidget(p4card3,3,7,Qt::AlignRight);
   this->setWindowTitle("进击！来自异世界的赌徒！");

   this->setLayout(gameLayout);
    setWindowState(Qt::WindowMaximized);
//   this->setFixedSize(1920,1080);

}

void gameStartWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
        esc->show();

    }
}

gameStartWidget::~gameStartWidget()
{


    delete money;  //
    delete coin;  //
    delete moneypool;   //
    delete nowMoney;   //

    delete background;   //
    delete bac;          //
    delete player1;
    delete player2;
    delete player3;
    delete player4;
    delete self;

    delete card1;
    delete card2;
    delete card3;

    delete p1card1;
    delete p1card2;
    delete p1card3;

    delete p2card1;
    delete p2card2;
    delete p2card3;

    delete p3card1;
    delete p3card2;
    delete p3card3;

    delete p4card1;
    delete p4card2;
    delete p4card3;

    delete player1_icon;
    delete player2_icon;
    delete player3_icon;
    delete player4_icon;
    delete self_icon;

    delete hold;
    delete check;
    delete unseen_cmp;
    delete pass;


   delete gameLayout;
   delete roundInfo;

}


