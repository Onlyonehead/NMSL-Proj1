#include "TCPConnection.h"

TCPConnection::TCPConnection(QWidget *parent)
    : QWidget(parent)
{
    MyServer *server = new MyServer;
    server->listen(QHostAddress::Any,8848);//监听的端口号
}
