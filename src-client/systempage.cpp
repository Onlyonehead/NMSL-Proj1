#include "systemcenter.h"
#include "sqltool.h"
#include "ui_systemcenter.h"
#include "garment.h"
#include <QPixmap>
#include <QVector>
#include <QStringList>
#include <QCompleter>
#include <QFileDialog>
#include <QImage>
#include <QImageReader>
#include <QStringListModel>
#include <QFileInfo>
#include <QAbstractItemView>

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
    QStringList list;
    list.append("sp_confirmAddG");
    sendMessage(list);


    QString garmentStyle;
    QString garmentSize;
    QString garmentPic;
    QString garmentValue;
    QFileInfo pictureInfo;

    garmentStyle = ui->lineEdit_addGStyle->text();//add garment style
    garmentPic = ui->label_showPicName->text();//add garment pic
    garmentValue = ui->lineEdit_addGValue->text();//add garment value
    if(ui->checkBox_GsizeS->isChecked()){
        garmentSize = ui->checkBox_GsizeS->text();
        Garment::addGarmentForm(garmentStyle, garmentSize, garmentPic, garmentValue);
    }if(ui->checkBox_GsizeM->isChecked()){
        garmentSize = ui->checkBox_GsizeM->text();
        Garment::addGarmentForm(garmentStyle, garmentSize, garmentPic, garmentValue);
    }if(ui->checkBox_GsizeL->isChecked()){
        garmentSize = ui->checkBox_GsizeL->text();
        Garment::addGarmentForm(garmentStyle, garmentSize, garmentPic, garmentValue);
    }

    ui->lineEdit_addGStyle->clear();
    ui->checkBox_GsizeS->setChecked(false);
    ui->checkBox_GsizeM->setChecked(false);
    ui->checkBox_GsizeL->setChecked(false);
    ui->lineEdit_addGValue->clear();
    ui->label_showGPic->clear();

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
    QStringList list;
    list.append("sp_setGPic");
    sendMessage(list);



    QString picture = QFileDialog::getOpenFileName(this, tr("文件对话框"),
                                                       "C:\\Users\\Dong9\\Pictures\\Saved Pictures",
                                                       tr("图片文件(*png *jpg)"));
    QPixmap pixmap(picture);
    QFileInfo pictureInfo = QFileInfo(picture);
    QString pictureName = pictureInfo.fileName();
    ui->label_showGPic->setPixmap(pixmap);
    ui->label_showGPic->show();
    ui->label_showPicName->setText(pictureName);
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


