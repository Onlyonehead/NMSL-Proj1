#include "systemcenter.h"
#include "ui_systemcenter.h"

void SystemCenter::on_pushButton_31_clicked()
{
    QStringList msg;
    msg.append("orderinfo_D");
    sendMessage(msg);
}

void SystemCenter::on_pushButton_26_clicked()
{
    url_num = 0;
    progress_num = 0;
    ui->tableWidget_logistics_D1->setRowCount(0);
    ui->tableWidget_logistics_D4->setRowCount(0);
    ui->tableWidget_logistics_D2->setRowCount(0);
    ui->logistics_label_B_2->clear();
    wh_id.clear();
    order_id.clear();
    replenishment.clear();
    wh_info.clear();
    order_time.clear();
}

void SystemCenter::on_pushButton_32_clicked()
{
    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "Confirm to reject this order ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        QStringList msg;
        msg.append("reject_order_D");
        msg.append(order_id);
        sendMessage(msg);
    }
}

void SystemCenter::on_tableWidget_logistics_D1_itemClicked(QTableWidgetItem *item){

    url_num = 0;
    progress_num = 0;
    replenishment.clear();
    wh_id.clear();
    order_id.clear();
    order_time.clear();
    ui->tableWidget_logistics_D4->setRowCount(0);
    ui->tableWidget_logistics_D2->setRowCount(0);
    QVector<QStringList> vlist;
    vlist = this->orderList;
    QStringList order;
    QString wh;



    order_time = ui->tableWidget_logistics_D1->item(item->row(), 2)->
            text().split(":")[1].trimmed() + ":" + ui->tableWidget_logistics_D1->item(item->row(), 2)->
            text().split(":")[2].trimmed() + ":" + ui->tableWidget_logistics_D1->item(item->row(), 2)->
            text().split(":")[3].trimmed();

    order_id = ui->tableWidget_logistics_D1->item(item->row(), 0)->
            text().split(":")[1].trimmed();


    for(QStringList l : vlist){
        if(l.at(0) == ui->tableWidget_logistics_D1->item(item->row(), 0)->
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

    ui->logistics_label_B_2->setText(wh);


    int n = order.size();
    while(n){
        QString s_clothes;
        ui->tableWidget_logistics_D4->insertRow((order.size() - n) / 2);
        for(QStringList l : clothes){
            if(l.at(0) == order.at(n-2)){
                s_clothes += order.at(n-2) + " - " + l.at(1);
                break;
            }
        }
        ui->tableWidget_logistics_D4->setItem((order.size() - n) / 2, 0, new QTableWidgetItem(s_clothes));
        ui->tableWidget_logistics_D4->setItem((order.size() - n) / 2, 1, new QTableWidgetItem(order.at(n-1)));
        n -= 2;
    }
    ui->tableWidget_logistics_D4->setRowCount(order.size() / 2);

}

void SystemCenter::on_logistics_showmap_clicked()
{

    if(ui->tableWidget_logistics_D2->currentItem() == NULL){
        QMessageBox::warning(this,"警告", "请选中条目",QMessageBox::Ok);
        return ;
    }

    if(ui->tableWidget_logistics_D2->item(
                ui->tableWidget_logistics_D2->currentItem()->row(), 0)
            == NULL){
        QMessageBox::warning(this,"警告", "请选中一个仓库",QMessageBox::Ok);
        return ;
    }

    if(ui->tableWidget_logistics_D2->item(
                ui->tableWidget_logistics_D2->currentItem()->row(), 0)
            ->text() == "--------"){
        QMessageBox::warning(this,"警告", "请选中一个仓库",QMessageBox::Ok);
        return ;
    }

    QtMap *qtMap = new QtMap("http://39.108.155.50/project1/src/auto_route.html");
    connect(this, SIGNAL(webReturn(QVector<QStringList>)),
            qtMap, SLOT(webInit(QVector<QStringList>)));
    QVector<QStringList> sites;

    QString from = ui->tableWidget_logistics_D2->item(
                ui->tableWidget_logistics_D2->currentItem()->row(), 0)
            ->text().trimmed();
    QString to_id =  ui->logistics_label_B_2->text().split("-")[0].trimmed();

    for(QStringList l : warehouse){
        if(l.at(1) == from){
            sites.append(l);
            break;
        }
    }

    QByteArray ba = to_id.toLatin1();
    const char *s = ba.data();

    if(*s == 'S'){
        for(QStringList l : stores){
            if("S" + l.at(0) == to_id){
                sites.append(l);
                break;
            }
        }
    }else{
        for(QStringList l : warehouse){
            if(l.at(0) == to_id){
                sites.append(l);
                break;
            }
        }
    }

    emit webReturn(sites);

    qtMap->exec();
}


void SystemCenter::on_logistics_send_D_clicked()
{
    if(ui->tableWidget_logistics_D2->rowCount() < 2){
        QMessageBox::warning(this," 警告", "\n请先计算路线",QMessageBox::Close);
        return ;
    }
    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "Confirm to send this replenishment ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        QStringList list;
        list.append("auto_replenish");

        QByteArray message;
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out << (quint16) 0;

        out << list;
        out << order_id;
        out << ui->logistics_label_B_2->text();
        out << replenishment;
        out << order_time;

        out.device()->seek(0);
        out << (quint16) (message.size() - sizeof(quint16));
        m_tcpsocket->write(message);
    }
}

void SystemCenter::on_logistics_route_D_clicked()
{
    if(ui->tableWidget_logistics_D1->currentItem() == NULL){
        QMessageBox::warning(this," 警告", "\n未选中任何订单",QMessageBox::Close);
        return ;
    }

    ui->tableWidget_logistics_D1->setEnabled(false);

    QNetworkAccessManager *m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlotForAuto(QNetworkReply*)));
    QUrl url;
    QNetworkRequest request;

    QString id = ui->logistics_label_B_2->text().split("-")[0].trimmed();

    QString destination;

    QByteArray ba = id.toLatin1();
    const char *s = ba.data();

    if(*s == 'S'){
        for(QStringList ll : stores){
            if("S" + ll.at(0) == id){
                destination = ll.at(6) + "," + ll.at(7);
                break;
            }
        }
    }else{
        for(QStringList ll : warehouse){
            if(ll.at(0) == id){
                destination = ll.at(6) + "," + ll.at(7);
                break;
            }
        }
    }


    QStringList urls;

    for(QStringList l : warehouse){
        if(l.at(0) != id){
            urls.append("https://restapi.amap.com/v3/direction/driving?origin="
                        + l.at(6) + "," + l.at(7) +
                        "&destination="
                        + destination +
                        "&key=be6f38b0c3801dd73bcba0e07165b068");
        }
    }

    auto_route.clear();
    url_num = urls.size();
    progress_num = url_num;


    for(int i = 0; i < url_num; i++){
        url = QUrl(urls[i]);

        request.setUrl(url);
        m_accessManager->get(request);
    }

    for(QStringList l : this->orderList){

        if(l.at(0) == ui->tableWidget_logistics_D1->item(
                    ui->tableWidget_logistics_D1->currentItem()->row(), 0)->
                text().split(":")[1].trimmed()){
            current_order = l.at(3).split("#");
            break;
        }
    }
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);

}

