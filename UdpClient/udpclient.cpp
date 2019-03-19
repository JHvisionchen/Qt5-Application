#include "udpclient.h"

//构造函数
UdpClient::UdpClient(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    //设置窗口名字
    setWindowTitle(tr("UDP Client"));
    //布局组建
    ReceiveTextEdit = new QTextEdit(this);
    CloseBtn = new QPushButton(tr("Close"),this);
    mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(ReceiveTextEdit);
    mainLayout->addWidget(CloseBtn);
    //连接关闭按钮信号及槽
    connect(CloseBtn,SIGNAL(clicked()),this,SLOT(CloseBtnClicked()));
    //端口号
    port =5555;
    //通讯套接字
    udpSocket = new QUdpSocket(this);
    //数据接受信号及槽
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    //套接字与端口绑定
    bool result=udpSocket->bind(port);
    if(!result)
    {
        QMessageBox::information(this,tr("error"),tr("udp socket create error!"));
        return;
    }
}
//析构函数
UdpClient::~UdpClient()
{
    
}
//关闭按钮槽
void UdpClient::CloseBtnClicked()
{
    close();
}
//数据接受槽
void UdpClient::dataReceived()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        udpSocket->readDatagram(datagram.data(),datagram.size());
        QString msg=datagram.data();
        ReceiveTextEdit->insertPlainText(msg);
    }
}
