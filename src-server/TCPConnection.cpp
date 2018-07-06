#include "TCPConnection.h"

TCPConnection::TCPConnection(QWidget *parent)
    : QWidget(parent)
{
    m_tcpserver = new QTcpServer(this);
    m_tcpsocket = new QTcpSocket(this);
    m_tcpserver->listen(QHostAddress::Any,8848);//监听的端口号
    connect(m_tcpserver,SIGNAL(newConnection()),this,SLOT(newConnect()));
}
void TCPConnection::newConnect()
{
    qDebug() << "Now connecting with client" << endl;
    m_tcpsocket = m_tcpserver->nextPendingConnection();//设置监听
    connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage())); //服务器接收客户端的消息
    connect(m_tcpsocket,SIGNAL(disconnected()),
                m_tcpsocket,SLOT(deleteLater()));
}


void TCPConnection::readMessage()
{
    QDataStream in(m_tcpsocket);
    in.setVersion (QDataStream::Qt_5_7);

    QStringList list;
    in >> list;

    sendMessage(list);
}

void TCPConnection::sendMessage(QStringList list)
{
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);

    QString function = list.at(0);
    list.removeFirst();

    if(function == "login"){
        QString username = list.at(0);
        QString password = list.at(1);
        int result = Login::login(username, password);
        out << function;
        out << result;

    }

    if(function == "info"){
        QStringList result = Login::info(list.at(0));
        out << function;
        out << result;

    }

    if(function == "send"){
        QString username = list.at(0);
        QString email = list.at(1);
        QString securityCode = list.at(2);
        int result = ForgetPassword::sendCode(username, email, securityCode);
        out << function;
        out << result;

    }

    if(function == "check"){
        QString username = list.at(0);
        QString pw1 = list.at(1);
        QString pw2 = list.at(2);
        QString code = list.at(3);
        QString securityCode = list.at(4);
        int result = ForgetPassword::checkCode(username, pw1, pw2, code, securityCode);
        out << function;
        out << result;

    }
    qDebug() << function << endl;
    m_tcpsocket->write(message);
}


