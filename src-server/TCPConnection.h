#ifndef STATUS_H
#define STATUS_H

#include <QWidget>
#include <QtNetwork>
#include <QWidget>
#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <QSqlQuery>
#include <QFontDatabase>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDateTime>
#include <QTime>
#include <QDate>

#include "login.h"
#include "forgetpassword.h"
#include "sqltool.h"
#include "record.h"
#include "store.h"

class TCPConnection : public QWidget
{
    Q_OBJECT

public:
    TCPConnection(QWidget *parent = 0);
    void sendMessage(QStringList);

private:
    QTcpSocket *m_tcpsocket;
    QTcpServer *m_tcpserver;

private slots:
    void newConnect();
    void readMessage();

};

#endif // STATUS_H
