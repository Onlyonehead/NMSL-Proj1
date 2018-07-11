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
    ui->logistics_label_B->clear();
    ui->quantity_logistics->clear();
    wh_id.clear();
    order_id.clear();
    replenishment.clear();
    wh_info.clear();

}

void SystemCenter::on_tableWidget_logistics_A_itemClicked(QTableWidgetItem *item){

    ui->tableWidget_logistics_C->setRowCount(0);
    replenishment.clear();
    wh_id.clear();
    order_id.clear();
    ui->tableWidget_logistics_D->setRowCount(0);
    QVector<QStringList> vlist;
    vlist = this->orderList;
    QStringList order;
    QString wh;
    order_id = ui->tableWidget_logistics_A->item(item->row(), 0)->
            text().split(":")[1].trimmed();
    for(QStringList l : vlist){
        if(l.at(0) == ui->tableWidget_logistics_A->item(item->row(), 0)->
                text().split(":")[1].trimmed()){
            order = l.at(3).split("#");
            for(QStringList ll : warehouse){
                if(ll.at(0) == l.at(1)){
                    wh += ll.at(0) + " - " + ll.at(1);
                    break;
                }
            }
            break;
        }
    }

    ui->logistics_label_B->setText(wh);


    int n = order.size();
    while(n){
        QString s_clothes;
        ui->tableWidget_logistics_D->insertRow((order.size() - n) / 2);
        for(QStringList l : clothes){
            if(l.at(0) == order.at(n-2)){
                s_clothes += order.at(n-2) + " - " + l.at(1);
                break;
            }
        }
        ui->tableWidget_logistics_D->setItem((order.size() - n) / 2, 0, new QTableWidgetItem(s_clothes));
        ui->tableWidget_logistics_D->setItem((order.size() - n) / 2, 1, new QTableWidgetItem("0"));
        ui->tableWidget_logistics_D->setItem((order.size() - n) / 2, 2, new QTableWidgetItem("of:  " +order.at(n-1)));
        n -= 2;
    }
    ui->tableWidget_logistics_D->setRowCount(order.size() / 2);

    if(this->wh_info.size() == 0){
        QStringList msg;
        msg.append("tWlAiC");
        sendMessage(msg);
    }else{
        QStringList list = wh_info;
        int n = list.size();
        QString s = ui->logistics_label_B->text().split("-")[0].trimmed();


        int count = 0;
        while(n){

            QApplication::processEvents();
            if(s != list.at(list.size()-n).split(QRegExp("[-:]"))[1].trimmed()){
                ui->tableWidget_logistics_B->insertRow(count);
                ui->tableWidget_logistics_B->setItem(count, 0, new QTableWidgetItem(list.at(list.size()-n)));
                count++;
            }
            n--;
        }

        ui->tableWidget_logistics_B->setRowCount(count);
    }
}

void SystemCenter::on_tableWidget_logistics_B_itemClicked(QTableWidgetItem *item){

    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            item->text().split(QRegExp("[-:]"))[3].trimmed();

    this->wh_id = s;

    ui->tableWidget_logistics_C->setRowCount(0);

    QMap<QString, QString> stock;

    stock = this->stock_map.value(wh_id.split("-")[0].trimmed());

    QVector<QStringList> g = this->clothes;

    QMap<QString, QString> clothes;

    for(QStringList l : g){
        clothes.insert(l.at(0), l.at(1));
    }

    QApplication::processEvents();

    int count = 0;
    for(QMap<QString, QString>::const_iterator i = stock.begin(); i != stock.end(); ++i){
        QString clothes_name;
        clothes_name = clothes.value(i.key());
        QApplication::processEvents();
        ui->tableWidget_logistics_C->insertRow(count);
        ui->tableWidget_logistics_C->setItem(count, 0, new QTableWidgetItem(i.key() +
                                                                   " - " + clothes_name));
        ui->tableWidget_logistics_C->setItem(count, 1, new QTableWidgetItem(i.value()));

        QApplication::processEvents();
        count++;
    }

    ui->tableWidget_logistics_C->setRowCount(count);


    progressBar_fast();
}

