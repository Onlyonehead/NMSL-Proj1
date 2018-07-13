#include "qtmap.h"
#include "ui_qtmap.h"
#include <QFileInfo>
#include <QWebEngineView>
#include <QWebChannel>
#include "bridge.h"
#include <QJsonObject>
#include <QJsonArray>

QtMap::QtMap(QString surl) :
    ui(new Ui::QtMap)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("QFrame{border-radius:10px;}");

    move(185,80);


    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject("bridge", &bridge);
//    QFileInfo file("/Users/Haibara/Desktop/index.html");
    QString url = surl;
//    url += file.absoluteFilePath();

    connect(ui->widget_web, SIGNAL(loadFinished(bool)), this, SLOT(slotSendDataToH5(bool)));
    ui->widget_web->page()->setWebChannel(channel);
    ui->widget_web->setUrl(QUrl(url));// spath为地址
}

QtMap::~QtMap()
{
    delete ui;
}

void QtMap::slotSendDataToH5(bool ok)
{
    if (ok){
        QJsonArray array;
        for(QStringList l : warehouse){
            QJsonObject o;
            o.insert("name", l.at(1));
            QJsonArray a;
            a.append(l.at(6));
            a.append(l.at(7));
            o.insert("position", QJsonValue(a));
            array.push_back(o);
        }


        emit bridge.signalToWeb(array);
    }
    else
        qDebug()<<"load failed! ok="<<ok;
}

void QtMap::webInit(QVector<QStringList> v){
    this->warehouse.clear();
    this->warehouse = v;
}

void QtMap::on_pushButton_clicked()
{
    this->close();
}
