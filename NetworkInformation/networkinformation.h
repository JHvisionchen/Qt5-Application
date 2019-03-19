#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

//可视界面类
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
//网络信息类
#include <QHostInfo>
#include <QNetworkInterface>

class NetworkInformation : public QWidget
{
    Q_OBJECT
    
public:
    //构造函数
    NetworkInformation(QWidget *parent = 0);
    //析构函数
    ~NetworkInformation();
    //获取主机信息
    void getHostInformation();

public slots:
    //信息获取槽
    void slotDetail();

private:
    QLabel *hostLabel;
    QLineEdit *LineEditLocalHostName;
    QLabel *ipLabel;
    QLineEdit *LineEditAddress;
    //详细信息按钮
    QPushButton *detailBtn;
    //布局组建
    QGridLayout *mainLayout;
};

#endif // NETWORKINFORMATION_H
