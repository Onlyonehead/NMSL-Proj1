#include "systemcenter.h"
#include "ui_systemcenter.h"
#include "record.h"

void SystemCenter::sendMessage(QStringList list)
{
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << (quint16) 0;
    out << list;
    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    m_tcpsocket->write(message);
}

void SystemCenter::readMessage()
{
    QDataStream in(m_tcpsocket);
    in.setVersion(QDataStream::Qt_5_7);
    quint16 blocksize = 0;
    if (m_tcpsocket->bytesAvailable() < (int)sizeof(quint16)){
        return;

    }
    in >> blocksize;

    if(m_tcpsocket->bytesAvailable() < blocksize){
        return;
    }


    QString from;
    in >> from;
    qDebug() << "From: " << from << endl;
    if(from == "transfer"){

        ui->progressBar->setValue(80);
        int count1 = 0;
        int count2 = 0;

        QVector<QStringList> stock;
        QVector<QStringList> arriving;
        QVector<QStringList> clothes;
        QVector<QStringList> warehouse;
        QMap<QString,QMap<QString, QString>> stock_map;
        QMap<QString, QMap<QString, QStringList>> arriving_map;
        QMap<QString, QString> warehouse_map;
        QVector<QStringList> stores;



        in >> stock;
        in >> arriving;
        in >> clothes;
        in >> warehouse;
        in >> stock_map;
        in >> arriving_map;
        in >> warehouse_map;
        in >> stores;
        in >> count_dealt;
        in >> count_ongoing;
        in >> count_rejected;

        this->stock = stock;
        this->arriving = arriving;
        this->clothes = clothes;
        this->warehouse = warehouse;
        this->stock_map = stock_map;
        this->arriving_map = arriving_map;
        this->warehouse_map = warehouse_map;
        this->stores = stores;

        ui->label_121->setText(QString::number(count_dealt));
        ui->label_123->setText(QString::number(count_ongoing));
        ui->label_128->setText(QString::number(count_rejected));

        for(QStringList list : stock){
            count1 += list.at(2).toInt();
        }

        ui->progressBar->setValue(85);


        for(QStringList list: arriving){
            count2 += list.at(2).toInt();
        }

        ui->progressBar->setValue(90);

        ui->label_20->setText(QString::number(count1));
        ui->label_27->setText(QString::number(count2));

        QApplication::processEvents();

        ui->label_22->setText(QString::number(clothes.size()));

        ui->progressBar->setValue(100);

        ui->progressBar->setVisible(false);
        ui->pushButton_switch->setEnabled(true);
        ui->pushButton_quit->setEnabled(true);
    }

    if(from == "info_whEC"){

        QStringList wordlist;
        in >> wordlist;
        QApplication::processEvents();
        QCompleter *completer = new QCompleter(this);
        QStringListModel *string_list_model = new QStringListModel(wordlist, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setModel(string_list_model);
        completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                          "background:rgba(255, 255, 255,200);"
                                          "color: rgb(76, 76, 76);"
                                          "	font: 17pt \"Times\" bold;");
        ui->warehouse_search_A->setCompleter(completer);

        ui->progressBar->setValue(55);

        wordlist.clear();
        in >> wordlist;
        completer = new QCompleter(this);
        string_list_model = new QStringListModel(wordlist, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setModel(string_list_model);
        completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                          "background:rgba(255, 255, 255,200);"
                                          "color: rgb(76, 76, 76);"
                                          "	font: 17pt \"Times\" bold;");
        ui->warehouse_search_C->setCompleter(completer);

        ui->progressBar->setValue(60);


        wordlist.clear();
        in >> wordlist;

        completer = new QCompleter(this);
        string_list_model = new QStringListModel(wordlist, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setModel(string_list_model);
        completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                          "background:rgba(255, 255, 255,200);"
                                          "color: rgb(76, 76, 76);"
                                          "	font: 17pt \"Times\" bold;");
        ui->warehouse_search_B->setCompleter(completer);

        ui->progressBar->setValue(65);

        wordlist.clear();
        in >> wordlist;

        completer = new QCompleter(this);
        string_list_model = new QStringListModel(wordlist, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setModel(string_list_model);
        completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                          "background:rgba(255, 255, 255,200);"
                                          "color: rgb(76, 76, 76);"
                                          "	font: 17pt \"Times\" bold;");
        ui->warehouse_search_D->setCompleter(completer);

        ui->progressBar->setValue(70);
    }
    if(from == "isC"){
        ui->tableWidget_C1->setRowCount(0);
        ui->tableWidget_C2->setRowCount(0);

        QString text = ui->warehouse_search_C->text();

        QStringList warehouse;

        QMap<QString, QString> stock;

        QMap<QString, QStringList> arriving;

        QVector<QStringList> clothes = this->clothes;



        in >> warehouse;
        in >> stock;
        in >> arriving;

        int count = 0;
        for(QMap<QString, QString>::const_iterator i = stock.begin(); i != stock.end(); ++i){
            QStringList list;
            for(QStringList l : clothes){
                if(l.at(0) == i.key()){
                    list = l;
                    break;
                }
            }
            QApplication::processEvents();
            ui->tableWidget_C1->insertRow(count);
            ui->tableWidget_C1->setItem(count, 0, new QTableWidgetItem(warehouse.at(1)));
            ui->tableWidget_C1->setItem(count, 1, new QTableWidgetItem(i.key()));
            ui->tableWidget_C1->setItem(count, 2, new QTableWidgetItem(list.at(1)));
            ui->tableWidget_C1->setItem(count, 3, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_C1->setItem(count, 4, new QTableWidgetItem(i.value()));

            QApplication::processEvents();
            count++;
        }

        ui->tableWidget_C1->setRowCount(count);
        ui->tableWidget_C1->setSpan(0, 0, count, 1);


        count = 0;
        for(QMap<QString, QStringList>::const_iterator i = arriving.begin(); i != arriving.end(); ++i){
            QStringList list;
            for(QStringList l : clothes){
                if(l.at(0) == i.key()){
                    list = l;
                    break;
                }
            }
            QApplication::processEvents();
            ui->tableWidget_C2->insertRow(count);
            ui->tableWidget_C2->setItem(count, 0, new QTableWidgetItem(warehouse.at(1)));
            ui->tableWidget_C2->setItem(count, 1, new QTableWidgetItem(i.key()));
            ui->tableWidget_C2->setItem(count, 2, new QTableWidgetItem(list.at(1)));
            ui->tableWidget_C2->setItem(count, 3, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_C2->setItem(count, 4, new QTableWidgetItem(i.value().at(0)));
            QStringList s = i.value().at(1).split(QRegExp("[A-Z]"));
            ui->tableWidget_C2->setItem(count, 5, new QTableWidgetItem(s.at(0) + " " + s.at(1)));

            count++;
            QApplication::processEvents();
        }

        ui->tableWidget_C2->setRowCount(count);
        if(count > 1){
            ui->tableWidget_C2->setSpan(0, 0, count, 1);
        }
    }

    if(from == "pB5"){
        ui->tableWidget_C1->setRowCount(0);
        ui->tableWidget_C2->setRowCount(0);

        QMap<QString, QString> warehouse;

        QMap<QString,QMap<QString, QString>> stock = stock_map;

        QMap<QString, QMap<QString, QStringList>> arriving = arriving_map;

        QVector<QStringList> clothes = this->clothes;

        in >> warehouse;

        int count_i = 0;
        int count_j = 0;

        for (QMap<QString,QMap<QString, QString>>::const_iterator j
             = stock.begin(); j != stock.end(); ++j){
            QApplication::processEvents();
            for(QMap<QString, QString>::const_iterator i = j.value().begin(); i != j.value().end(); ++i){
                QStringList list;
                for(QStringList l : clothes){
                    if(l.at(0) == i.key()){
                        list = l;
                        break;
                    }
                }
                QApplication::processEvents();

                ui->tableWidget_C1->insertRow(count_i);
                ui->tableWidget_C1->setItem(count_i, 0, new QTableWidgetItem(warehouse.find(j.key()).value()));
                ui->tableWidget_C1->setItem(count_i, 1, new QTableWidgetItem(i.key()));
                ui->tableWidget_C1->setItem(count_i, 2, new QTableWidgetItem(list.at(1)));
                QApplication::processEvents();
                ui->tableWidget_C1->setItem(count_i, 3, new QTableWidgetItem(list.at(2)));
                ui->tableWidget_C1->setItem(count_i, 4, new QTableWidgetItem(i.value()));
                count_i++;
                QApplication::processEvents();
            }
            if(j.value().size() > 1){
                //                ui->tableWidget_C1->item(count_i-j.value().size(), 0)->setBackground(QBrush(QColor(255,255,255)));
                ui->tableWidget_C1->setSpan(count_i-j.value().size(), 0, j.value().size(), 1);

            }
        }

        for (QMap<QString,QMap<QString, QStringList>>::const_iterator j
             = arriving.begin(); j != arriving.end(); ++j){
            QApplication::processEvents();
            for(QMap<QString, QStringList>::const_iterator i =
                j.value().begin(); i != j.value().end(); ++i){
                QStringList list;
                for(QStringList l : clothes){
                    if(l.at(0) == i.key()){
                        list = l;
                        break;
                    }
                }
                QApplication::processEvents();
                ui->tableWidget_C2->insertRow(count_j);
                ui->tableWidget_C2->setItem(count_j, 0, new QTableWidgetItem(warehouse.find(j.key()).value()));
                ui->tableWidget_C2->setItem(count_j, 1, new QTableWidgetItem(i.key()));
                ui->tableWidget_C2->setItem(count_j, 2, new QTableWidgetItem(list.at(1)));
                QApplication::processEvents();
                ui->tableWidget_C2->setItem(count_j, 3, new QTableWidgetItem(list.at(2)));
                ui->tableWidget_C2->setItem(count_j, 4, new QTableWidgetItem(i.value().at(0)));
                QStringList s = i.value().at(1).split(QRegExp("[A-Z]"));
                ui->tableWidget_C2->setItem(count_j, 5, new QTableWidgetItem(s.at(0) + " " + s.at(1)));

                QApplication::processEvents();
                count_j++;
            }
            if(j.value().size() > 1){
                //                ui->tableWidget_C2->item(count_i-j.value().size(), 0)->setBackground(QBrush(QColor(255,255,255)));
                ui->tableWidget_C2->setSpan(count_j-j.value().size(), 0, j.value().size(), 1);

            }

        }

        progressBar();
        QApplication::processEvents();
        ui->tableWidget_C1->setRowCount(count_i);
        ui->tableWidget_C2->setRowCount(count_j);
    }
    if(from == "pB8"){
        ui->tableWidget_B->setRowCount(0);

        QStringList list;

        in >> list;

        int n = list.size();

        while(n){
            QApplication::processEvents();
            ui->tableWidget_B->insertRow(list.size()-n);
            ui->tableWidget_B->setItem(list.size()-n, 0, new QTableWidgetItem(list.at(list.size()-n)));
            n--;
        }

        ui->tableWidget_B->setRowCount(list.size());

        progressBar();
    }
    if(from == "tWBiC"){
        QMap<QString, QString> warehouse;
        QVector<QStringList> stock = this->stock;
        QStringList result;
        in >> warehouse;
        in >> result;


        QString id = result.at(0);
        QString style = result.at(1);
        QString size = result.at(2);
        QString path = result.at(3);
        QString price = result.at(4);

        QApplication::processEvents();
        QPixmap *pixmap = new QPixmap(DIR + QString("/clothes/") + path);
        if (pixmap->isNull()){
            download("/clothes/" + path, DIR + QString("/clothes/") + path);
        }

        if (pixmap->isNull()){
            pixmap = new QPixmap(":/default.jpg");
        }
        QApplication::processEvents();
        ui->label_clothes->setScaledContents(true);
        ui->label_clothes->setPixmap(*pixmap);
        delete pixmap;
        QApplication::processEvents();

        ui->label_29->setText(id);
        ui->label_30->setText(style);
        ui->label_31->setText(price);
        ui->label_32->setText(size);
        QApplication::processEvents();

        int quantity_count = 0;

        int i = 0;

        for(QStringList list : stock){
            QApplication::processEvents();
            if(list.at(1) == id){
                ui->tableWidget_B_2->insertRow(i);
                ui->tableWidget_B_2->setItem(i, 0, new QTableWidgetItem(warehouse.find(list.at(0)).value()));
                ui->tableWidget_B_2->setItem(i, 1, new QTableWidgetItem(list.at(2)));
                quantity_count += list.at(2).toInt();
                i++;
            }
        }
        ui->tableWidget_B_2->setRowCount(i);
        ui->label_35->setText(QString::number(quantity_count));
        progressBar_fast();
    }
    if(from == "pB10"){
        ui->tableWidget_D1->setRowCount(0);

        QStringList list;

        in >> list;

        int n = list.size();

        while(n){
            QApplication::processEvents();
            ui->tableWidget_D1->insertRow(list.size()-n);
            ui->tableWidget_D1->setItem(list.size()-n, 0, new QTableWidgetItem(list.at(list.size()-n)));
            n--;
        }

        ui->tableWidget_D1->setRowCount(list.size());

        ui->tableWidget_D2->setRowCount(0);

        list.clear();

        in >> list;

        n = list.size();

        while(n-1){

            //n-1 为了不显示仓库1

            QApplication::processEvents();
            ui->tableWidget_D2->insertRow(list.size()-n);
            ui->tableWidget_D2->setItem(list.size()-n, 0, new QTableWidgetItem(list.at(list.size()-n+1)));
            n--;
        }

        ui->tableWidget_D2->setRowCount(list.size()-1);

        progressBar();
    }
    if(from == "tWD1iC"){
        QStringList result;
        in >> result;


        QString id = result.at(0);
        QString style = result.at(1);
        QString size = result.at(2);
        QString path = result.at(3);
        QString price = result.at(4);

        QApplication::processEvents();
        QPixmap *pixmap = new QPixmap(DIR + QString("/clothes/") + path);
        if (pixmap->isNull()){
            download("/clothes/" + path, DIR + QString("/clothes/") + path);
        }
        if (pixmap->isNull()){
            pixmap = new QPixmap(":/default.jpg");
        }
        QApplication::processEvents();
        ui->label_clothes_D->setScaledContents(true);
        ui->label_clothes_D->setPixmap(*pixmap);
        delete pixmap;
        QApplication::processEvents();

        ui->label_72->setText(id);
        ui->label_73->setText(style);
        ui->label_74->setText(price);
        ui->label_75->setText(size);
        QApplication::processEvents();

        progressBar_fast();
    }

    if(from == "tWD2iC"){
        ui->tableWidget_D3->setRowCount(0);
        QMap<QString, QString> stock;
        in >> stock;

        QMap<QString, QString> clothes;
        in >> clothes;

        QApplication::processEvents();

        int count = 0;
        for(QMap<QString, QString>::const_iterator i = stock.begin(); i != stock.end(); ++i){
            QString clothes_name;
            clothes_name = clothes.value(i.key());
            QApplication::processEvents();
            ui->tableWidget_D3->insertRow(count);
            ui->tableWidget_D3->setItem(count, 0, new QTableWidgetItem(i.key() +
                                                                       " - " + clothes_name));
            ui->tableWidget_D3->setItem(count, 1, new QTableWidgetItem(i.value()));

            QApplication::processEvents();
            count++;
        }

        ui->tableWidget_D3->setRowCount(count);


        progressBar_fast();
    }

    if(from == "order_send"){
        QString msg;
        in >> msg;
        if(msg == "Done"){
            QMessageBox::information(this,"完成", "\n提交订单成功！",QMessageBox::Ok);
            ui->tableWidget_D4->setRowCount(0);
            count_ongoing++;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));

        }
        ui->tableWidget_B->setRowCount(0);
    }

    if(from == "orderinfo"){
        on_pushButton_12_clicked();

        QVector<QStringList> vlist;
        in >> vlist;
        this->orderList = vlist;

        int count = 0;
        for(QStringList l : vlist){
            QApplication::processEvents();
            ui->tableWidget_logistics_A->insertRow(count);
            ui->tableWidget_logistics_A->setItem(count, 0, new QTableWidgetItem("Order id: " + l.at(0)));
            ui->tableWidget_logistics_A->setItem(count, 1, new QTableWidgetItem("Sender: " + l.at(1)));
            QStringList ss = l.at(2).split(QRegExp("[A-Z]"));
            ui->tableWidget_logistics_A->setItem(count, 2, new QTableWidgetItem("Time: " + ss[0] + " " + ss[1]));
            QApplication::processEvents();
            count++;
        }
        ui->tableWidget_logistics_A->setRowCount(count);

        progressBar();
    }

    if(from == "wh_history"){
        ui->tableWidget_A->setRowCount(0);
        QVector<QStringList> result;
        in >> result;
        this->wh_history = result;
        for(int i = result.size()-1; i > -1; i--){
            ui->tableWidget_A->insertRow(result.size()-i-1);

            ui->tableWidget_A->setItem(result.size()-i-1, 0, new QTableWidgetItem("From id: " + result.at(i).at(1)));
            ui->tableWidget_A->setItem(result.size()-i-1, 1, new QTableWidgetItem("To id: " + result.at(i).at(2)));
            QStringList s = result.at(i).at(0).split(QRegExp("[A-Z]"));
            ui->tableWidget_A->setItem(result.size()-i-1, 2, new QTableWidgetItem(s.at(0) + " " + s.at(1)));
        }
        ui->tableWidget_A->setRowCount(result.size());
    }

    if(from == "wh_history_all"){
        ui->tableWidget_A->setRowCount(0);
        QVector<QStringList> result;
        in >> result;
        this->wh_history = result;
        for(int i = result.size()-1; i > -1; i--){
            ui->tableWidget_A->insertRow(result.size()-i-1);
            QStringList s = result.at(i).at(0).split(QRegExp("[A-Z]"));
            ui->tableWidget_A->setItem(result.size()-i-1, 0, new QTableWidgetItem("From id: " + result.at(i).at(1)));
            ui->tableWidget_A->setItem(result.size()-i-1, 1, new QTableWidgetItem("To id: " + result.at(i).at(2)));
            ui->tableWidget_A->setItem(result.size()-i-1, 2, new QTableWidgetItem(s.at(0) + " " + s.at(1)));
        }
        ui->tableWidget_A->setRowCount(result.size());
        progressBar();
    }

    if(from == "tWlAiC"){
        ui->tableWidget_logistics_B->setRowCount(0);
        QStringList list;
        in >> list;

        this->wh_info = list;

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

    if(from == "send_replenishment"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n补货成功！",QMessageBox::Ok);
            on_pushButton_13_clicked();

            count_ongoing--;
            count_dealt++;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));
        }
    }

    if(from == "orderCheckedInfo"){
        on_pushButton_14_clicked();
        QVector<QStringList> vlist;
        in >> vlist;
        this->orderCheckedList = vlist;

        int count = 0;
        for(QStringList l : vlist){
            QApplication::processEvents();
            ui->tableWidget_logistics_2A->insertRow(count);
            ui->tableWidget_logistics_2A->setItem(count, 0, new QTableWidgetItem("Order id: " + l.at(0)));
            ui->tableWidget_logistics_2A->setItem(count, 1, new QTableWidgetItem("Sender: " + l.at(1)));
            QStringList ss = l.at(2).split(QRegExp("[A-Z]"));
            ui->tableWidget_logistics_2A->setItem(count, 2, new QTableWidgetItem("Time: " + ss[0] + " " + ss[1]));
            QApplication::processEvents();
            count++;
        }
        ui->tableWidget_logistics_2A->setRowCount(count);

        progressBar();
    }

    if(from == "del_orderChecked"){
        QString s;
        in >> s;
        if(s == "Done"){
            on_pushButton_15_clicked();
            QMessageBox::information(this,"完成", "\n删除成功！",QMessageBox::Ok);
            orderCheckedId.clear();

            count_dealt--;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));
        }
        if(s == "REJECTED"){
            on_pushButton_15_clicked();
            QMessageBox::information(this,"完成", "\n删除成功！",QMessageBox::Ok);
            orderCheckedId.clear();

            count_rejected--;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));
        }
    }
    if(from == "reject_order"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n已拒绝此次订单！",QMessageBox::Ok);
            order_id.clear();
            on_pushButton_13_clicked();

            count_ongoing--;
            count_rejected++;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));
        }
    }

    if(from == "reject_order_D"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n已拒绝此次订单！",QMessageBox::Ok);
            order_id.clear();
            on_pushButton_26_clicked();

            count_ongoing--;
            count_rejected++;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));
        }
    }

    if(from == "add_warehouse"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n已成功添加！",QMessageBox::Ok);
            QStringList l;
            in >> l;
            l.replace(0, QString::number(warehouse.size() + 1));
            warehouse.append(l);
            warehouse_map.insert(l.at(0), l.at(1));
            ui->warehouse_add_name->clear();
            ui->warehouse_add_province->clear();
            ui->warehouse_add_city->clear();
            ui->warehouse_add_address->clear();
            ui->add_warehouse->setVisible(false);
            ui->pushButton_22->setEnabled(true);
            ui->pushButton_23->setEnabled(true);
            ui->pushButton_24->setEnabled(true);
        }
    }
    if(from == "edit_warehouse"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n已成功修改！",QMessageBox::Ok);
            QStringList l;
            in >> l;
            for(int i = 0; i < warehouse.size(); i++){
                if(l.at(0) == warehouse.at(i).at(0)){
                    warehouse.replace(i, l);
                    break;
                }
            }
            warehouse_map[l.at(0)] = l.at(1);
            ui->warehouse_edit_name->clear();
            ui->warehouse_edit_province->clear();
            ui->warehouse_edit_city->clear();
            ui->warehouse_edit_address->clear();
            on_pushButton_30_clicked();
            on_pushButton_4_clicked();
            ui->pushButton_22->setEnabled(true);
            ui->pushButton_23->setEnabled(true);
            ui->pushButton_24->setEnabled(true);
        }
    }

    if(from == "del_warehouse"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n已成功删除！",QMessageBox::Ok);
            QString id;
            in >> id;
            for(int i = 0; i < warehouse.size(); i++){
                if(id == warehouse.at(i).at(0)){
                    warehouse.remove(i);
                    break;
                }
            }

            warehouse_map.remove(id);
            wh_info_warehouse.clear();
            on_pushButton_4_clicked();
        }
    }

    if(from == "createStore"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n已成功添加！",QMessageBox::Ok);
            on_pushButton_54_clicked();
        }
    }

    if(from == "orderinfo_D"){
        on_pushButton_26_clicked();

        QVector<QStringList> vlist;
        in >> vlist;
        this->orderList = vlist;

        int count = 0;
        for(QStringList l : vlist){
            QApplication::processEvents();
            ui->tableWidget_logistics_D1->insertRow(count);
            ui->tableWidget_logistics_D1->setItem(count, 0, new QTableWidgetItem("Order id: " + l.at(0)));
            ui->tableWidget_logistics_D1->setItem(count, 1, new QTableWidgetItem("Sender: " + l.at(1)));
            QStringList ss = l.at(2).split(QRegExp("[A-Z]"));
            ui->tableWidget_logistics_D1->setItem(count, 2, new QTableWidgetItem("Time: " + ss[0] + " " + ss[1]));
            QApplication::processEvents();
            count++;
        }
        ui->tableWidget_logistics_D1->setRowCount(count);

        progressBar();
    }

    if(from == "auto_replenish"){
        QString s;
        in >> s;
        if(s == "Done"){
            QMessageBox::information(this,"完成", "\n补货成功！",QMessageBox::Ok);
            on_pushButton_31_clicked();

            count_ongoing--;
            count_dealt++;
            ui->label_121->setText(QString::number(count_dealt));
            ui->label_123->setText(QString::number(count_ongoing));
            ui->label_128->setText(QString::number(count_rejected));
        }
    }



    // system page add new garment
    if(from == "sp_confirmAddG"){
        QVector<QStringList> garmentInfo;
        in >> garmentInfo;

        QMessageBox::information(NULL, tr("提示"), tr("新服装已添加完成，已可查看"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        on_clearGarment_clicked();

        for(QStringList l : garmentInfo){
            this->clothes.append(l);
        }
    }
    // system page save picture

    if(from == "sp_sendPic"){
        qDebug() << "save picture success";
    }
    //providerpage show provider info

    if(from == "pp_sp"){
        ui->tableWidget_providerInfo->setRowCount(0);
        int i = 0;
        QVector<QStringList> result;
        in >> result;
        for(QStringList list : result) {
            ui->tableWidget_providerInfo->insertRow(i);
            ui->tableWidget_providerInfo->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_providerInfo->setItem(i, 1, new QTableWidgetItem(list.at(1)));
            ui->tableWidget_providerInfo->setItem(i, 2, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_providerInfo->setItem(i, 3, new QTableWidgetItem(list.at(3)));
//            QTableWidgetItem *item = ui->tableWidget_providerInfo->item(i, 0);
//            item->setFlags(item->flags() & (Qt::ItemIsEditable));
            i++;
        }
        ui->tableWidget_providerInfo->setRowCount(i);
        progressBar();
    } // providerpage hange provider info
    if(from == "pp_cpi"){
        QMessageBox::information(NULL, tr("提示"), tr("供货商信息修改成功！"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        on_pushButton_clearProvider_clicked();
    } // provider page add new provider
    if(from == "pp_api"){
        QMessageBox::information(NULL, tr("提示"), tr("新供货商已添加成功！现在已可查看或下发订单。"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        on_pushButton_addProviderInfo_2_clicked();
    }// personnelpage1 show staff info
    if(from == "pp1_ss"){
        QVector<QStringList> result;
        in >> result;
        int i = 0;
        for(QStringList list : result) {
            ui->tableWidget_showStaffInfo->insertRow(i);
            ui->tableWidget_showStaffInfo->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_showStaffInfo->setItem(i, 1, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_showStaffInfo->setItem(i, 2, new QTableWidgetItem(list.at(3)));
            ui->tableWidget_showStaffInfo->setItem(i, 3, new QTableWidgetItem(list.at(4)));
            ui->tableWidget_showStaffInfo->setItem(i, 4, new QTableWidgetItem(list.at(5)));
            i++;
        }
        ui->tableWidget_showStaffInfo->setRowCount(i);
        progressBar();
    }  //personnel page 1 search staff info multi results
    if(from == "pp1_ssi"){
        QVector<QStringList> result;
        in >> result;
        ui->tableWidget_showStaffInfo->clear();
        QStringList showStaffInfoHeader;
        showStaffInfoHeader << "用户名" << "姓名" << "性别" << "职位" << "邮箱";
        ui->tableWidget_showStaffInfo->setHorizontalHeaderLabels(showStaffInfoHeader);
        ui->tableWidget_showStaffInfo->setAlternatingRowColors(true);
        ui->tableWidget_showStaffInfo->verticalHeader()->setVisible(false);
        int i = 0;
        for(QStringList list : result){
            ui->tableWidget_showStaffInfo->insertRow(i);
            ui->tableWidget_showStaffInfo->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_showStaffInfo->setItem(i, 1, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_showStaffInfo->setItem(i, 2, new QTableWidgetItem(list.at(3)));
            ui->tableWidget_showStaffInfo->setItem(i, 3, new QTableWidgetItem(list.at(4)));
            ui->tableWidget_showStaffInfo->setItem(i, 4, new QTableWidgetItem(list.at(5)));
            i++;
        }
        ui->tableWidget_showStaffInfo->setRowCount(i);
        progressBar();
    } // perspnnel page 1 delete staff info
    if(from == "pp1_dsi"){
        QMessageBox::information(NULL, tr("提示"), tr("删除员工成功！"), QMessageBox::Yes, QMessageBox::Yes);
    } // personnel page 2 ad  neu staff name
    if(from == "pp2_anu"){
        bool isExisted;
        in >> isExisted;
        if(isExisted == true){
            ui->label_newStaffUsernameTip->setVisible(true);
            ui->lineEdit_addNewPassword->setEnabled(false);
            ui->lineEdit_repeatPassword->setEnabled(false);
            ui->lineEdit_addNewName->setEnabled(false);
            ui->lineEdit_addNewEmail->setEnabled(false);
            ui->pushButton_addNewPortrait->setEnabled(false);
            ui->pushButton_confirmNewStaff->setEnabled(false);
        }else {
            ui->label_newStaffUsernameTip->setVisible(false);
            ui->lineEdit_addNewPassword->setEnabled(true);
            ui->lineEdit_repeatPassword->setEnabled(true);
            ui->lineEdit_addNewName->setEnabled(true);
            ui->lineEdit_addNewEmail->setEnabled(true);
            ui->pushButton_addNewPortrait->setEnabled(true);
            ui->pushButton_confirmNewStaff->setEnabled(true);
        }
    }  // personnel page 2 add new email
    if(from == "pp2_ane"){
        bool isExisted;
        in >> isExisted;
        if(isExisted){
            ui->label_newStaffEmailTip->setVisible(true);
            ui->pushButton_addNewPortrait->setEnabled(false);
            ui->pushButton_confirmNewStaff->setEnabled(false);
        }else {
            ui->label_newStaffEmailTip->setVisible(false);
            ui->pushButton_addNewPortrait->setEnabled(true);
            ui->pushButton_confirmNewStaff->setEnabled(true);
        }
    } // personnel page 2 add new portrait
    if(from == "pp2_anp"){
        qDebug() << "add portrait success!";
    }
    // personnel page 2 confirm add new staff
    if(from == "pp2_cns"){
        QMessageBox::information(NULL, tr("提示"), tr("添加新员工成功！现已可查询此员工信息。"),
                                 QMessageBox::Yes , QMessageBox::Yes);
        ui->lineEdit_addNewUsername->clear();
        ui->lineEdit_addNewPassword->clear();
        ui->lineEdit_repeatPassword->clear();
        ui->lineEdit_addNewName->clear();
        ui->lineEdit_addNewEmail->clear();
        ui->label_showNewPortrait->clear();
        ui->label_showNewPortraitPath->clear();
    }// personnel page 4 check if email exists
    if(from == "pp4_ise"){
        bool isEmailExisted;
        in >> isEmailExisted;
        if(!isEmailExisted){
            ui->label_updateEmailTip->setVisible(true);
            ui->lineEdit_updateStaffNewpassword->setEnabled(false);
            ui->lineEdit_updateStaffOldpassword->setEnabled(false);
            ui->lineEdit_updateStaffUsername->setEnabled(false);
            ui->pushButton_changeStaffpassword->setEnabled(false);
        }else {
            ui->label_updateEmailTip->setVisible(false);
            ui->lineEdit_updateStaffOldpassword->setEnabled(true);
            ui->lineEdit_updateStaffNewpassword->setEnabled(true);
            ui->lineEdit_updateStaffUsername->setEnabled(true);
            ui->pushButton_changeStaffpassword->setEnabled(true);
        }
    }// personnel page 4 check if old password right
    if(from == "pp4_cop"){
        bool isPasswordRight;
        in >> isPasswordRight;
        if(!isPasswordRight){
            ui->label_updatePasswordTip->setVisible(true);
            ui->lineEdit_updateStaffNewpassword->setEnabled(false);
            ui->lineEdit_updateStaffUsername->setEnabled(false);
            ui->pushButton_changeStaffpassword->setEnabled(false);
        }else {
            ui->label_updatePasswordTip->setVisible(false);
            ui->lineEdit_updateStaffNewpassword->setEnabled(true);
            ui->lineEdit_updateStaffUsername->setEnabled(true);
            ui->pushButton_changeStaffpassword->setEnabled(true);
        }
    }//personnel page 4 update password & username
    if(from == "pp4_csp"){



        QString newUsername, oldUsername;
        in >> newUsername;
        in >> oldUsername;
        QMessageBox::information(NULL, tr("提示"), tr("用户名和密码已修改。"), QMessageBox::Yes, QMessageBox::Yes);
        if(ui->label_2->text().trimmed() == oldUsername){
            QFile file(DIR + QString("/pwd.data"));
            if (file.exists()){
                file.remove();
            }

            Login *lg = new Login;
            connect(this, SIGNAL(stringReturn(QString)), lg, SLOT(showString(QString)));
            emit stringReturn(newUsername);
            this->close();
        }else{
            on_pushButton_cancelStaffpasswordChange_clicked();
        }

    }// purchase page show garment info
    if(from == "pcp_sg"){
        int i = 0;
        QVector<QStringList> result;
        in >> result;
        for(QStringList list : result) {
            ui->tableWidget_generateOrder->insertRow(i);
            ui->tableWidget_generateOrder->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_generateOrder->setItem(i, 1, new QTableWidgetItem(list.at(1)));
            ui->tableWidget_generateOrder->setItem(i, 2, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_generateOrder->setItem(i, 3, new QTableWidgetItem(list.at(3)));
            ui->tableWidget_generateOrder->setItem(i, 4, new QTableWidgetItem(list.at(4)));
            i++;
        }
        ui->tableWidget_generateOrder->setRowCount(i);
        progressBar();
    }// personnel page 3 show staff
    if(from == "pp3_upss"){
        int i = 0;
        QVector<QStringList> result;
        in >> result;
        for(QStringList list : result){
            ui->tableWidget_updateShowStaffInfo->insertRow(i);
            ui->tableWidget_updateShowStaffInfo->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_updateShowStaffInfo->setItem(i, 1, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_updateShowStaffInfo->setItem(i, 2, new QTableWidgetItem(list.at(3)));
            ui->tableWidget_updateShowStaffInfo->setItem(i, 3, new QTableWidgetItem(list.at(4)));
            ui->tableWidget_updateShowStaffInfo->setItem(i, 4, new QTableWidgetItem(list.at(5)));
            i++;
        }
        ui->tableWidget_updateShowStaffInfo->setRowCount(i);
        progressBar();
    }// personnel page 3 update staff information
    if(from == "pp3_csi"){
        QMessageBox::information(NULL, tr("提示"), tr("用户信息更改成功!"),
                                 QMessageBox::Yes, QMessageBox::Yes);
        on_pushButton_updatePageClearStaff_clicked();
    }// deliver page show provider ids
    if(from == "dp_sp"){
        int i = 0;
        QVector<QStringList> result;
        in >> result;

        for(QStringList list : result){
            ui->tableWidget_deliverProvider->insertRow(i);
            ui->tableWidget_deliverProvider->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_deliverProvider->setItem(i, 1, new QTableWidgetItem(list.at(2)));
            i++;
        }
        ui->tableWidget_deliverProvider->setRowCount(i);
        progressBar();
    }// deliver page show provider detailed information
    if(from == "dp_spdi"){
        QStringList result;
        in >> result;
        ui->label_deliverShowID->setText(result.at(0));
        ui->label_deliverShowAds->setText(result.at(1));
        ui->label_deliverShowName->setText(result.at(2));
        ui->label_deliverShowProduct->setText(result.at(3));
        progressBar();
    }//deliver page deliver order successfully information
    if(from == "dp_do"){
        QMessageBox::information(NULL, tr("提示"), tr("订单分发成功，预计三天后送达至总仓库，现已可查询"),
                                 QMessageBox::Yes, QMessageBox::Yes);
    }


    //sissyVI--Start

    if(from == "showStores"){
        QVector<QStringList> qv_stores;
        in >> qv_stores;

        ui->tableWidget_stores->setRowCount(0);
        qDebug()<<"门店数量："<<qv_stores.size();
        int i=0;
        QVector<QStringList>::const_iterator it;
        for(it=qv_stores.constBegin(); it!=qv_stores.constEnd(); ++it){
            ui->tableWidget_stores->insertRow(i);
            for(int j=0; j<6; ++j){
                ui->tableWidget_stores->setItem(i, j, new QTableWidgetItem(it->at(j)));
            }
            ++i;
        }
        ui->tableWidget_stores->setRowCount(qv_stores.size());

        progressBar();
    }

    if(from == "storesClicked"){
        int record_size;
        int qv_size;//获取QVector的大小
        QString id_trans;
        QString id_store;
        QString date;
        QString prices;
        QMap<QString, QString> m;
        in >> record_size;
        in >> qv_size;

        ui->tableWidget_storeRecord->clear();
        ui->tableWidget_storeRecord->setRowCount(record_size);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(0, 80); //设置列的宽度
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(1, 230);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(2, 100);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(3, 115);
        ui->tableWidget_storeRecord->horizontalHeader()->setStretchLastSection(true);


        int i=0;
        for(int num=0; num<qv_size; ++num){
            in >> id_trans >> id_store >> date >> prices >> m;

            QMap<QString, QString>::iterator it2;

            ui->tableWidget_storeRecord->setItem(i,0,new QTableWidgetItem(id_trans)); //id_trans
            QStringList sIndex = date.split("T");
            ui->tableWidget_storeRecord->setItem(i,1,new QTableWidgetItem(sIndex.at(0)+" "+sIndex.at(1))); //date
            ui->tableWidget_storeRecord->setItem(i,2,new QTableWidgetItem(prices)); //prices

            if(m.size()>1){
                ui->tableWidget_storeRecord->setSpan(i, 0, m.size(), 1);
                ui->tableWidget_storeRecord->setSpan(i, 1, m.size(), 1);
                ui->tableWidget_storeRecord->setSpan(i, 2, m.size(), 1);
            }

            for(it2=m.begin(); it2!=m.end(); ++it2){
                QApplication::processEvents();

                QString styleS;
                QString idC = it2.key();
                QVector<QStringList>::const_iterator itC;
                for(itC=clothes.constBegin(); itC!=clothes.constEnd(); ++itC){
                    if(itC->at(0)==idC){
                        styleS = itC->at(1)+" "+itC->at(2);
                        break;
                    }
                }

                ui->tableWidget_storeRecord->setItem(i,3,new QTableWidgetItem(styleS)); //style
                ui->tableWidget_storeRecord->setItem(i,4,new QTableWidgetItem(it2.value())); //amount
                ++i;
            }
        }

        progressBar();
    }

    if(from == "getAllRequests"){
        in >> qv_requests;

        ui->tableWidget_check->verticalHeader()->setVisible(false); //设置表垂直头不可见
        ui->tableWidget_check->setRowCount(qv_requests.size());//设置行数，与公司所有私服种数相同
        ui->tableWidget_check->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(0, 70); //设置列的宽度
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(1, 70);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(2, 260);
        ui->pushButton_change->setVisible(false);
        ui->pushButton_commit->setVisible(false);
        ui->pushButton_reject->setVisible(false);

        int i=0;
        QVector<QStringList>::const_iterator it;
        for(it=qv_requests.constBegin(); it!=qv_requests.constEnd(); ++it){
            ui->tableWidget_check->setItem(i, 0, new QTableWidgetItem(it->at(0)));
            ui->tableWidget_check->setItem(i, 1, new QTableWidgetItem(it->at(1)));
            QStringList sIndex = it->at(2).split("T");
            ui->tableWidget_check->setItem(i, 2, new QTableWidgetItem(sIndex.at(0)+" "+sIndex.at(1)));
            ++i;
        }

        progressBar();
    }

    if(from == "getCheckDetail"){
        QString store_id;
        QVector<QStringList> qv;//请求详细信息

        in >> store_id >>  qv;

        QVector<QStringList>::const_iterator its;
        for(its=stores.constBegin(); its!=stores.constEnd(); ++its){
            if(its->at(0)==store_id){
                ui->label_storeN->setText(its->at(1));
                ui->label_manager->setText(its->at(5));
                QString location;
                if(its->at(3)=="")
                    location = its->at(2)+"市";
                else
                    location = its->at(2)+"省"+its->at(3)+"市";
                ui->label_location->setText(location);
            }
        }

        ui->tableWidget_checkDetail->verticalHeader()->setVisible(false);
        ui->tableWidget_checkDetail->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑,但是不会像设置Enable那样使界面变灰
        ui->tableWidget_checkDetail->setRowCount(qv.size());//设置行数，与搜索结果size相同
        ui->tableWidget_checkDetail->setSelectionBehavior(QAbstractItemView::SelectRows);


        int i=0;
        QVector<QStringList>::const_iterator it;
        for(it=qv.constBegin(); it!=qv.constEnd(); ++it){

            ui->tableWidget_checkDetail->setItem(i,0,new QTableWidgetItem(it->at(0)));

            QVector<QStringList>::const_iterator itc;
            for(itc=clothes.constBegin(); itc!=clothes.constEnd(); ++itc){
                if(itc->at(0)==it->at(0)){
                    ui->tableWidget_checkDetail->setItem(i,1,new QTableWidgetItem(itc->at(1)));
                    ui->tableWidget_checkDetail->setItem(i,2,new QTableWidgetItem(itc->at(2)));
                }
            }

            ui->tableWidget_checkDetail->setItem(i,3,new QTableWidgetItem(it->at(1)));
            ui->tableWidget_checkDetail->setItem(i,4,new QTableWidgetItem(it->at(2)));


            ++i;
        }

        ui->pushButton_commit->setVisible(true);
        ui->pushButton_reject->setVisible(true);

        progressBar();
    }

    if(from == "changeAmount"){
        QString amount;
        in >> amount;
        ui->tableWidget_checkDetail->item(ui->label_sell_row->text().toInt(), 4)->setText(amount);

        progressBar();
    }

    if(from == "commitRequest"){
        QString s;
        in >> s;
        QMessageBox::information(this,"completed", "\nrequest approved successfully!",QMessageBox::Ok);

        count_ongoing++;
        ui->label_121->setText(QString::number(count_dealt));
        ui->label_123->setText(QString::number(count_ongoing));
        ui->label_128->setText(QString::number(count_rejected));

        ui->pushButton_change->setVisible(false);
        ui->pushButton_commit->setVisible(false);
        ui->pushButton_reject->setVisible(false);
        ui->lineEdit_sell_amount->setText("");
        ui->tableWidget_checkDetail->setRowCount(0);
        ui->label_storeN->setText("");
        ui->label_manager->setText("");
        ui->label_location->setText("");

        //从表中删去已处理请求
        for(int i=0; i<ui->tableWidget_check->rowCount(); ++i){
            if(ui->label_sell_idPurchase->text()==ui->tableWidget_check->item(i, 0)->text()){
                ui->tableWidget_check->removeRow(i);
                break;
            }
        }

        progressBar();
    }

    if(from == "requestReject"){
        QString s;
        in >> s;
        QMessageBox::information(this,"completed", "\nrequest rejected successfully!",QMessageBox::Ok);

        ui->pushButton_change->setVisible(false);
        ui->pushButton_commit->setVisible(false);
        ui->pushButton_reject->setVisible(false);
        ui->lineEdit_sell_amount->setText("");
        ui->tableWidget_checkDetail->setRowCount(0);
        ui->label_storeN->setText("");
        ui->label_manager->setText("");
        ui->label_location->setText("");

        //从表中删去已处理请求
        for(int i=0; i<ui->tableWidget_check->rowCount(); ++i){
            if(ui->label_sell_idPurchase->text()==ui->tableWidget_check->item(i, 0)->text()){
                ui->tableWidget_check->removeRow(i);
                break;
            }
        }

        progressBar();
    }

    if(from == "getArriveRecord"){

        QVector<QStringList> qv;
        in >> qv;
        ui->tw_sell_C2->setRowCount(qv.size());

        int i=0;
        QVector<QStringList>::const_iterator ita;
        for(ita=qv.constBegin(); ita!=qv.constEnd(); ++ita, ++i){
            //id, time, state
            ui->tw_sell_C2->setItem(i, 0, new QTableWidgetItem(ita->at(0)));
            QStringList sIndex = ita->at(2).split("T");
            ui->tw_sell_C2->setItem(i, 1, new QTableWidgetItem(sIndex.at(0)+" "+sIndex.at(1)));

            QString state;
            if(ita->at(1)=="1")
                state = "Checked";
            else
                state = "Rejected";
            ui->tw_sell_C2->setItem(i, 2, new QTableWidgetItem(state));
        }

        progressBar();
    }

    if(from == "getArriveDetail"){
        QMap<QString, QVector<QStringList> > qm;
        QMap<QString, QString> qmt;
        int size;
        in >> size >> qm >> qmt;

        ui->tw_sell_C3->clear();
        ui->tw_sell_C3->verticalHeader()->setVisible(false);
        ui->tw_sell_C3->setRowCount(size);
        ui->tw_sell_C3->setEditTriggers(QAbstractItemView::NoEditTriggers);

        //470
        ui->tw_sell_C3->horizontalHeader()->resizeSection(0, 100);
        ui->tw_sell_C3->horizontalHeader()->resizeSection(1, 220);
        ui->tw_sell_C3->horizontalHeader()->resizeSection(2, 90);
        ui->tw_sell_C3->horizontalHeader()->resizeSection(3, 60);

        int i=0;
        QMap<QString, QVector<QStringList> >::const_iterator ita;
        for(ita=qm.constBegin(); ita!=qm.constEnd(); ++ita){
            QString from_id = ita.key();
            ui->tw_sell_C3->setItem(i, 0, new QTableWidgetItem(warehouse_map.value(from_id)));

            QStringList sIndex = qmt.value(from_id).split("T");
            ui->tw_sell_C3->setItem(i, 1, new QTableWidgetItem(sIndex.at(0)+" "+sIndex.at(1)));

            int height = ita.value().size();
            if(height>1){
                ui->tw_sell_C3->setSpan(i, 0, height, 1);
                ui->tw_sell_C3->setSpan(i, 1, height, 1);
            }

            QVector<QStringList>::const_iterator its;
            for(its=ita.value().constBegin(); its!=ita.value().constEnd(); ++its, ++i){
                QString clothes_id = its->at(0);
                QVector<QStringList>::const_iterator itc;
                for(itc=clothes.constBegin(); itc!=clothes.constEnd(); ++itc){
                    if(itc->at(0)==clothes_id){
                        ui->tw_sell_C3->setItem(i, 2, new QTableWidgetItem(itc->at(1)+" "+itc->at(2)));
                        break;
                    }
                }


                ui->tw_sell_C3->setItem(i, 3, new QTableWidgetItem(its->at(1)));
            }
        }

        progressBar();
    }

    if(from == "changeUserName"){
        QStringList users, users2;
        in >> users;
        for(int i=0; i<users.size(); ++i){
            if(users.at(i)!=ui->label_2->text()){
                users2.append("                   " + users.at(i));
            }
        }
        ui->comboBox_sellDUserName->addItems(users2);

        progressBar();
    }

    if(from == "changeUserName2"){
        QStringList users, users2;
        in >> users;
        for(int i=0; i<users.size(); ++i){
            if(users.at(i)!=ui->label_2->text()){
                users2.append("                   " + users.at(i));
            }
        }
        ui->comboBox_2->addItems(users2);

        progressBar();
    }

    if(from == "storeInfoChange"){
        QMessageBox::information(this,"completed", "\nstore infomation changed successfully!",QMessageBox::Ok);

        this->on_pushButton_50_clicked();

        QStringList qsl;
        qsl.append("reloadStores");//更新商店信息
        sendMessage(qsl);

        progressBar();
    }

    if(from == "reloadStores"){
        in >> stores;
    }

    //sissyVI--Finish

    //    m_tcpsocket->disconnectFromHost();
}
