#include "systemcenter.h"
#include "sqltool.h"
#include "ui_systemcenter.h"
#include "garment.h"
#include "ftpmanager.h"
#include <QPixmap>
#include <QVector>
#include <QStringList>
#include <QCompleter>
#include <QFileDialog>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QStringListModel>
#include <QFileInfo>
#include <QAbstractItemView>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QBuffer>
#include <QProcess>

/**
 * return all garments' information
 *
 * @author Yihan Dong
 * @return information
 */


void SystemCenter::on_pushButton_showGarment_clicked()
{
    ui->tableWidget_garmentInfo->setRowCount(0);
    ui->tableWidget_garmentInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_garmentInfo->verticalHeader()->setVisible(false);
    QStringList list;
    list.append("sp_sg");
    sendMessage(list);
}

/**
 * clear all garments' information
 *
 * @author Yihan Dong
 * @return void
 */

void SystemCenter::on_clearGarment_clicked()
{
    qDebug() << "clear garment info";
    ui->tableWidget_garmentInfo->clear();
    ui->tableWidget_garmentInfo->setRowCount(0);
    QStringList header;

    header << tr("服装编号") << tr("服装样式") << tr("服装大小") << tr("服装图片") << tr("服装价格");
    ui->tableWidget_garmentInfo->setHorizontalHeaderLabels(header);
}

/**
 * add new garment's information
 *
 * @author Yihan Dong
 * @return information
 * done
 */


void SystemCenter::on_pushButton_confirmAddG_clicked()
{



//    QStringList list;
//    list.append("sp_confirmAddG");


//    QString garmentStyle;
//    QString garmentSize;
//    QString garmentPic;
//    QString garmentValue;

//    garmentStyle = ui->lineEdit_addGStyle->text();//add garment style
//    garmentPic = ui->label_showPicName->text();//add garment pic
//    garmentValue = ui->lineEdit_addGValue->text();//add garment value
//    list.append(garmentStyle);
//    list.append(garmentPic);
//    list.append(garmentValue);
//    if(ui->checkBox_GsizeS->isChecked()){
//        garmentSize = ui->checkBox_GsizeS->text();
//        list.append(garmentSize);
//        sendMessage(list);
//    }if(ui->checkBox_GsizeM->isChecked()){
//        garmentSize = ui->checkBox_GsizeM->text();
//        list.append(garmentSize);
//        sendMessage(list);
//    }if(ui->checkBox_GsizeL->isChecked()){
//        garmentSize = ui->checkBox_GsizeL->text();
//        list.append(garmentSize);
//        sendMessage(list);
//    }

//    ui->lineEdit_addGStyle->clear();
//    ui->checkBox_GsizeS->setChecked(false);
//    ui->checkBox_GsizeM->setChecked(false);
//    ui->checkBox_GsizeL->setChecked(false);
//    ui->lineEdit_addGValue->clear();
//    ui->label_showGPic->clear();

//    QString showPic = ui->label_showPicPath->text();
//    QImage img(showPic);
//    QString pictureName = ui->label_showPicName->text();

//    QStringList list;
//    list.append("sp_sendPic");
//    list.append(pictureName);


//    QByteArray message;
//    QBuffer buffer(&message);
//    QDataStream out(&message,QIODevice::WriteOnly);

//    out.setVersion(QDataStream::Qt_5_7);
//    out << (quint16) 0;
//    buffer.open(QIODevice::ReadWrite);
//    img.save(&buffer, "PNG");
//    out << list;
//    out << buffer.data();
//    qDebug() << buffer.data();

//    message.append(buffer.data());


//    out.device()->seek(0);
//    out << (quint16) (message.size() - sizeof(quint16));
//    m_tcpsocket->write(message);

//    qDebug() << message.count();


    QString picPath = ui->label_showPicPath->text();
    QString picName = ui->label_showPicName->text();
    qDebug() << picPath;
    qDebug() << picName;
    ftpManager m_ftp;
    m_ftp.setHostPort("39.108.155.50", 21);
    m_ftp.setUserInfo("ftpuser", "abcd1234");
    m_ftp.put(picPath, "/ftpuser/project1/clothes/" + picName);
    connect(&m_ftp, SIGNAL(error(QNetworkReply::NetworkError)), this,SLOT(error(QNetworkReply::NetworkError)));



//    QProcess p(0);
//    QString openFTP = "ftp";
//    QString openIP = "open kousz.top";
//    QString username = "ftpuser";
//    QString password = "abcd1234";
//    QString enterLog = "cd /ftpuser/project1/clothes";
//    QString putPic = "PUT" + picPath;
//    QStringList list;
//    list.append(openFTP);
//    p.start("cmd.exe", list);

//    p.execute(openFTP);
//    p.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
//    p.execute(openIP);
//    p.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
//    p.execute(username);
//    p.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
//    p.execute(password);
//    p.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
//    p.execute(enterLog);
//    p.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());
//    p.execute(putPic);
//    p.waitForFinished();
//    qDebug() << QString::fromLocal8Bit(p.readAllStandardError());














//    QString surl = "ftp://ftpuser:abcd1234@39.108.155.50:21/ftpuser/project1/clothes";
//    QUrl Url = QUrl(surl + picName);
//    qDebug() << Url;
//    QFile file(picPath);
//    file.open(QIODevice::ReadOnly);
//    QByteArray data = file.readAll();
//    qDebug() << file.size();
//    qDebug() << data.size();
//    QNetworkRequest putRequest;
//    QNetworkAccessManager manager;
//    putRequest.setUrl(Url);
//    manager.put(putRequest, data);




}

