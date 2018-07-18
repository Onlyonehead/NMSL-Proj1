#include "systemcenter.h"
#include "ui_systemcenter.h"

void SystemCenter::on_pushButton_showArrive_clicked()
{
    ui->tw_sell_C1->verticalHeader()->setVisible(false);
    ui->tw_sell_C1->setRowCount(stores.size());
    ui->tw_sell_C1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_sell_C1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽

    int i=0;
    QVector<QStringList>::const_iterator it;
    for(it=stores.constBegin(); it!=stores.constEnd(); ++it, ++i){
        ui->tw_sell_C1->setItem(i, 0, new QTableWidgetItem(it->at(1)));
    }

}

void SystemCenter::on_tw_sell_C1_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->tw_sell_C3->setRowCount(0);
    //groupBox_shopC
    QString store_id, location, username;
    QString name = ui->tw_sell_C1->item(row, 0)->text();
    QVector<QStringList>::const_iterator its;
    for(its=stores.constBegin(); its!=stores.constEnd(); ++its){
        if(its->at(1) == name){
            store_id = its->at(0);

            if(""!=its->at(3))
                location = its->at(2)+"省"+its->at(3)+"市";
            else
                location = its->at(3)+"市";
            username = its->at(5);
            break;
        }
    }
    ui->label_storeN_C->setText(name);
    ui->label_manager_C->setText(username);
    ui->label_location_C->setText(location);

    //tw_sell_C2
    QStringList qsl;
    qsl.append("getArriveRecord");
    qsl.append(store_id);
    sendMessage(qsl);
}

void SystemCenter::on_tw_sell_C2_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    if(ui->tw_sell_C2->item(row, 2)->text()=="Checked"){
        QStringList qsl;
        qsl.append("getArriveDetail");
        qsl.append(ui->tw_sell_C2->item(row, 0)->text());
        sendMessage(qsl);
    }
}

void SystemCenter::on_pushButton_clearRequests_4_clicked()
{
    ui->label_storeN_C->setText("");
    ui->label_manager_C->setText("");
    ui->label_location_C->setText("");

    ui->tw_sell_C1->setRowCount(0);
    ui->tw_sell_C2->setRowCount(0);
    ui->tw_sell_C3->setRowCount(0);


}







