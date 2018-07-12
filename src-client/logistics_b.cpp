#include "systemcenter.h"
#include "ui_systemcenter.h"



void SystemCenter::on_pushButton_15_clicked()
{
    QStringList msg;
    msg.append("orderCheckedInfo");
    sendMessage(msg);
}

void SystemCenter::on_pushButton_14_clicked()
{
    orderCheckedId.clear();
    ui->tableWidget_logistics_2A->setRowCount(0);
    ui->pushButton_16->setVisible(true);
    ui->pushButton_17->setVisible(false);
    ui->pushButton_18->setVisible(false);
}

void SystemCenter::on_pushButton_16_clicked()
{
    ui->pushButton_16->setVisible(false);
    ui->pushButton_17->setVisible(true);
    ui->pushButton_18->setVisible(true);
}

void SystemCenter::on_pushButton_17_clicked() // confirm
{
    ui->pushButton_16->setVisible(true);
    ui->pushButton_17->setVisible(false);
    ui->pushButton_18->setVisible(false);

    if(orderCheckedId.isEmpty()){
        QMessageBox::information(this,"警告", "请选择要删除的条目",QMessageBox::Ok);
        return ;
    }

    QStringList msg;
    msg.append("del_orderChecked");
    msg.append(orderCheckedId);
    sendMessage(msg);

}

void SystemCenter::on_pushButton_18_clicked()  //cancel
{
    ui->pushButton_16->setVisible(true);
    ui->pushButton_17->setVisible(false);
    ui->pushButton_18->setVisible(false);
}

void SystemCenter::on_tableWidget_logistics_2A_itemClicked(QTableWidgetItem *item){
    orderCheckedId.clear();
    QString s;

    QVector<QStringList> vlist;
    vlist = this->orderCheckedList;
    QStringList order;
    QString wh;

    orderCheckedId = ui->tableWidget_logistics_2A->item(item->row(), 0)->
            text().split(":")[1].trimmed();

    for(QStringList l : vlist){
        if(l.at(0) == ui->tableWidget_logistics_2A->item(item->row(), 0)->
                text().split(":")[1].trimmed()){
            order = l.at(3).split("#");
            QByteArray ba = l.at(1).toLatin1();
            const char *s = ba.data();

            if(*s == 'S'){
                for(QStringList ll : stores){
                    if("S" + ll.at(0) == l.at(1)){
                        wh += l.at(1) + " - " + ll.at(1);
                        break;
                    }
                }
            }else{
                wh += l.at(1) + " - " + warehouse_map.find(l.at(1)).value();
            }

            break;
        }
    }

    s += "\n";
    s += ui->tableWidget_logistics_2A->item(item->row(), 0)->text();
    s += "\n";
    s += "\n";
    s += ui->tableWidget_logistics_2A->item(item->row(), 2)->text();
    s += "\n";
    s += "\n";
    s += "Sender: " + wh;
    s += "\n\n";
    s += "----------------------";
    s += "\n\n";

    if(order.at(0) == "REJECTED"){
        s += "\n\nREJECTED";
    }else{
        int n = order.size();
        QMap<QString, QMap<QString, QString>> order_map;
        while(n){
            QMap<QString, QString> map;
            map = order_map.value(order.at(n-3));
            map.insert(order.at(n-2), order.at(n-1));
            order_map[order.at(n-3)] = map;
            n -= 3;
        }
        for(QMap<QString, QMap<QString, QString>>::const_iterator i = order_map.begin(); i != order_map.end(); ++i){
            s += "From:  " + i.key() + " - " + warehouse_map.find(i.key()).value() + "\n";
            for(QMap<QString, QString>::const_iterator j = i.value().begin(); j != i.value().end(); ++j){
                QString s_clothes;
                for(QStringList l : clothes){
                    if(l.at(0) == j.key()){
                        s_clothes += j.key() + " - " + l.at(1);
                        break;
                    }
                }
                s += s_clothes + " : " + j.value() + "\n";
            }
            s += "\n";
        }
    }

    QMessageBox::information(this,"历史", s,QMessageBox::Ok);

}
