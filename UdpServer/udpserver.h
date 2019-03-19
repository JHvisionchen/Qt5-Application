#ifndef UDPSERVER_H
#define UDPSERVER_H

//布局组建
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
//通讯以及计时器
#include <QUdpSocket>
#include <QTimer>
#include <QHostAddress>

class UdpServer : public QDialog
{
    Q_OBJECT
    
public:
    //构造函数
    UdpServer(QWidget *parent = 0,Qt::WindowFlags f=0);
    //析构函数
    ~UdpServer();

public slots:
    //开始按钮点击槽
    void StartBtnClicked();
    //计时器到时处理槽
    void timeout();

private:
    QLabel *TimerLabel;
    QLineEdit *TextLineEdit;
    QPushButton *StartBtn;
    //布局组建
    QVBoxLayout *mainLayout;
    int port;
    bool isStarted;
    QUdpSocket *udpSocket;
    QTimer *timer;
};

#endif // UDPSERVER_H
