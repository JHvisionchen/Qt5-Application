#ifndef TCPSERVER_H
#define TCPSERVER_H

//布局组件类
#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
//服务器类
#include "server.h"

class TcpServer : public QDialog
{
    Q_OBJECT
    
public:
    //构造函数
    TcpServer(QWidget *parent = 0,Qt::WindowFlags f=0);
    //析构函数
    ~TcpServer();

private:
    QListWidget *ContentListWidget;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;
    QGridLayout *mainLayout;

    int port;
    Server *server;

public slots:
    //新建聊天服务器槽
    void slotCreateServer();
    //更新服务器槽
    void updateServer(QString,int);
};

#endif // TCPSERVER_H
