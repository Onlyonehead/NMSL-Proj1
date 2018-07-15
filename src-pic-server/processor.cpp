#include "processor.h"
#include <QDataStream>
#include <QImage>

#define DIR "/Users/Haibara/Documents/qt build files/Serverfiles/"

Processor::Processor(QTcpSocket* socket, QObject *parent) :
    QObject(parent)
{
    m_socket = socket;
}

void Processor::work ()
{


    //发送方代码

    /*

    QBuffer buffer;
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    buffer.open(QIODevice::ReadWrite);
    QImage img;
    img.load("/Users/Haibara/Desktop/a.jpg");
    img.save(&buffer,"JPG");
    out << qint32(buffer.size());
    out << QString("a.jpg");
    out << buffer.data();

    m_socket->write(message);
    m_socket->flush();
    qDebug("sendpic");


    */



    QDataStream in(m_socket);
    in.setVersion (QDataStream::Qt_5_7);

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    qDebug() << "sb";

    if(dataSize == 0)
    {
       if(m_socket->bytesAvailable() < (sizeof(quint32)+sizeof(QString)) )
       {
            return;
       }
       in >> dataSize;
       in >> fileName;
    }
    if(dataSize > qint32(m_socket->bytesAvailable()))
    {
       return;
    }

    QByteArray data;

    in>>data;

    QImage img;
    img.loadFromData(data);

    img.save(DIR + fileName);

    qDebug() << dataSize;
    qDebug() << fileName;
    qDebug() << img;
    qDebug() << "Done";
    qDebug() << "\n\n";

    dataSize = 0;
    fileName.clear();

//    out << "Done";

//    m_socket->write(message);
}
