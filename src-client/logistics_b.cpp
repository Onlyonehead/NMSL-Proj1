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
    ui->tableWidget_logistics_2A->setRowCount(0);
}

void SystemCenter::on_pushButton_16_clicked()
{
    ui->pushButton_16->setVisible(false);
    ui->pushButton_17->setVisible(true);
}

void SystemCenter::on_pushButton_17_clicked()
{
    ui->pushButton_16->setVisible(true);
    ui->pushButton_17->setVisible(false);
}


void SystemCenter::on_tableWidget_logistics_2A_itemClicked(QTableWidgetItem *item){
    QString s;

    QVector<QStringList> vlist;
    vlist = this->orderCheckedList;
    QStringList order;
    QString wh;
    order_id = ui->tableWidget_logistics_2A->item(item->row(), 0)->
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
                for(QStringList ll : warehouse){
                    if(ll.at(0) == l.at(1)){
                        wh += ll.at(0) + " - " + ll.at(1);
                        break;
                    }
                }
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
    s += "\n";
    s += "\n";

//    int n = order.size();
//    while(n){
//        QString s_clothes;
//        ui->tableWidget_logistics_D->insertRow((order.size() - n) / 2);
//        for(QStringList l : clothes){
//            if(l.at(0) == order.at(n-2)){
//                s_clothes += order.at(n-2) + " - " + l.at(1);
//                break;
//            }
//        }
//        ui->tableWidget_logistics_D->setItem((order.size() - n) / 2, 0, new QTableWidgetItem(s_clothes));
//        ui->tableWidget_logistics_D->setItem((order.size() - n) / 2, 1, new QTableWidgetItem("0"));
//        ui->tableWidget_logistics_D->setItem((order.size() - n) / 2, 2, new QTableWidgetItem("of:  " +order.at(n-1)));
//        n -= 2;
//    }

//    for(QStringList l : wh_history){
//        QStringList temp = l.at(0).split(QRegExp("[A-Z]"));
//        if(l.at(1) == ui->tableWidget_A->item(item->row(), 0)->text().split(":")[1].trimmed() &&
//                l.at(2) == ui->tableWidget_A->item(item->row(), 1)->text().split(":")[1].trimmed() &&
//                temp.at(0) + " " + temp.at(1)
//                == ui->tableWidget_A->item(item->row(), 2)->text()){
//            s += l.at(3);
//            break;
//        }
//    }
    QMessageBox::information(this,"历史", s,QMessageBox::Ok);

}
