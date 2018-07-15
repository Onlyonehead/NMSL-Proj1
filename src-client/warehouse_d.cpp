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
    ui->tableWidget_D3->setRowCount(0);
    ui->tableWidget_D4->setRowCount(0);
    QPixmap *pixmap = new QPixmap(":/default.jpg");
    QApplication::processEvents();
    ui->label_clothes_D->setScaledContents(true);
    ui->label_clothes_D->setPixmap(*pixmap);

    delete pixmap;

    ui->label_72->clear();
    ui->label_73->clear();
    ui->label_74->clear();
    ui->label_75->clear();
    ui->warehouse_label_D->clear();
    ui->quantity_D->clear();

    QApplication::processEvents();
}

void SystemCenter::on_tableWidget_D1_itemClicked(QTableWidgetItem *item){

    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

    QStringList msg;
    msg.append("tWD1iC");
    msg.append(s);
    sendMessage(msg);

}

void SystemCenter::on_tableWidget_D2_itemClicked(QTableWidgetItem *item){

    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

    ui->warehouse_label_D->setText(item->text().split(QRegExp("[-:]"))[3].trimmed());

    QStringList msg;
    msg.append("tWD2iC");
    msg.append(s);
    sendMessage(msg);

}


void SystemCenter::on_clothes_ADD_clicked()
{

    QString quantity = ui->quantity_D->text();
    if(quantity.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入数量！",QMessageBox::Close);
        return;
    }
    QByteArray ba = quantity.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        QMessageBox::warning(this,"警告", "\n请输入纯数字！",QMessageBox::Close);
        return;
    }

    if(!ui->tableWidget_D2->currentItem() || !ui->tableWidget_D1->currentItem()){
        QMessageBox::warning(this,"警告", "\n请选中仓库和货物！",QMessageBox::Close);
        return;
    }

    int count = ui->tableWidget_D4->rowCount();
    QString s1 = ui->tableWidget_D1->currentItem()->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            ui->tableWidget_D1->currentItem()->text().split(QRegExp("[-:]"))[3].trimmed();
    QString s2 = ui->tableWidget_D2->currentItem()->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            ui->tableWidget_D2->currentItem()->text().split(QRegExp("[-:]"))[3].trimmed();
    for(int i = 0; i < count; i++){
        if(ui->tableWidget_D4->item(i, 0)->text().trimmed() == s1 &&
                ui->tableWidget_D4->item(i, 1)->text().trimmed() == s2){
            ui->tableWidget_D4->item(i, 2)->setText(
                        QString::number(quantity.toInt() +
                        ui->tableWidget_D4->item(i, 2)->text().toInt()));
            return ;
        }

    }
    ui->tableWidget_D4->insertRow(count);

    ui->tableWidget_D4->setItem(count, 0, new QTableWidgetItem(s1));

    ui->tableWidget_D4->setItem(count, 1, new QTableWidgetItem(s2));

    ui->tableWidget_D4->setItem(count, 2, new QTableWidgetItem(ui->quantity_D->text()));

    ui->tableWidget_D4->setRowCount(count+1);
}


void SystemCenter::on_order_send_clicked()
{
    if(ui->tableWidget_D4->rowCount() == 0){
        QMessageBox::warning(this,"警告", "\n请添加订单！",QMessageBox::Close);
        return;
    }
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

void SystemCenter::on_icon_search_D_clicked()
{
    ui->tableWidget_D1->setRowCount(0);;
    QString text = ui->warehouse_search_D->text();

    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }

    QVector<QStringList> result = this->clothes;

    int i = 0;
    for(QStringList list : result){
        if(list.at(0) == text || list.at(1) == text){
            ui->tableWidget_D1->insertRow(i);
            ui->tableWidget_D1->setItem(i, 0, new QTableWidgetItem(list.at(0) + " - " + list.at(1)));
            i++;
            QApplication::processEvents();
        }
    }
    ui->tableWidget_D1->setRowCount(i);

    result = this->warehouse;
    i = 0;
    for(QStringList list : result){
        if(list.at(0) == text || list.at(1) == text){
            ui->tableWidget_D2->insertRow(i);
            ui->tableWidget_D2->setItem(i, 0, new QTableWidgetItem(list.at(0) + " - " + list.at(1)));
            i++;
            QApplication::processEvents();
        }
    }
    ui->tableWidget_D2->setRowCount(i);
}
