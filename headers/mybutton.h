#ifndef MYBUTTON_H
#define MYBUTTON_H
#include<QPushButton>
#include <QPropertyAnimation>
class myButton:public QPushButton
{
    Q_OBJECT
public:

    myButton(QString normalImg,QString hoverImg,int w=100,int h=90);
    ~myButton();
    QString normalImg;   //正常图片
    QString hoverImg;     //鼠标悬停的图片
    int w=100;
    int h=90;

    QPixmap *pix;
    QPixmap *pixHover;
    void zoomIn();        //弹动效果
    void zoomOut();

    void hover();        //实现悬浮效果
    void rev();
    void primeHover();   //相比hover没有放大效果
};


#endif // MYBUTTON_H
