#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>
#include <QObject>

//继承自tcpsocket类
class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    //构造函数
    TcpClientSocket(QObject *parent=0);

signals:
    //接受到数据的信号
    void updateClients(QString,int);
    //断开连接信号
    void disconnected(int);

protected slots:
    //数据接受槽
    void dataReceived();
    //断开连接槽
    void slotDisconnected();
};

#endif // TCPCLIENTSOCKET_H
