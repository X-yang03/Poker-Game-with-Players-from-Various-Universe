#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H
#include<QMediaPlayer>
#include<QWidget>
#include<QMediaPlaylist>
#include<QVideoWidget>
#include<QKeyEvent>
class Video:public QWidget
{
public:
    Video();
    ~Video();

    void keyPressEvent(QKeyEvent *event);
    QVideoWidget *video;
    QMediaPlayer *player;
    QMediaPlaylist *list;


};

#endif // VIDEOWIDGET_H
