#include "server.h"

//构造函数
Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    //对指定端口的任意地址进行监控
    listen(QHostAddress::Any,port);
    //当有一个新的连接时会触发incomingconnection函数
}
//
void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    //更新数据
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    //断开连接槽
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    //
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    //添加tcp socket到列表
    tcpClientSocketList.append(tcpClientSocket);
}
//数据接收槽
void Server::updateClients(QString msg,int length)
{
    //发送更新服务器信号
    emit updateServer(msg,length);
    //
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->write(msg.toLatin1(),length)!=length)
        {
            continue;
        }
    }
}
//断开连接槽
void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}
