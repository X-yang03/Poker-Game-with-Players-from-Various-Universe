#ifndef SCENECHOOSE_H
#define SCENECHOOSE_H
#include"mybutton.h"
#include<QGridLayout>
#include<QLabel>
#include<QMovie>
class sceneChoose:public QWidget
{
public :
    sceneChoose();
    ~sceneChoose();

    QMovie *background;

    QLabel *bac;
    QLabel *Hgwc;  //关卡一
    QLabel *Pldd;  //关卡二
    QLabel *dksls;  //关卡三
    myButton *btn1;
    myButton *btn2;
    myButton *btn3;
    myButton *btn4; //关卡四不置图片
    QGridLayout *lay;  //布局控件

};

#endif // SCENECHOOSE_H
