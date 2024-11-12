#include"sceneChoose.h"

sceneChoose::sceneChoose()
{
    background=new QMovie(":/gifs/image/background/chooseScene.gif");
    bac=new QLabel(this);
    bac->setMovie(background);
    bac->showFullScreen();
    bac->setScaledContents(true);
    bac->setGeometry(0,0,1920,1080);
    background->start();

    QPixmap pix1;
    QPixmap pix2;
    QPixmap pix3;

    pix1.load(":/background/image/background/hgwc.jpg");
    pix2.load(":/background/image/background/dksls.jpg");
    pix3.load(":/background/image/background/titan.jpg");

    btn1=new myButton(":/button/image/buttons/choose1.png",":/button/image/buttons/choose1Hover.png",250,225);
    btn2=new myButton(":/button/image/buttons/choose2.png",":/button/image/buttons/choose2Hover.png",250,225);
    btn3=new myButton(":/button/image/buttons/choose3.png",":/button/image/buttons/choose3Hover.png",250,225);
    btn4=new myButton(":/button/image/buttons/choose4.png",":/button/image/buttons/choose4Hover.png",500,450);

    Hgwc=new QLabel;
    Pldd=new QLabel;
    dksls= new QLabel;

    Hgwc->setPixmap(pix1);
    Pldd->setPixmap(pix3);
    dksls->setPixmap(pix2);

    Hgwc->setFixedSize(510,300);Hgwc->setScaledContents(true);
    Pldd->setFixedSize(510,300);Pldd->setScaledContents(true);
    dksls->setFixedSize(510,300);dksls->setScaledContents(true);

    lay=new QGridLayout;

    lay->setRowStretch(0,1);
    lay->setRowStretch(4,1);
    lay->setRowStretch(2,1);
    lay->setColumnStretch(0,1);
    lay->setColumnStretch(4,1);
    lay->setColumnStretch(2,1);
    lay->addWidget(Hgwc,1,1,1,1,Qt::AlignTop|Qt::AlignRight);
    lay->addWidget(Pldd,1,3,1,1,Qt::AlignTop|Qt::AlignLeft);
    lay->addWidget(dksls,3,2,1,1,Qt::AlignTop|Qt::AlignHCenter);
    lay->addWidget(btn1,1,1,1,1,Qt::AlignBottom|Qt::AlignHCenter);
    lay->addWidget(btn2,1,3,1,1,Qt::AlignBottom|Qt::AlignHCenter);
    lay->addWidget(btn3,3,2,1,1,Qt::AlignBottom|Qt::AlignHCenter);
    lay->addWidget(btn4,2,2,1,1,Qt::AlignCenter);

    this->setWindowTitle("进击！来自异世界的赌徒！");
    this->setLayout(lay);
    setWindowState(Qt::WindowMaximized);
//    this->setFixedSize(1920,1080);


}

sceneChoose::~sceneChoose()
{
    delete bac;
    delete background;
    delete lay;
    delete btn1;
    delete btn2;
    delete btn3;
    delete btn4;

}
