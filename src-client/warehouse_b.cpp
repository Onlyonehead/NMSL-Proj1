#include "systemcenter.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


void SystemCenter::on_pushButton_8_clicked()
{
    QStringList msg;
    msg.append("pB8");
    sendMessage(msg);

}

void SystemCenter::on_tableWidget_B_itemClicked(QTableWidgetItem *item){

    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QString s = item->text().split("-")[0].trimmed();

    QStringList msg;
    msg.append("tWBiC");
    msg.append(s);
    sendMessage(msg);

}


void SystemCenter::on_pushButton_9_clicked()
{
    ui->warehouse_search_B->clear();
    ui->tableWidget_B->setRowCount(0);
    QPixmap *pixmap = new QPixmap(":/default.jpg");
    QApplication::processEvents();
    ui->label_clothes->setScaledContents(true);
    ui->label_clothes->setPixmap(*pixmap);

    delete pixmap;

    ui->label_29->clear();
    ui->label_30->clear();
    ui->label_31->clear();
    ui->label_32->clear();
    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QApplication::processEvents();
}


void SystemCenter::on_icon_search_B_clicked()
{

    QStringList msg;
    msg.append("isB");
    sendMessage(msg);
}
