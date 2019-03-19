#include "tcpclient.h"

//构造函数
TcpClient::TcpClient(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    //设置窗体名字
    setWindowTitle(tr("TCP Client"));
    //组件布局
    contentListWidget = new QListWidget;
    sendLineEdit = new QLineEdit;
    sendBtn = new QPushButton(tr("发送"));
    userNameLabel = new QLabel(tr("用户名："));
    userNameLineEdit = new QLineEdit;
    serverIPLabel = new QLabel(tr("服务器地址："));
    serverIPLineEdit = new QLineEdit;
    portLabel = new QLabel(tr("端口："));
    portLineEdit = new QLineEdit;
    enterBtn= new QPushButton(tr("进入聊天室"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(contentListWidget,0,0,1,2);
    mainLayout->addWidget(sendLineEdit,1,0);
    mainLayout->addWidget(sendBtn,1,1);
    mainLayout->addWidget(userNameLabel,2,0);
    mainLayout->addWidget(userNameLineEdit,2,1);
    mainLayout->addWidget(serverIPLabel,3,0);
    mainLayout->addWidget(serverIPLineEdit,3,1);
    mainLayout->addWidget(portLabel,4,0);
    mainLayout->addWidget(portLineEdit,4,1);
    mainLayout->addWidget(enterBtn,5,0,1,2);
    //连接状态
    status = false;
    //端口号
    port = 8010;
    portLineEdit->setText(QString::number(port));
    //服务器地址
    serverIP =new QHostAddress();
    //连接按钮
    connect(enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));
    //发送按钮
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(slotSend()));
    //发送按钮默认不可控
    sendBtn->setEnabled(false);
}
//析构函数
TcpClient::~TcpClient()
{
    
}
//连接槽
void TcpClient::slotEnter()
{
    //没有连接
    if(!status)
    {
        //完成输入合法性检验
        QString ip = serverIPLineEdit->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
            return;
        }

        if(userNameLineEdit->text()=="")
        {
            QMessageBox::information(this,tr("error"),tr("User name error!"));
            return;
        }

        userName=userNameLineEdit->text();

        tcpSocket = new QTcpSocket(this);
        //套接字连接
        connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        //断开套接字连接
        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        //数据接收
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
        //连接到服务器
        tcpSocket->connectToHost(*serverIP,port);
        //连接状态更新
        status=true;
    }
    //以及连接
    else
    {
        int length=0;
        QString msg=userName+tr(":Leave Chat Room");
        if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg. length())
        {
            return;
        }
        //断开连接
        tcpSocket->disconnectFromHost();
        //连接状态更新
        status=false;
    }
}
//连接执行槽
void TcpClient::slotConnected()
{
    sendBtn->setEnabled(true);
    enterBtn->setText(tr("离开"));

    int length=0;
    QString msg=userName+tr(":Enter Chat Room");
    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
    {
        return;
    }
}
//发送数据槽
void TcpClient::slotSend()
{
    if(sendLineEdit->text()=="")
    {
        return ;
    }

    QString msg=userName+":"+sendLineEdit->text();

    tcpSocket->write(msg.toLatin1(),msg.length());
    sendLineEdit->clear();
}
//断开执行槽
void TcpClient::slotDisconnected()
{
    sendBtn->setEnabled(false);
    enterBtn->setText(tr("进入聊天室"));
}
//数据接收槽
void TcpClient::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        tcpSocket->read(datagram.data(),datagram.size());

        QString msg=datagram.data();
        contentListWidget->addItem(msg.left(datagram.size()));
    }
}
