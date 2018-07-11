#include "systemcenter.h"
#include "ui_systemcenter.h"

void SystemCenter::on_pushButton_showRequests_clicked()
{
    QStringList qsl;
    qsl.append("getAllRequests");
    sendMessage(qsl);
}

void SystemCenter::on_tableWidget_check_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->label_sell_idPurchase->setText(ui->tableWidget_check->item(row, 0)->text());//记录id_purchase
    ui->pushButton_change->setVisible(false);
    ui->pushButton_commit->setVisible(true);

    QString purchase_id = ui->tableWidget_check->item(row, 0)->text();
    QString store_id = ui->tableWidget_check->item(row, 1)->text();

    QStringList qsl;
    qsl.append("getCheckDetail");
    qsl.append(purchase_id);
    qsl.append(store_id);
    sendMessage(qsl);
}


void SystemCenter::on_tableWidget_checkDetail_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->label_sell_row->setText(QString::number(row, 10));//记录行号
    ui->lineEdit_sell_amount->setText(ui->tableWidget_checkDetail->item(row, 4)->text());
    ui->pushButton_change->setVisible(true);

}

void SystemCenter::on_pushButton_change_clicked()
{
    //比对表格和输入框中的数据，如果数据被修改
    if(ui->lineEdit_sell_amount->text()!=ui->tableWidget_checkDetail->item(ui->label_sell_row->text().toInt(), 3)->text()){
        QStringList qsl;
        qsl.append("changeAmount");

        QString purchase_id, row;
        purchase_id = ui->label_sell_idPurchase->text();
        row = ui->label_sell_row->text();

        qsl.append(purchase_id);//id_purchase
        qsl.append(ui->tableWidget_checkDetail->item(row.toInt(), 0)->text());//id_clothes
        qsl.append(ui->lineEdit_sell_amount->text());//new amount
        sendMessage(qsl);
    }
}

void SystemCenter::on_pushButton_clearRequests_clicked()
{
    ui->tableWidget_check->clear();
    ui->tableWidget_check->setRowCount(0);
    ui->tableWidget_checkDetail->clear();
    ui->tableWidget_checkDetail->setRowCount(0);
    ui->pushButton_change->setVisible(false);
    ui->pushButton_commit->setVisible(false);
    ui->label_storeN->setText("");
    ui->label_manager->setText("");
    ui->label_location->setText("");
}
