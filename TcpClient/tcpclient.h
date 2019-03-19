#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

#include <QHostAddress>
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostInfo>

class TcpClient : public QDialog
{
    Q_OBJECT
    
public:
    //构造函数
    TcpClient(QWidget *parent = 0,Qt::WindowFlags f=0);
    //析构函数
    ~TcpClient();

private:
    QListWidget *contentListWidget;
    QLineEdit *sendLineEdit;
    QPushButton *sendBtn;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *serverIPLabel;
    QLineEdit *serverIPLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *enterBtn;
    QGridLayout *mainLayout;
    //连接状态
    bool status;
    //端口号
    int port;
    //服务器地址
    QHostAddress *serverIP;
    //用户名
    QString userName;
    //通讯套接字
    QTcpSocket *tcpSocket;

public slots:
    //连接槽
    void slotEnter();
    //连接执行槽
    void slotConnected();
    //断开执行槽
    void slotDisconnected();
    //数据接收槽
    void dataReceived();
    //发送数据槽
    void slotSend();
};

#endif // TCPCLIENT_H