void SystemCenter::finishedSlotForAuto(QNetworkReply* reply){
    bool flag = false;
    if (reply->error() == QNetworkReply::NoError){
        QByteArray ba = reply->readAll();
            QJsonParseError jsonpe;
            QJsonDocument json = QJsonDocument::fromJson(ba, &jsonpe);
            if (jsonpe.error == QJsonParseError::NoError){
                if (json.isObject()){
                    QJsonObject obj = json.object();
                    if (obj.contains("error")){
                        qDebug() << "error:" << obj["error"];
                    }else{
                        QJsonObject o = obj.value("route").toObject();

                        QString origin = o.value("origin").toString();
                        QString destination = o.value("destination").toString();

                        QJsonArray jarray = o.value("paths").toArray();


                        QString distance = jarray[0].toObject().value("distance").toString();
                        QString duration = jarray[0].toObject().value("duration").toString();
                        QStringList list;
                        list.append(origin);
                        list.append(distance);

                        url_num--;

                        ui->progressBar->setValue(100 - url_num * 100 / progress_num);
                        if(ui->progressBar->value() == 100){
                            ui->progressBar->setVisible(false);
                        }

                        if(!(distance == "" || duration == "")){
                            auto_route.insert(duration.toInt(), list);
                        }

                        if(url_num == 0){
                            generateNewRoute();
                            ui->tableWidget_logistics_D1->setEnabled(true);
                        }

                        flag = true;
                    }
                }else{
                    qDebug() << "error, should be json object";
                }
            }else{
                qDebug() << "error:" << jsonpe.errorString();
            }
    }else{
        qDebug() << "error:" << reply->errorString();
    }
    if(!flag){
        QMessageBox::warning(this," 警告", "\n计算失败",QMessageBox::Close);
        return ;
    }
}

