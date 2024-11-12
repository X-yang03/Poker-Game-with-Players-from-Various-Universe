#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include<QTcpServer>
#include<QTcpSocket>
#include<QList>

#include <QNetworkInterface>
namespace Ui {
class server;
}

class server : public QDialog
{
    Q_OBJECT

public:
    server(QWidget *parent = nullptr);
    ~server();

    QTcpServer *Server;
    QTcpSocket *Socket;

    QHostAddress *IP;
    quint16 *Port;

    void setIp();
    void setPort();

    quint16 port;//服务器端口
    QList<QTcpSocket*> ClientList;//保存所有和客户端通信的套接字

//private:
    Ui::server *ui;

signals:
    void cnt_clicked();
    void join_clicked();
private slots:
    void on_connect_clicked();
    void on_join_clicked();
};

#endif // SERVER_H
