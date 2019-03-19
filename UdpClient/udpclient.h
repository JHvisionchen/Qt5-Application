#ifndef UDPCLIENT_H
#define UDPCLIENT_H

//布局类
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
//通讯类
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>

class UdpClient : public QDialog
{
    Q_OBJECT
    
public:
    //构造函数
    UdpClient(QWidget *parent = 0,Qt::WindowFlags f=0);
    //析构函数
    ~UdpClient();

public slots:
    //关闭按钮槽
    void CloseBtnClicked();
    //数据接受槽
    void dataReceived();

private:
    QTextEdit *ReceiveTextEdit;
    QPushButton *CloseBtn;
    QVBoxLayout *mainLayout;
    int port;
    QUdpSocket *udpSocket;
};

#endif // UDPCLIENT_H
