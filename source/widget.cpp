#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this -> setWindowFlags (Qt::Dialog|Qt::FramelessWindowHint);
    back=new myButton(":/button/image/buttons/back.png",":/button/image/buttons/backHover.png",200,180);
    again=new myButton(":/button/image/buttons/again.png",":/button/image/buttons/againHover.png",200,180);
    Continue=new myButton(":/button/image/buttons/continue.png",":/button/image/buttons/continueHover.png",200,180);
    lay=new QVBoxLayout;
    lay->setDirection(QVBoxLayout::TopToBottom);
    lay->addWidget(back);
    lay->addWidget(Continue);
    lay->addWidget(again);
    lay->setAlignment(Qt::AlignCenter);
    this->setLayout(lay);
    this->setFixedSize(300,500);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QObject::connect(Continue,&myButton::clicked,[=](){
        Continue->zoomIn();
        Continue->zoomOut();
        QTimer::singleShot(400,this,[=](){
            this->close();
        });
    });



}

Widget::~Widget()
{
    delete ui;

}