void SystemCenter::on_tableWidget_logistics_C_itemClicked(QTableWidgetItem *item){

    QString s = ui->tableWidget_logistics_C->item(item->row(), 0)->text().trimmed();

    ui->logistics_label_A->setText(s);

}

void SystemCenter::on_logistics_ADD_clicked()
{
    QString clothes_id = ui->logistics_label_A->text();
    QString warehouse_id = this->wh_id.split("-")[0].trimmed();
    QString quantity = ui->quantity_logistics->text();
    if(clothes_id.trimmed() == "" || clothes_id.trimmed() == "-"
            || warehouse_id.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请选中仓库和衣服！",QMessageBox::Close);
        return;
    }

    if(quantity.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入数量！",QMessageBox::Close);
        return;
    }
    bool flag = false;
    for(int i = 0; i < ui->tableWidget_logistics_D->rowCount(); i++){
        if(ui->tableWidget_logistics_D->item(i, 0)->text() == clothes_id){
            if(ui->tableWidget_logistics_D->item(i, 1)->text().trimmed() ==
                    ui->tableWidget_logistics_D->item(i, 2)->text().split(":")[1].trimmed()){
                QMessageBox::warning(this,"警告", "\n该商品数量已达到需求！",QMessageBox::Close);
                ui->quantity_logistics->clear();
                return;
            }
            if((ui->tableWidget_logistics_D->item(i, 2)->text().split(":")[1].trimmed().toInt()-
                    ui->tableWidget_logistics_D->item(i, 1)->text().trimmed().toInt()
                 < quantity.trimmed().toInt())){
                quantity = QString::number(ui->tableWidget_logistics_D->item(i, 2)->text().split(":")[1].
                        trimmed().toInt() - ui->tableWidget_logistics_D->item(i, 1)->text().trimmed().toInt());
                QMessageBox::warning(this,"警告", "\n数量超过需求！\n\n实际添加：" + quantity,QMessageBox::Close);
            }
            QMap<QString, QString> map;
            map = replenishment.value(warehouse_id);
            int num = map.value(clothes_id.split("-")[0].trimmed()).toInt();
            map.insert(clothes_id.split("-")[0].trimmed(), QString::number(quantity.toInt() + num));
            replenishment[warehouse_id] = map;

            ui->tableWidget_logistics_D->item(i, 1)->setText(QString::number(ui->tableWidget_logistics_D->
                    item(i, 1)->text().toInt() + quantity.toInt()));

            ui->tableWidget_logistics_D->insertRow(i+1);
            ui->tableWidget_logistics_D->setItem(i+1, 0, new QTableWidgetItem(""));
            ui->tableWidget_logistics_D->setItem(i+1, 1, new QTableWidgetItem(quantity));
            ui->tableWidget_logistics_D->setItem(i+1, 2, new QTableWidgetItem(wh_id));

            flag = true;
            break;
        }
    }
    if(!flag){
        QMessageBox::warning(this,"警告", "\n无需添加该商品！",QMessageBox::Close);
    }
    ui->quantity_logistics->clear();
}

void SystemCenter::on_logistics_send_clicked()
{
    for(int i = 0; i < ui->tableWidget_logistics_D->rowCount(); i++){
        if(ui->tableWidget_logistics_D->item(i, 0)->text() != ""){
            if(ui->tableWidget_logistics_D->item(i, 1)->text().trimmed() !=
                    ui->tableWidget_logistics_D->item(i, 2)->text().split(":")[1].trimmed()){
                QMessageBox::warning(this,"警告", "\n商品需求未达到，请继续添加！",QMessageBox::Close);
                return;
            }
        }
    }

    QStringList list;
    list.append("send_replenishment");

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << (quint16) 0;

    out << list;
    out << order_id;
    out << ui->logistics_label_B->text();
    out << replenishment;

    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    m_tcpsocket->write(message);
}
