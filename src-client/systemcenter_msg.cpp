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
    m_tcpsocket->flush();
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
        qDebug() << "Transfer Done" << endl;
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

        QVector<QMap<QString, QString>> stock;

        QVector<QMap<QString, QStringList>> arriving;

        QVector<QStringList> clothes;

        in >> warehouse;
        in >> stock;
        in >> arriving;
        in >> clothes;

        int count_i = 0;
        int count_j = 0;

        for (QMap<QString,QString> map : stock){
            QApplication::processEvents();
            for(QMap<QString, QString>::const_iterator i = map.begin(); i != map.end(); ++i){
                QStringList list;
                for(QStringList l : clothes){
                    if(l.at(0) == i.key()){
                        list = l;
                        break;
                    }
                }
                QApplication::processEvents();

                ui->tableWidget_C1->insertRow(count_i);
                ui->tableWidget_C1->setItem(count_i, 0, new QTableWidgetItem(warehouse.find(i.key()).value()));
                ui->tableWidget_C1->setItem(count_i, 1, new QTableWidgetItem(i.key()));
                ui->tableWidget_C1->setItem(count_i, 2, new QTableWidgetItem(list.at(1)));
                QApplication::processEvents();
                ui->tableWidget_C1->setItem(count_i, 3, new QTableWidgetItem(list.at(2)));
                ui->tableWidget_C1->setItem(count_i, 4, new QTableWidgetItem(i.value()));
                count_i++;
                QApplication::processEvents();
            }
            if(stock.size() > 1){
                ui->tableWidget_C1->setSpan(count_i-stock.size(), 0, stock.size(), 1);
            }
        }

        for (QMap<QString,QStringList> map : arriving){
            QApplication::processEvents();
            for(QMap<QString, QStringList>::const_iterator i = map.begin(); i != map.end(); ++i){
                QStringList list;
                for(QStringList l : clothes){
                    if(l.at(0) == i.key()){
                        list = l;
                        break;
                    }
                }
                QApplication::processEvents();
                ui->tableWidget_C2->insertRow(count_j);
                ui->tableWidget_C2->setItem(count_j, 0, new QTableWidgetItem(warehouse.find(i.key()).value()));
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
            if(arriving.size() > 1){
                ui->tableWidget_C2->setSpan(count_j-arriving.size(), 0, arriving.size(), 1);
            }

        }

        progressBar_fast();
        QApplication::processEvents();
        ui->tableWidget_C1->setRowCount(count_i);
        ui->tableWidget_C2->setRowCount(count_j);
    }
    if(from == "iwhC"){

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
    if(from == "info_whEC3"){
        QStringList wordlist;
        in >> wordlist;

        QCompleter *completer = new QCompleter(this);
        QStringListModel *string_list_model = new QStringListModel(wordlist, this);
        completer->setCaseSensitivity(Qt::CaseInsensitive);
        completer->setModel(string_list_model);
        completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                          "background:rgba(255, 255, 255,200);"
                                          "color: rgb(76, 76, 76);"
                                          "	font: 17pt \"Times\" bold;");
        ui->warehouse_search_B->setCompleter(completer);
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
    }



//    m_tcpsocket->disconnectFromHost();
}
