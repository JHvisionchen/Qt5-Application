#include "udpserver.h"

//构造函数
UdpServer::UdpServer(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent,f)
{
    //设置窗体名字
    setWindowTitle(tr("UDP Server"));
    //各个组件
    TimerLabel = new QLabel(tr("计时器："),this);
    TextLineEdit = new QLineEdit(this);
    StartBtn = new QPushButton(tr("开始"),this);
    //布局组建
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(TimerLabel);
    mainLayout->addWidget(TextLineEdit);
    mainLayout->addWidget(StartBtn);
    //开始按钮点击与槽连接
    connect(StartBtn,SIGNAL(clicked()),this,SLOT(StartBtnClicked()));
    //端口号
    port =5555;
    isStarted=false;
    //通讯udp套接字
    udpSocket = new QUdpSocket(this);
    //计时器
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}
//析构函数
UdpServer::~UdpServer()
{
    
}
//开始按钮点击槽
void UdpServer::StartBtnClicked()
{
    if(!isStarted)
    {
        StartBtn->setText(tr("停止"));
        timer->start(1000);
        isStarted =true;
    }
    else
    {
        StartBtn->setText(tr("开始"));
        isStarted = false;
        timer->stop();
    }
}
//计时器到时处理槽
void UdpServer::timeout()
{
    QString msg = TextLineEdit->text();
    int length=0;
    if(msg=="")
    {
       return;
    }
    //发送文字框中的内容
    if((length=udpSocket->writeDatagram(msg.toLatin1(),msg.length(),QHostAddress::Broadcast,port))!=msg.length())
    {
        return;
    }
}
