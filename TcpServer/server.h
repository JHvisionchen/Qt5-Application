#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>

#include "tcpclientsocket.h"

//继承自tcpserver类
class Server : public QTcpServer
{
    Q_OBJECT

public:
    //构造函数
    Server(QObject *parent=0,int port=0);
    //用于保存每一个和客户端连接的socket
    QList<TcpClientSocket*> tcpClientSocketList;

signals:
    //更新服务器信号
    void updateServer(QString,int);

public slots:
    //更新客户端连接槽
    void updateClients(QString,int);
    //断开连接槽
    void slotDisconnected(int);

protected:
    //在tcpserver类中继承
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H