/**
 * choose new garment's picture
 *
 * @author Yihan Dong
 * @return void
 * done
 * todo:add to server
 */

void SystemCenter::on_pushButton_setGPic_clicked()
{
    QStringList picture = QFileDialog::getOpenFileNames(this, tr("Open File"),
                                                       "C:\\Users\\Dong9\\Pictures\\Saved Pictures",
                                                       tr("图片文件(*png *jpg)"));
    QString showPic = picture.join("/");
    QString picturePath = picture.at(0);
    QStringList Piclist = picturePath.split("/");
    QString pictureName = Piclist.at(Piclist.length() - 1);
    qDebug() << pictureName;


    QPixmap pixmap(showPic);
    ui->label_showPicPath->setText(showPic);
    ui->label_showGPic->setPixmap(pixmap.scaled(ui->label_showGPic->size(), Qt::IgnoreAspectRatio));
    ui->label_showGPic->show();
    ui->label_showPicName->setText(pictureName);




//    QFile pushPic(picturePath);
//    pushPic.open(QIODevice::ReadOnly);
//    QByteArray by_pushPic = pushPic.readAll();
//    pushPic.close();
//    QNetworkAccessManager manager;
//    qDebug() << pictureName;
//    QString serverPath = "ftp://39.108.155.50/ftpuser/project1/clothes/";
//    QUrl URL = QUrl(serverPath + pictureName);
//    qDebug() << URL;
//    URL.setUserName("root");
//    URL.setPassword("abcd1234");
//    URL.setPort(21);



//    QNetworkRequest pushRequest;
//    pushRequest.setUrl(URL);

//    QNetworkReply *pushReply = manager.put(pushRequest, by_pushPic);






//    if(pushReply->error() == QNetworkReply::NoError){
//        qDebug() << "success";
//    }else {
//        qDebug() << "fail";
//    }

}


/**
 * cancel create new garment
 *
 * @author Yihan Dong
 * @return void
 */

void SystemCenter::on_pushButton_cancelAddG_clicked()
{
    ui->lineEdit_addGStyle->clear();;
    ui->checkBox_GsizeS->setChecked(false);
    ui->checkBox_GsizeM->setChecked(false);
    ui->checkBox_GsizeL->setChecked(false);
    ui->lineEdit_addGValue->clear();
    ui->label_showGPic->clear();
}


