#include"mybutton.h"

myButton::myButton(QString normalImg,QString hoverImg,int w,int h)
{
    this->w=w;
    this->h=h;
    this->normalImg=normalImg;
    this->hoverImg=hoverImg;
    pixHover=new QPixmap;
    pixHover->load(hoverImg);
    pix =new QPixmap;
    pix->load(normalImg);
    *pix = pix->scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    *pixHover = pixHover->scaled(w*1.1, h*1.1, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setFixedSize(pix->width(), pix->height());//设置不规则图片样式
    this->setStyleSheet("border:none;"); //设置不规则图片样式
    this->setIcon(*pix); //设置图标及大小
    this->setIconSize(QSize(pix->width(), pix->height()));

}


void myButton::zoomIn()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
void myButton::zoomOut()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    //设置动画间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void myButton::hover()
{

    this->setFixedSize(pixHover->width(), pixHover->height());//设置不规则图片样式
    this->setIcon(*pixHover); //设置图标及大小
    this->setIconSize(QSize(pixHover->width(), pixHover->height()));
    this->setIcon(*pixHover);
}

void myButton::rev()
{

    this->setFixedSize(pix->width(), pix->height());//设置不规则图片样式
    this->setIcon(*pix); //设置图标及大小
    this->setIconSize(QSize(pix->width(), pix->height()));
     this->setIcon(*pix);
}

void myButton::primeHover()
{
    this->setIcon(*pixHover);
}

myButton::~myButton()
{
    delete pix;
    delete pixHover;
}
