#include "widget.h"
#include"gameStartWidget.h"
#include <QApplication>
#include"gameRun.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameRun h(nullptr);

    return a.exec();
}
