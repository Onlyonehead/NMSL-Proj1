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
        ui->tableWidget_B->setRowCount(0);
    } //systempage show garment info
    if(from == "sp_sg"){
        QVector<QStringList> result;
        in >> result;
        int i = 0;
        for(QStringList list : result){
            ui->tableWidget_garmentInfo->insertRow(i);
            ui->tableWidget_garmentInfo->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget_garmentInfo->setItem(i, 1, new QTableWidgetItem(list.at(1)));
            ui->tableWidget_garmentInfo->setItem(i, 2, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_garmentInfo->setItem(i, 3, new QTableWidgetItem(list.at(3)));
            ui->tableWidget_garmentInfo->setItem(i, 4, new QTableWidgetItem(list.at(4)));
            i++;
        }
        ui->tableWidget_garmentInfo->setRowCount(i);
        progressBar();
    } //providerpage show provider info
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
            QTableWidgetItem *item = ui->tableWidget_providerInfo->item(i, 0);
            item->setFlags(item->flags() & (Qt::ItemIsEditable));
            i++;
        }
        ui->tableWidget_providerInfo->setRowCount(i);
        progressBar();
    } // providerpage hange provider info
    if(from == "pp_cpi"){
        qDebug() << "Change information successfully";
    } // personnelpage1 show staff info
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
        qDebug() << "Delete staff infomation successfully";
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
    } //personnel page 2 check password and repeatpassword
    if(from == "pp2_rp"){
        bool isSame;
        in >> isSame;
        if(!isSame){
            ui->label_repeatPasswordTip->setVisible(true);
            ui->lineEdit_addNewName->setEnabled(false);
            ui->lineEdit_addNewEmail->setEnabled(false);
            ui->pushButton_addNewPortrait->setEnabled(false);
            ui->pushButton_confirmNewStaff->setEnabled(false);
        }else {
            ui->label_repeatPasswordTip->setVisible(false);
            ui->lineEdit_addNewName->setEnabled(true);
            ui->lineEdit_addNewEmail->setEnabled(true);
            ui->pushButton_addNewPortrait->setEnabled(true);
            ui->pushButton_confirmNewStaff->setEnabled(true);
        }
    } // personnel page 2 add new email
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
    } // purchase page show garment info
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
    } // purchase page show garment detailed information 没了？？？
    if(from == "pcp_sgdi"){
        QStringList result;
        in >> result;
        QString path = result.at(3);
        QApplication::processEvents();
        QPixmap *pixmap = new QPixmap("./" + path);
        if(pixmap->isNull()){
            download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
        }

        if (pixmap->isNull()){
            pixmap = new QPixmap(":/default.jpg");
        }
        QApplication::processEvents();
        ui->label_purchaseShowPic->setScaledContents(true);
        ui->label_purchaseShowPic->setPixmap(*pixmap);
        delete pixmap;
        QApplication::processEvents();
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



    //sissyVI--Start

    if(from == "showStores"){
        QVector<QStringList> qv_stores;
        in >> qv_stores;

        qDebug()<<"门店数量："<<qv_stores.size();
        ui->tableWidget_stores->setRowCount(qv_stores.size());
        int i=0;
        QVector<QStringList>::const_iterator it;
        for(it=qv_stores.constBegin(); it!=qv_stores.constEnd(); ++it){
            for(int j=0; j<6; ++j){
                ui->tableWidget_stores->setItem(i, j, new QTableWidgetItem(it->at(j)));
            }
            ++i;
        }
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
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(0, 115); //设置列的宽度
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(1, 230);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(2, 115);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(3, 115);
        ui->tableWidget_storeRecord->horizontalHeader()->resizeSection(4, 115);

        int i=0;
        for(int num=0; num<qv_size; ++num){
            in >> id_trans >> id_store >> date >> prices >> m;

            QMap<QString, QString>::iterator it2;

            ui->tableWidget_storeRecord->setItem(i,0,new QTableWidgetItem(id_trans)); //id_trans
            ui->tableWidget_storeRecord->setItem(i,1,new QTableWidgetItem(date)); //date
            ui->tableWidget_storeRecord->setItem(i,2,new QTableWidgetItem(prices)); //prices

            if(m.size()>1){
                ui->tableWidget_storeRecord->setSpan(i, 0, m.size(), 1);
                ui->tableWidget_storeRecord->setSpan(i, 1, m.size(), 1);
                ui->tableWidget_storeRecord->setSpan(i, 2, m.size(), 1);
            }

            for(it2=m.begin(); it2!=m.end(); ++it2){
                QApplication::processEvents();
                ui->tableWidget_storeRecord->setItem(i,3,new QTableWidgetItem(it2.key())); //style
                ui->tableWidget_storeRecord->setItem(i,4,new QTableWidgetItem(it2.value())); //amount
                ++i;
            }
        }
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

        int i=0;
        QVector<QStringList>::const_iterator it;
        for(it=qv_requests.constBegin(); it!=qv_requests.constEnd(); ++it){
            ui->tableWidget_check->setItem(i, 0, new QTableWidgetItem(it->at(0)));
            ui->tableWidget_check->setItem(i, 1, new QTableWidgetItem(it->at(1)));
            ui->tableWidget_check->setItem(i, 2, new QTableWidgetItem(it->at(2)));
            ++i;
        }
    }

    if(from == "getCheckDetail"){
        QStringList qsl_s;
        QVector<QStringList> qv;
        in >> qsl_s >> qv;

        qDebug()<<qv.size();

        ui->label_storeN->setText(qsl_s.at(0));
        ui->label_manager->setText(qsl_s.at(1));
        ui->label_location->setText(qsl_s.at(2));

        ui->tableWidget_checkDetail->verticalHeader()->setVisible(false);
        ui->tableWidget_checkDetail->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑,但是不会像设置Enable那样使界面变灰
        ui->tableWidget_checkDetail->setRowCount(qv.size());//设置行数，与搜索结果size相同
        ui->tableWidget_checkDetail->setSelectionBehavior(QAbstractItemView::SelectRows);


        int i=0;
        QVector<QStringList>::const_iterator it;
        for(it=qv.constBegin(); it!=qv.constEnd(); ++it){
            for(int j=0; j<5; ++j){
                ui->tableWidget_checkDetail->setItem(i,j,new QTableWidgetItem(it->at(j)));
            }
            ++i;
        }
    }

    if(from == "changeAmount"){
        QString amount;
        in >> amount;
        ui->tableWidget_checkDetail->item(ui->label_sell_row->text().toInt(), 4)->setText(amount);
    }

    //sissyVI--Finish

    //    m_tcpsocket->disconnectFromHost();
}
