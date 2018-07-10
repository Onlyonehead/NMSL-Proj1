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
}

void SystemCenter::on_tableWidget_logistics_A_itemClicked(QTableWidgetItem *item){

}
