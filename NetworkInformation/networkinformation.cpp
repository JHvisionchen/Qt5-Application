#include "networkinformation.h"

//构造函数
NetworkInformation::NetworkInformation(QWidget *parent)
    : QWidget(parent)
{
    //界面组建
    hostLabel = new QLabel(tr("主机名："));
    LineEditLocalHostName = new QLineEdit;
    ipLabel = new QLabel(tr("IP 地址："));
    LineEditAddress = new QLineEdit;
    detailBtn = new QPushButton(tr("详细"));
    //界面布局
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(hostLabel,0,0);
    mainLayout->addWidget(LineEditLocalHostName,0,1);
    mainLayout->addWidget(ipLabel,1,0);
    mainLayout->addWidget(LineEditAddress,1,1);
    mainLayout->addWidget(detailBtn,2,0,1,2);
    //调整窗口大小
    this->resize(QSize(400,100));
    //获取主机信息
    getHostInformation();
    //连接信号及槽
    connect(detailBtn,SIGNAL(clicked()),this,SLOT(slotDetail()));
}
//析构函数
NetworkInformation::~NetworkInformation()
{
    
}
//获取主机信息
void NetworkInformation::getHostInformation()
{
    QString localHostName = QHostInfo::localHostName();
    LineEditLocalHostName->setText(localHostName);

    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.isEmpty())
    {
        LineEditAddress->setText(listAddress.first().toString());
    }
}
//获取信息槽
void NetworkInformation::slotDetail()
{
    QString detail="";
    QList<QNetworkInterface> list=QNetworkInterface::allInterfaces();
    for(int i=0;i<list.count();i++)
    {
        QNetworkInterface interface=list.at(i);
        detail=detail+tr("设备：")+interface.name()+"\n";
        detail=detail+tr("硬件地址：")+interface.hardwareAddress()+"\n";
        QList<QNetworkAddressEntry> entryList=interface.addressEntries();
        for(int j=0;j<entryList.count();j++)
        {
            QNetworkAddressEntry entry=entryList.at(j);
            detail=detail+"\t"+tr("IP 地址：")+entry.ip().toString()+"\n";
            detail=detail+"\t"+tr("子网掩码：")+entry.netmask().toString()+"\n";
            detail=detail+"\t"+tr("广播地址：")+entry.broadcast().toString()+"\n";
        }
    }
    QMessageBox::information(this,tr("Detail"),detail);
}
