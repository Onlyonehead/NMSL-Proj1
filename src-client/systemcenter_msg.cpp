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
        int count1 = 0;
        int count2 = 0;

        QVector<QStringList> stock;
        QVector<QStringList> arriving;
        QVector<QStringList> clothes;

        in >> stock;
        in >> arriving;
        in >> clothes;

        for(QStringList list : stock){
            count1 += list.at(2).toInt();
        }


        for(QStringList list: arriving){
            count2 += list.at(2).toInt();
        }

        ui->label_20->setText(QString::number(count1));
        ui->label_27->setText(QString::number(count2));

        QApplication::processEvents();

        ui->label_22->setText(QString::number(clothes.size()));


        progressBar_fast();

        ui->pushButton_switch->setEnabled(true);
        ui->pushButton_quit->setEnabled(true);
    }
    if(from == "info_pB4"){
        QVector<QStringList> result;
        in >> result;
        int i = 0;
        for(QStringList list : result){
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(list.at(1)));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(list.at(2)));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(list.at(3)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(list.at(4)));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(list.at(5)));
            i++;
        }
        ui->tableWidget->setRowCount(i);
        progressBar();
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
    }

    if(from == "info_isA"){
        ui->tableWidget->setRowCount(0);
        QString text = ui->warehouse_search_A->text();
        QVector<QStringList> result;
        in >> result;
        int i = 0;
        for(QStringList list: result){
            qDebug() << list.at(0) << endl;
            if(list.at(0) == text || list.at(1) == text ||
                    list.at(2) == text || list.at(3) == text ||
                    list.at(4) == text || list.at(5) == text) {
                ui->tableWidget->insertRow(i);
                ui->tableWidget->setItem(i, 0, new QTableWidgetItem(list.at(0)));
                ui->tableWidget->setItem(i, 1, new QTableWidgetItem(list.at(1)));
                ui->tableWidget->setItem(i, 2, new QTableWidgetItem(list.at(2)));
                ui->tableWidget->setItem(i, 3, new QTableWidgetItem(list.at(3)));
                ui->tableWidget->setItem(i, 4, new QTableWidgetItem(list.at(4)));
                ui->tableWidget->setItem(i, 5, new QTableWidgetItem(list.at(5)));
                i++;
            }
        }
        ui->tableWidget->setRowCount(i);
    }

    if(from == "isC"){
        ui->tableWidget_C1->setRowCount(0);
        ui->tableWidget_C2->setRowCount(0);

        QString text = ui->warehouse_search_C->text();

        QStringList warehouse;

        QMap<QString, QString> stock;

        QMap<QString, QStringList> arriving;

        QVector<QStringList> clothes;



        in >> warehouse;
        in >> stock;
        in >> arriving;
        in >> clothes;

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

        QMap<QString,QMap<QString, QString>> stock;

        QMap<QString, QMap<QString, QStringList>> arriving;

        QVector<QStringList> clothes;

        in >> warehouse;
        in >> stock;
        in >> arriving;
        in >> clothes;

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
        QVector<QStringList> stock;
        QStringList result;
        in >> warehouse;
        in >> stock;
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
    if(from == "isB"){
        ui->tableWidget_B->setRowCount(0);;
        QString text = ui->warehouse_search_B->text();

        QVector<QStringList> result;

        in >> result;


        int i = 0;
        for(QStringList list : result){
            if(list.at(0) == text || list.at(1) == text){
                ui->tableWidget_B->insertRow(i);
                ui->tableWidget_B->setItem(i, 0, new QTableWidgetItem(list.at(0) + " - " + list.at(1)));
                i++;
                QApplication::processEvents();
            }
        }
        ui->tableWidget_B->setRowCount(i);
    }

//    m_tcpsocket->disconnectFromHost();
}
