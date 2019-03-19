#include "tcpclientsocket.h"

//构造函数
TcpClientSocket::TcpClientSocket(QObject *)
{
    //数据接受槽
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    //断开连接槽
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
//数据接受槽
void TcpClientSocket::dataReceived()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[1024];
        read(buf,length);

        QString msg=buf;
        //发送接受到数据的信号
        emit updateClients(msg,length);
    }
}
//断开连接槽
void TcpClientSocket::slotDisconnected()
{
    //发送断开连接信号
    emit disconnected(this->socketDescriptor());
}
