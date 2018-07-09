#include "systemcenter.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


void SystemCenter::on_pushButton_10_clicked()
{
    QStringList msg;
    msg.append("pB10");
    sendMessage(msg);
}

void SystemCenter::on_pushButton_11_clicked()
{
    ui->warehouse_search_D->clear();
    ui->tableWidget_D1->setRowCount(0);
    ui->tableWidget_D2->setRowCount(0);
    QPixmap *pixmap = new QPixmap(":/default.jpg");
    QApplication::processEvents();
    ui->label_clothes_D->setScaledContents(true);
    ui->label_clothes_D->setPixmap(*pixmap);

    delete pixmap;

    ui->label_72->clear();
    ui->label_73->clear();
    ui->label_74->clear();
    ui->label_75->clear();

    QApplication::processEvents();
}

void SystemCenter::on_tableWidget_D1_itemClicked(QTableWidgetItem *item){

    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QString s = item->text().split("-")[0].trimmed();

    QStringList msg;
    msg.append("tWD1iC");
    msg.append(s);
    sendMessage(msg);

}

void SystemCenter::on_tableWidget_D2_itemClicked(QTableWidgetItem *item){

    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QString s = item->text().split("-")[0].trimmed();

    ui->warehouse_label_D->setText(item->text().split("-")[1].trimmed());

    QStringList msg;
    msg.append("tWD2iC");
    msg.append(s);
    sendMessage(msg);

}


void SystemCenter::on_clothes_ADD_clicked()
{

    int count = ui->tableWidget_D4->rowCount();
    for(int i = 0; i < count; i++){
        if(ui->tableWidget_D4->item(i, 0)->text().trimmed() ==
                ui->tableWidget_D2->currentItem()->text().trimmed() &&
                ui->tableWidget_D4->item(i, 1)->text().trimmed() ==
                ui->tableWidget_D1->currentItem()->text().trimmed()){
            ui->tableWidget_D4->item(i, 2)->setText(
                        QString::number(ui->quantity_D->text().toInt() +
                        ui->tableWidget_D4->item(i, 2)->text().toInt()));
            return ;
        }

    }
    ui->tableWidget_D4->insertRow(count);

    ui->tableWidget_D4->setItem(count, 0, new QTableWidgetItem(ui->tableWidget_D2->currentItem()
                                                           ->text().trimmed()));
    ui->tableWidget_D4->setItem(count, 1, new QTableWidgetItem(ui->tableWidget_D1->currentItem()
                                                           ->text().trimmed()));
    ui->tableWidget_D4->setItem(count, 2, new QTableWidgetItem(ui->quantity_D->text()));

    ui->tableWidget_D4->setRowCount(count+1);
}


void SystemCenter::on_order_send_clicked()
{
    QMap<QString, QMap<QString, QString>> orders;
    int count = ui->tableWidget_D4->rowCount();
    for(int i = 0; i < count; i++){
        QString w_id = ui->tableWidget_D4->item(i, 0)->text().split("-")[0].trimmed();
        QString c_id = ui->tableWidget_D4->item(i, 1)->text().split("-")[0].trimmed();
        QString quantity = ui->tableWidget_D4->item(i, 2)->text().trimmed();
        QMap<QString, QString> map;
        map.clear();
        map[c_id] = quantity;
        if(orders.contains(w_id)){
            map = orders.value(w_id);
            map.insert(c_id, quantity);
        }
        orders.insert(w_id, map);
    }
    QStringList list;
    list.append("order_send");

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << (quint16) 0;

    out << list;
    out << orders;

    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    m_tcpsocket->write(message);
}
