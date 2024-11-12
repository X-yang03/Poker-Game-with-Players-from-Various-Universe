#include<videoWidget.h>

Video::Video()
{
    video=new QVideoWidget;
    list=new QMediaPlaylist;
    player=new QMediaPlayer;
    video->setParent(this);
    this->setFixedSize(1280,720);
    video->setFixedSize(1280,720);
    player->setVideoOutput(video);
    player->setMedia(QUrl::fromLocalFile("D:\\project\\宣讲录屏.mp4"));
    player->play();
    this -> setWindowFlags (Qt::Dialog|Qt::FramelessWindowHint);
}

Video::~Video()
{
    player->stop();
    delete player;
    delete list;
    delete video;
}

void Video::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {
      player->stop();
      delete this;
    }
}

