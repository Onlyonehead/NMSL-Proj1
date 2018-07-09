#include "TCPConnection.h"

TCPConnection::TCPConnection(QWidget *parent)
    : QWidget(parent)
{
    MyServer *server = new MyServer;
    server->listen(QHostAddress::Any,8848);//监听的端口号
}
<<<<<<< HEAD
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


    //sissyVI--Start

    if(function == "getRecord"){
        out << function;
        QString store_id = list.at(0);
        int size;

        qDebug()<<"店铺ID为："<<store_id;
        QVector<Record> qv_record = Store::getRecord(store_id.toInt(), size);
        qDebug()<<"记录大小为："<<qv_record.size();

        out << qv_record.size();
        QVector<Record>::iterator it;
        for(it=qv_record.begin(); it!=qv_record.end(); ++it){
            out<<it->getIdTrans()<<it->getIdStore()<<it->getDate()<<it->getPrices();
            out<<it->getDetails();
        }

        out<< size;

    }

    if(function == "getStoreInfo"){
        out << function;
        QString username, size;
        username = list.at(0);
        size = list.at(1);
        QVector<QString> qv = Store::getStoreInfo(username, size);
        out << qv;
    }

    if(function == "getStock"){
        out << function;
        QVector<QVector<QString> > qv = Store::getStock(list.at(0));
        out << qv;
    }

    if(function == "getPicPath"){
        out << function;
        QString path = Store::getPicPath(list.at(1));
        out<<list.at(0)<<path;
    }

    if(function == "sellGoods"){
        out << function;
        int i=2;
        QVector<int> qv;
        while(list.at(i) != "#"){
            QString s1, s2;
            s1 = list.at(i++);
            s2 = list.at(i++);
            qv.append(s1.toInt());qv.append(s2.toInt());
        }
        if(Store::sellGoods(list.at(0), list.at(1), qv))
            out << QString("交易成功");
        else
            out << QString("交易失败");
    }

    if(function == "getAllClothes"){
        out << function;
        QVector<QStringList> qv;
        Store::getAllClothes(qv);
        out << qv;
    }

    //sissyVI--Finish


    qDebug() << function << endl;
    m_tcpsocket->write(message);
}


=======
>>>>>>> faaffdc84f655b4ee4ea3631e05215d153568b5a
