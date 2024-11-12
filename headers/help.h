#ifndef HELP_H
#define HELP_H
#include<QWidget>
#include<mybutton.h>
#include<QPixmap>
#include<QGridLayout>
#include<QPalette>
#include<qlabel.h>
class help:public QWidget
{

public:
    QPalette *pal;
    QPixmap *pix;
    QGridLayout *lay;
    QLabel *bac;
    help();
    ~help();
    myButton *back;


};

#endif // HELP_H
