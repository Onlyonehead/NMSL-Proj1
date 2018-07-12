#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QObject>
#include <QtNetwork>
#include <QThread>
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
#include <QImage>
#include <QImageReader>

#include "myserver.h"
#include "login.h"
#include "forgetpassword.h"
#include "sqltool.h"
#include "warehouse.h"
#include "tool.h"
#include "garment.h"
#include "provider.h"
#include "staff.h"
#include "order.h"

class Processor : public QObject
{
    Q_OBJECT
public:
    explicit Processor(QTcpSocket*);

signals:

public slots:
    void work ();

private:
    QTcpSocket *m_socket;

};

#endif // PROCESSOR_H
