#include "systemcenter.h"
#include "ui_systemcenter.h"

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

        ui->progressBar->setValue(70);
        int count1 = 0;
        int count2 = 0;

        QVector<QStringList> stock;
        QVector<QStringList> arriving;
        QVector<QStringList> clothes;
        QVector<QStringList> warehouse;
        QMap<QString,QMap<QString, QString>> stock_map;
        QMap<QString, QMap<QString, QStringList>> arriving_map;

        in >> stock;
        in >> arriving;
        in >> clothes;
        in >> warehouse;
        in >> stock_map;
        in >> arriving_map;

        this->stock = stock;
        this->arriving = arriving;
        this->clothes = clothes;
        this->warehouse = warehouse;
        this->stock_map = stock_map;
        this->arriving_map = arriving_map;

        for(QStringList list : stock){
            count1 += list.at(2).toInt();
        }

        ui->progressBar->setValue(80);


        for(QStringList list: arriving){
            count2 += list.at(2).toInt();
        }

        ui->progressBar->setValue(90);

        ui->label_20->setText(QString::number(count1));
        ui->label_27->setText(QString::number(count2));

        QApplication::processEvents();

        ui->label_22->setText(QString::number(clothes.size()));

        ui->progressBar->setValue(100);

        ui->pushButton_switch->setEnabled(true);
        ui->pushButton_quit->setEnabled(true);
    }

    if(from == "info_whEC"){
        ui->progressBar->setRange(0, 100);

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

        ui->progressBar->setValue(10);

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

        ui->progressBar->setValue(20);


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

        ui->progressBar->setValue(30);

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

        ui->progressBar->setValue(40);
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
                ui->tableWidget_C2->setSpan(count_j-j.value().size(), 0, j.value().size(), 1);
            }

        }

        progressBar_fast();
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

        progressBar_fast();
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
        QPixmap *pixmap = new QPixmap("./" + path);
        if(pixmap->isNull()){
            download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
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

        while(n){
            QApplication::processEvents();
            ui->tableWidget_D2->insertRow(list.size()-n);
            ui->tableWidget_D2->setItem(list.size()-n, 0, new QTableWidgetItem(list.at(list.size()-n)));
            n--;
        }

        ui->tableWidget_D2->setRowCount(list.size());

        progressBar_fast();
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
        QPixmap *pixmap = new QPixmap("./" + path);
        if(pixmap->isNull()){
            download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
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
            ui->tableWidget_D3->setItem(count, 0, new QTableWidgetItem(i.key() + " - " + clothes_name));
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
        }
    }
    if(from == "wh_history"){
        ui->tableWidget_A->setRowCount(0);
        QVector<QStringList> result;
        in >> result;
        for(int i = result.size()-1; i > -1; i--){
            ui->tableWidget_A->insertRow(result.size()-i-1);
            QStringList s = result.at(i).at(0).split(QRegExp("[A-Z]"));
            ui->tableWidget_A->setItem(result.size()-i-1, 0, new QTableWidgetItem(s.at(0) + " " + s.at(1) + "\n  "
                                                                  + "from id " + result.at(i).at(1) + " -> "
                                                                  + "to id " + result.at(i).at(2) + "\n\n" +
                                                                  result.at(i).at(3)));
        }
        ui->tableWidget_A->setRowCount(result.size());
    }

    if(from == "wh_history_all"){
        ui->tableWidget_A->setRowCount(0);
        QVector<QStringList> result;
        in >> result;
        for(int i = result.size()-1; i > -1; i--){
            ui->tableWidget_A->insertRow(result.size()-i-1);
            QStringList s = result.at(i).at(0).split(QRegExp("[A-Z]"));
            ui->tableWidget_A->setItem(result.size()-i-1, 0, new QTableWidgetItem(s.at(0) + " " + s.at(1) + "\n   "
                                                                  + "from id " + result.at(i).at(1) + " -> "
                                                                  + "to id " + result.at(i).at(2) + "\n\n" +
                                                                  result.at(i).at(3)));
        }
        ui->tableWidget_A->setRowCount(result.size());
    }

//    m_tcpsocket->disconnectFromHost();
}
