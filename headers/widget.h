﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"mybutton.h"
#include<QVBoxLayout>
#include<QPalette>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    myButton *back;
    myButton *again;
    myButton *Continue;
    QVBoxLayout *lay;

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
