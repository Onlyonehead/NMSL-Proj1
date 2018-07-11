#include "systemcenter.h"
#include "ui_systemcenter.h"



void SystemCenter::on_pushButton_13_clicked()
{
    QStringList msg;
    msg.append("orderinfo");
    sendMessage(msg);
}



void SystemCenter::on_pushButton_12_clicked()
{
    ui->tableWidget_logistics_A->setRowCount(0);
    ui->tableWidget_logistics_B->setRowCount(0);
    ui->tableWidget_logistics_C->setRowCount(0);
    ui->tableWidget_logistics_D->setRowCount(0);
    ui->logistics_label_A->clear();
    ui->quantity_logistics->clear();
}

void SystemCenter::on_tableWidget_logistics_A_itemClicked(QTableWidgetItem *item){
    QVector<QStringList> vlist;
    vlist = this->orderList;
    QStringList order;
    for(QStringList l : vlist){
        if(l.at(0) == ui->tableWidget_logistics_A->item(item->row(), 0)->
                text().split(":")[1].trimmed()){
            order = l.at(3).split("#");
            break;
        }
    }
    qDebug() << order << endl;
}

void SystemCenter::on_tableWidget_logistics_B_itemClicked(QTableWidgetItem *item){

    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

    ui->logistics_label_A->setText(item->text().split(QRegExp("[-:]"))[3].trimmed());

    QStringList msg;
    msg.append("tWlAiC");
    msg.append(s);
    sendMessage(msg);
}

void SystemCenter::on_clothes_ADD_3_clicked()
{

}
