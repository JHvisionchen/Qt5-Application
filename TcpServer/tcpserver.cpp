#include "tcpserver.h"

//构造函数
TcpServer::TcpServer(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    //设置窗口名字
    setWindowTitle(tr("TCP Server"));
    //布局组件
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel(tr("端口："));
    PortLineEdit = new QLineEdit;
    CreateBtn = new QPushButton(tr("创建聊天室"));
    //组件布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ContentListWidget,0,0,1,2);
    mainLayout->addWidget(PortLabel,1,0);
    mainLayout->addWidget(PortLineEdit,1,1);
    mainLayout->addWidget(CreateBtn,2,0,1,2);
    //端口号
    port=8010;
    PortLineEdit->setText(QString::number(port));
    //创建聊天点击按钮与槽
    connect(CreateBtn,SIGNAL(clicked()),this,SLOT(slotCreateServer()));
}
//析构函数
TcpServer::~TcpServer()
{
    
}
//新建聊天服务器
void TcpServer::slotCreateServer()
{
    server = new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));

    CreateBtn->setEnabled(false);
}
//更新服务器槽
void TcpServer::updateServer(QString msg,int length)
{
    ContentListWidget->addItem(msg.left(length));
}
