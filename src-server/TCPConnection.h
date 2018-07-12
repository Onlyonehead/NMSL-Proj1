#ifndef STATUS_H
#define STATUS_H

#include <QWidget>
#include <QtNetwork>
#include "sqltool.h"
#include "store.h"
#include "myserver.h"

class TCPConnection : public QWidget
{
    Q_OBJECT

public:
    TCPConnection(QWidget *parent = 0);

private:

private slots:

};

#endif // STATUS_H
