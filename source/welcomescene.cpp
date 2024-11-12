#include"welcomscene.h"
welcomeScene::welcomeScene()
{
   startGame=new myButton(":/button/image/buttons/start.png",":/button/image/buttons/startHover.png",200,180);
   quitGame=new myButton(":/button/image/buttons/quitgame.png",":/button/image/buttons/quitgameHover.png",200,180);

   help=new myButton(":/button/image/buttons/help.png",":/button/image/buttons/helpHover.png",200,180);

  cNt=new myButton(":/button/image/buttons/cNt.png",":/button/image/buttons/cNtHover.png",200,180);
  bac=new QLabel(this);
  QPixmap pix2(":/background/image/background/welcome.png");

  bac->setPixmap(pix2);
  bac->resize(1920,1080);
  bac->setScaledContents(true);

  startLayout=new QVBoxLayout;
  startLayout->setDirection(QVBoxLayout::TopToBottom);
  startLayout->addStretch(4);
  startLayout->addWidget(startGame);
  startLayout->addWidget(cNt);
  startLayout->addWidget(help);
  startLayout->addWidget(quitGame);
  startLayout->addStretch(2);
  startLayout->setAlignment(Qt::AlignCenter);
  setWindowState(Qt::WindowMaximized);
//  this->setFixedSize(1920,1080);

  this->setWindowTitle("进击！来自异世界的赌徒！");

  this->setLayout(startLayout);
};



