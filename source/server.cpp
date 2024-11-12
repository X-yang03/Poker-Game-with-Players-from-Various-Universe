#include "server.h"
#include "ui_server.h"

server::server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);

    Server=new QTcpServer();
    Socket=new QTcpSocket();
    IP=new QHostAddress;
    Port=new quint16;
    ui->portLine->setText("8888");
    setWindowTitle("入侵！");
    ui->IPLine->setPlaceholderText("请输入房间IP");


}

server::~server()
{
    delete ui;
}

void server::setIp()
{
     ui->IPLine->setText(QNetworkInterface().allAddresses().at(1).toString());
}

void server::setPort()
{

}

void server::on_connect_clicked()
{
    this->setIp();
    emit cnt_clicked();
}



void server::on_join_clicked()
{
     *Port = ui->portLine->text().toShort();
      IP->setAddress(ui->IPLine->text());
      Socket->connectToHost(*IP,*Port);
      emit join_clicked();
}
