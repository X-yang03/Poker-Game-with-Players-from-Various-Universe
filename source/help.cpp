#include"help.h"

help::help()
{
    pal=new QPalette;
    pix =new QPixmap;
    lay=new QGridLayout;
    bac=new QLabel;
    back= new myButton(":/button/image/buttons/goback.png",":/button/image/buttons/goback.png",100,100);
    pix->load(":/background/image/background/help.png");


    bac->setPixmap(*pix);
    bac->setFixedSize(1600,900);
    bac->setScaledContents(true);

    lay->addWidget(bac);
    this->setLayout(lay);

    setWindowState(Qt::WindowMaximized);
    back->setParent(this);
    back->raise();
//   this->setFixedSize(1920,1080);

}

help::~help()
{
    delete pal;
    delete pix;
    delete back;
    delete this;
}