void SystemCenter::generateNewRoute(){

    QMap<int, QStringList> map;
    for (QMap<int, QStringList>::const_iterator i
         = auto_route.begin(); i != auto_route.end(); ++i){
        for(QStringList l : warehouse){
            if(l.at(6) == i.value().at(0).split(",")[0].trimmed() &&
                    l.at(7) == i.value().at(0).split(",")[1].trimmed()){
                QStringList tmp;
                tmp.append(l.at(0) + "-" + l.at(1));
                tmp.append(i.value().at(1));
                map.insert(i.key(), tmp);
            }
        }
    }

    QMap<QString, int> order;

    int n = current_order.size();
    while(n){
        order.insert(current_order.at(n-2), current_order.at(n-1).toInt());
        n -= 2;
    }

//    qDebug() << map;
//    qDebug() << "Order:  " << order;


    QMap<QString, QString> clothes;

    for(QStringList l : this->clothes){
        clothes.insert(l.at(0), l.at(1));
    }

    int count = 0;

    for (QMap<int, QStringList>::const_iterator i
         = map.begin(); i != map.end();){

        int flag = count;

        QMap<QString, QString> stock;
        stock = this->stock_map.value(i.value().at(0).split("-")[0].trimmed());

        ui->tableWidget_logistics_D2->insertRow(flag);

        count++;

        int clothes_count = 0;

        QMap<QString, QString> m; // clothes

        for (QMap<QString, int>::const_iterator j
             = order.begin(); j != order.end(); ++j){

            if(!stock.contains(j.key())){
                continue;
            }
            if(stock.value(j.key()).toInt() >= j.value()){

                int clothes_num;
                clothes_count += j.value();
                if(clothes_count > 2000){
                    clothes_num = 2000 - clothes_count + j.value();
                    clothes_count = 2000;
                }else{
                    clothes_num = j.value();
                }


                ui->tableWidget_logistics_D2->insertRow(count);
                ui->tableWidget_logistics_D2->setItem(count, 1, new QTableWidgetItem("ID: " + j.key()));
                ui->tableWidget_logistics_D2->setItem(count, 2, new QTableWidgetItem("Style: " +
                                                                                     clothes.value(j.key())));
                ui->tableWidget_logistics_D2->setItem(count, 3, new QTableWidgetItem("Quantity:"));
                ui->tableWidget_logistics_D2->setItem(count, 4, new QTableWidgetItem(
                                                          QString::number(clothes_num)));



                count++;
                m.insert(j.key(), QString::number(clothes_num));



                if(clothes_count == 2000){
                    if(j.value() - clothes_num == 0){
                        order.remove(j.key());
                    }else{
                        order[j.key()] = j.value() - clothes_num;
                    }
                    break;
                }else{
                    order.remove(j.key());
                }


            }else{


                int clothes_num;
                clothes_count += stock.value(j.key()).toInt();
                if(clothes_count > 2000){
                    clothes_num = 2000 - clothes_count + stock.value(j.key()).toInt();
                    clothes_count = 2000;
                }else{
                    clothes_num = stock.value(j.key()).toInt();
                }

                ui->tableWidget_logistics_D2->insertRow(count);
                ui->tableWidget_logistics_D2->setItem(count, 1, new QTableWidgetItem("ID: " + j.key()));
                ui->tableWidget_logistics_D2->setItem(count, 2, new QTableWidgetItem("Style: " +
                                                                                     clothes.value(j.key())));
                ui->tableWidget_logistics_D2->setItem(count, 3, new QTableWidgetItem("Quantity:"));
                ui->tableWidget_logistics_D2->setItem(count, 4, new QTableWidgetItem(
                                                          QString::number(clothes_num)));

                count++;
                m.insert(j.key(), QString::number(clothes_num));
                order[j.key()] = j.value() - clothes_num;
                if(clothes_count == 2000){
                    break;
                }
            }

        }

        if(m.isEmpty()){
            ui->tableWidget_logistics_D2->removeRow(flag);
            count--;
            ++i;
            continue;
        }

        if(replenishment.contains(i.value().at(0).split("-")[0].trimmed())){
            QMap<QString, QString> mm;
            mm = replenishment.value(i.value().at(0).split("-")[0].trimmed());
            for (QMap<QString, QString>::const_iterator q
                 = m.begin(); q != m.end(); ++q){
                if(mm.contains(q.key())){
                    mm[q.key()] = QString::number(mm.value(q.key()).toInt() + q.value().toInt());
                }else{
                    mm.insert(q.key(), q.value());
                }
            }
            replenishment[i.value().at(0).split("-")[0].trimmed()] = mm;

        }else{
            m.insert("duration", QString::number(i.key()));
            replenishment.insert(i.value().at(0).split("-")[0].trimmed(), m);
        }


        ui->tableWidget_logistics_D2->insertRow(count);
        ui->tableWidget_logistics_D2->setItem(count, 3, new QTableWidgetItem("* Total:"));
        ui->tableWidget_logistics_D2->setItem(count, 4, new QTableWidgetItem(QString::number(clothes_count)));
        count++;

        ui->tableWidget_logistics_D2->insertRow(count);
        ui->tableWidget_logistics_D2->setItem(count, 0, new QTableWidgetItem("--------"));
        ui->tableWidget_logistics_D2->item(count,0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_logistics_D2->setItem(count, 1, new QTableWidgetItem("--------"));
        ui->tableWidget_logistics_D2->item(count,1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_logistics_D2->setItem(count, 2, new QTableWidgetItem("--------"));
        ui->tableWidget_logistics_D2->item(count,2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_logistics_D2->setItem(count, 3, new QTableWidgetItem("--------"));
        ui->tableWidget_logistics_D2->item(count,3)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget_logistics_D2->setItem(count, 4, new QTableWidgetItem("--------"));
        ui->tableWidget_logistics_D2->item(count,4)->setTextAlignment(Qt::AlignCenter);
        count++;

        QString car_type = "";
        double oil_consumed = 0;

        if(clothes_count < 200){
            car_type = "微型货车";
            oil_consumed = 5 + 2 * clothes_count / 100;
        }else if(clothes_count < 500){
            car_type = "轻型货车";
            oil_consumed = 10 + 1.5 * clothes_count / 100;
        }else if(clothes_count < 1000){
            car_type = "中型货车";
            oil_consumed = 20 + 1.2 * clothes_count / 100;
        }else if(clothes_count <= 2000){
            car_type = "重型货车";
            oil_consumed = 10 + clothes_count / 100;
        }

        ui->tableWidget_logistics_D2->setItem(flag, 0, new QTableWidgetItem(
                                                  i.value().at(0).split("-")[1].trimmed()));
        ui->tableWidget_logistics_D2->setItem(flag, 1, new QTableWidgetItem(car_type));
        ui->tableWidget_logistics_D2->setItem(flag, 2, new QTableWidgetItem(
                                                  QString::number(i.value().at(1).toInt() / 1000) + "km"));
        ui->tableWidget_logistics_D2->setItem(flag, 3, new QTableWidgetItem(
                                                  QString::number(i.key() / 3600) + "h " +
                                                  QString::number((i.key() % 3600) / 60) + "min"));
        ui->tableWidget_logistics_D2->setItem(flag, 4, new QTableWidgetItem(
                                                  QString::number(oil_consumed, 10, 2) + "L"));

        if(order.isEmpty()){
            ui->tableWidget_logistics_D2->setRowCount(count);
            break;
        }
        if(clothes_count != 2000){
            ++i;
        }


    }
//    qDebug() <<  replenishment;
}
