#include "systemcenter.h"
#include "sqltool.h"
#include "ui_systemcenter.h"
#include "login.h"
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
    QVector<QStringList> garmentInfo;
    Garment::Info(garmentInfo);
    int i = 0;
    int n = garmentInfo.size();
    ui->tableWidget_garmentInfo->setRowCount(garmentInfo.size());
    while (n) {
        ui->tableWidget_garmentInfo->setItem(i, 0, new QTableWidgetItem(garmentInfo.at(i).at(0)));
        ui->tableWidget_garmentInfo->setItem(i, 1, new QTableWidgetItem(garmentInfo.at(i).at(1)));
        ui->tableWidget_garmentInfo->setItem(i, 2, new QTableWidgetItem(garmentInfo.at(i).at(2)));
        ui->tableWidget_garmentInfo->setItem(i, 3, new QTableWidgetItem(garmentInfo.at(i).at(3)));
        ui->tableWidget_garmentInfo->setItem(i, 4, new QTableWidgetItem(garmentInfo.at(i).at(4)));
        i++;
        n--;
    }
    ui->tableWidget_garmentInfo->setRowCount(i);

    progressBar();
}

/**
 * clear all garments' information
 *
 * @author Yihan Dong
 * @return void
 */

void SystemCenter::on_pushButton_clearGarment_clicked()
{
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
 * undone!
 * todo:insert complete with SIGNAL & SLOTS
 */


void SystemCenter::on_pushButton_confirmAddG_clicked()
{
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
 * ubdone
 * todo:add to server
 */

void SystemCenter::on_pushButton_setGPic_clicked()
{
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


