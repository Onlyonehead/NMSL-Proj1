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

    ui->lineEdit_sell_amount->setText("");
    ui->label_sell_idPurchase->setText(ui->tableWidget_check->item(row, 0)->text());//记录id_purchase
    ui->pushButton_change->setVisible(false);

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
    ui->pushButton_reject->setVisible(false);
    ui->label_storeN->setText("");
    ui->label_manager->setText("");
    ui->label_location->setText("");
    ui->lineEdit_sell_amount->setText("");
}

void SystemCenter::on_pushButton_commit_clicked()
{
    QString message = "purchaseId:"+ui->label_sell_idPurchase->text()+"\nfrom:"+ui->label_storeN->text()+"\nApprove this purchase request?";
    if(QMessageBox::Yes==QMessageBox::question(this, tr("request approval"), message, QMessageBox::Yes, QMessageBox::No)) {
        QStringList qsl_order;
        qsl_order.append("commitRequest");

        QString id_pur = ui->label_sell_idPurchase->text();
        qsl_order.append(id_pur);

        QString id_sto;
        for(int i=0; i<ui->tableWidget_check->rowCount(); ++i){
            if(ui->tableWidget_check->item(i, 0)->text() == id_pur){
                id_sto = ui->tableWidget_check->item(i, 1)->text();
                break;
            }
        }
        qsl_order.append(id_sto);

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
        qsl_order.append(time);

        for(int i=0; i<ui->tableWidget_checkDetail->rowCount(); ++i){
            qsl_order.append(ui->tableWidget_checkDetail->item(i, 0)->text());
            qsl_order.append(ui->tableWidget_checkDetail->item(i, 4)->text());
        }

        sendMessage(qsl_order);

    } else {
        qDebug()<<"放弃";
    }
}

void SystemCenter::on_pushButton_reject_clicked()
{
    QString message = "purchaseId:"+ui->label_sell_idPurchase->text()+"\nfrom:"+ui->label_storeN->text()+"\nReject this purchase request?";
    if(QMessageBox::Yes==QMessageBox::question(this, tr("request rejection"), message, QMessageBox::Yes, QMessageBox::No)) {
        QStringList qsl;
        qsl.append("requestReject");
        qsl.append(ui->label_sell_idPurchase->text());
        sendMessage(qsl);
    } else {
        qDebug()<<"放弃";
    }

}
