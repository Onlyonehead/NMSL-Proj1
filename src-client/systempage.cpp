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


    QString picName = ui->label_showPicName->text();

    QStringList list;
    list.append("sp_confirmAddG");


    QString garmentStyle;
    QString garmentSize;
    QString garmentValue;

    garmentStyle = ui->lineEdit_addGStyle->text();//add garment style
    garmentValue = ui->lineEdit_addGValue->text();//add garment value
    list.append(garmentStyle);
    list.append(picName);
    list.append(garmentValue);
    if(ui->checkBox_GsizeS->isChecked()){
        garmentSize = ui->checkBox_GsizeS->text();
        list.append(garmentSize);
        sendMessage(list);
    }if(ui->checkBox_GsizeM->isChecked()){
        garmentSize = ui->checkBox_GsizeM->text();
        list.append(garmentSize);
        sendMessage(list);
    }if(ui->checkBox_GsizeL->isChecked()){
        garmentSize = ui->checkBox_GsizeL->text();
        list.append(garmentSize);
        sendMessage(list);
    }

    ui->lineEdit_addGStyle->clear();
    ui->checkBox_GsizeS->setChecked(false);
    ui->checkBox_GsizeM->setChecked(false);
    ui->checkBox_GsizeL->setChecked(false);
    ui->lineEdit_addGValue->clear();
    ui->label_showGPic->clear();



    QString picPath = ui->label_showPicPath->text();
    QBuffer buffer;
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    buffer.open(QIODevice::ReadWrite);
    QImage img;
    img.load(picPath);
    img.save(&buffer,"JPG");
    out << qint32(buffer.size());
    out << QString(picName);
    out << buffer.data();

    m_socket->write(message);
    m_socket->flush();
    qDebug("sendpic");

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
//    QString serverPath = "http://39.108.155.50/ftpuser/project1/clothes/";
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


