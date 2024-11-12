#ifndef WELCOMSCENE_H
#define WELCOMSCENE_H

#include<widget.h>
#include<QVBoxLayout>
#include<QLabel>
#include<QPixmap>
#include<QPalette>
#include"mybutton.h"
class welcomeScene:public QWidget
{
    Q_OBJECT

  public:
    QLabel *bac;
    welcomeScene();
    myButton *startGame;
    myButton *quitGame;
    myButton *help;
    QVBoxLayout *startLayout;
    myButton *cNt;

};

#endif // WELCOMSCENE_H
