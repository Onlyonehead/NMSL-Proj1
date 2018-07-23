#include "systemcenter.h"
#include "ui_systemcenter.h"
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
    int i = 0;
    for(QStringList list : clothes){
        ui->tableWidget_garmentInfo->insertRow(i);
        ui->tableWidget_garmentInfo->setItem(i, 0, new QTableWidgetItem(list.at(0)));
        ui->tableWidget_garmentInfo->setItem(i, 1, new QTableWidgetItem(list.at(1)));
        ui->tableWidget_garmentInfo->setItem(i, 2, new QTableWidgetItem(list.at(2)));
        ui->tableWidget_garmentInfo->setItem(i, 3, new QTableWidgetItem(list.at(3)));
        ui->tableWidget_garmentInfo->setItem(i, 4, new QTableWidgetItem(list.at(4)));
        i++;
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

void SystemCenter::on_clearGarment_clicked()
{
    ui->tableWidget_garmentInfo->setRowCount(0);

    ui->lineEdit_addGStyle->clear();;
    ui->checkBox_GsizeS->setChecked(false);
    ui->checkBox_GsizeM->setChecked(false);
    ui->checkBox_GsizeL->setChecked(false);
    ui->lineEdit_addGValue->clear();
    ui->label_showGPic->setText("Preview");
    ui->label_showPicPath->clear();
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


    QString garmentStyle;
    QString garmentSize;
    QString garmentValue;

    garmentStyle = ui->lineEdit_addGStyle->text().trimmed();//add garment style
    garmentValue = ui->lineEdit_addGValue->text().trimmed();//add garment value

    QString picName = garmentStyle + ".jpg";

    QString picPath = ui->label_showPicPath->text();

    if(garmentStyle == "" || garmentValue == "" || picPath == ""){
        QMessageBox::warning(this,"警告", "\n请输入全部字段！",QMessageBox::Close);
        return;
    }

    if(!ui->checkBox_GsizeS->isChecked() &&
            !ui->checkBox_GsizeM->isChecked() &&
            !ui->checkBox_GsizeL->isChecked()){
        QMessageBox::warning(this,"警告", "\n请至少选中一个size！",QMessageBox::Close);
        return;
    }

    QByteArray ba = garmentValue.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    {
        QMessageBox::warning(this,"警告", "\n价格请输入纯数字！",QMessageBox::Close);
        return;
    }

    list.append(garmentStyle);
    list.append(picName);
    list.append(garmentValue);
    if(ui->checkBox_GsizeS->isChecked()){
        garmentSize = ui->checkBox_GsizeS->text();
        list.append(garmentSize);
    }if(ui->checkBox_GsizeM->isChecked()){
        garmentSize = ui->checkBox_GsizeM->text();
        list.append(garmentSize);
    }if(ui->checkBox_GsizeL->isChecked()){
        garmentSize = ui->checkBox_GsizeL->text();
        list.append(garmentSize);
    }

    sendMessage(list);

    QBuffer buffer;
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    buffer.open(QIODevice::ReadWrite);
    QImage img;
    img.load(picPath);
    img.save(&buffer,"JPG");
    out << qint32(buffer.size());
    out << QString("/clothes/" + picName);
    out << buffer.data();

    m_socket->write(message);
    m_socket->flush();

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
                                                       tr("图片文件(*png *jpg)"));
    if(picture.isEmpty()){
        return ;
    }
    QString showPic = picture.join("/");
    QString picturePath = picture.at(0);
    QStringList Piclist = picturePath.split("/");
    QString pictureName = Piclist.at(Piclist.length() - 1);


    QPixmap pixmap(showPic);
    ui->label_showPicPath->setText(showPic);
    ui->label_showGPic->setPixmap(pixmap.scaled(162, 162, Qt::KeepAspectRatio,
                                                Qt::SmoothTransformation));
    ui->label_showGPic->show();

}

//老子写的

bool SystemCenter::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->label_showGPic) {
        if (event->type() == QEvent::DragEnter) {
            // [[2]]: 当拖放时鼠标进入label时, label接受拖放的动作
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
            dee->acceptProposedAction();
            return true;
        } else if (event->type() == QEvent::Drop) {
            // [[3]]: 当放操作发生后, 取得拖放的数据
            QDropEvent *de = dynamic_cast<QDropEvent *>(event);
            QList<QUrl> urls = de->mimeData()->urls();

            if (urls.isEmpty()) { return true; }
            QString path = urls.first().toLocalFile();

            // [[4]]: 在label上显示拖放的图片
            QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
            if (!image.isNull()) {
                image = image.scaled(162, 162,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
                ui->label_showGPic->setPixmap(QPixmap::fromImage(image));
                ui->label_showPicPath->setText(path);
            }

            return true;
        }
    }

    if (watched == ui->label_showNewPortrait) {
        if (event->type() == QEvent::DragEnter) {
            // [[2]]: 当拖放时鼠标进入label时, label接受拖放的动作
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
            dee->acceptProposedAction();
            return true;
        } else if (event->type() == QEvent::Drop) {
            // [[3]]: 当放操作发生后, 取得拖放的数据
            QDropEvent *de = dynamic_cast<QDropEvent *>(event);
            QList<QUrl> urls = de->mimeData()->urls();

            if (urls.isEmpty()) { return true; }
            QString path = urls.first().toLocalFile();

            // [[4]]: 在label上显示拖放的图片
            QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
            if (!image.isNull()) {
                image = image.scaled(142, 142,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
                ui->label_showNewPortrait->setPixmap(QPixmap::fromImage(image));
                ui->label_showNewPortraitPath->setText(path);
            }

            return true;
        }
    }

    if (watched == ui->label_showEditPortrait) {
        if (event->type() == QEvent::DragEnter) {
            // [[2]]: 当拖放时鼠标进入label时, label接受拖放的动作
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
            dee->acceptProposedAction();
            return true;
        } else if (event->type() == QEvent::Drop) {
            // [[3]]: 当放操作发生后, 取得拖放的数据
            QDropEvent *de = dynamic_cast<QDropEvent *>(event);
            QList<QUrl> urls = de->mimeData()->urls();

            if (urls.isEmpty()) { return true; }
            QString path = urls.first().toLocalFile();

            // [[4]]: 在label上显示拖放的图片
            QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
            if (!image.isNull()) {
                image = image.scaled(92, 92,
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
                ui->label_showEditPortrait->setPixmap(QPixmap::fromImage(image));
                ui->label_showEditPortraitPath->setText(path);
            }

            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}



