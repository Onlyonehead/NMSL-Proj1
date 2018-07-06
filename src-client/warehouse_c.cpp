#include "systemcenter.h"
#include "sqltool.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


/**
 * on_pushButton_7_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_7_clicked()
{
    ui->warehouse_search_C->clear();
    ui->tableWidget_C1->setRowCount(0);
    ui->tableWidget_C2->setRowCount(0);
}

/**
 * on_icon_search_C_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_icon_search_C_clicked()
{
    ui->tableWidget_C1->setRowCount(0);
    ui->tableWidget_C2->setRowCount(0);

    QString text = ui->warehouse_search_C->text();
    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }
    QApplication::processEvents();
    QSqlQuery query;
    SQLTool::search(query, "warehouse","name", text);
    int id;
    QApplication::processEvents();
    if(!query.next()){
        id = text.toInt();
    }else{
        id = query.value(0).toInt();
    }

    QStringList warehouse;
    Warehouse::info(id, warehouse);

    QMap<QString, QString> stock;
    Warehouse::stock(id, stock);

    QMap<QString, QStringList> arriving;
    Warehouse::arriving(id, arriving);

    int count = 0;
    for(QMap<QString, QString>::const_iterator i = stock.begin(); i != stock.end(); ++i){
        QStringList clothes;
        Garment::Info(i.key().toInt(), clothes);
        QApplication::processEvents();
        ui->tableWidget_C1->insertRow(count);
        ui->tableWidget_C1->setItem(count, 0, new QTableWidgetItem(warehouse.at(1)));
        ui->tableWidget_C1->setItem(count, 1, new QTableWidgetItem(i.key()));
        ui->tableWidget_C1->setItem(count, 2, new QTableWidgetItem(clothes.at(1)));
        ui->tableWidget_C1->setItem(count, 3, new QTableWidgetItem(clothes.at(2)));
        ui->tableWidget_C1->setItem(count, 4, new QTableWidgetItem(i.value()));

        QApplication::processEvents();
        count++;
    }

    ui->tableWidget_C1->setRowCount(count);
    ui->tableWidget_C1->setSpan(0, 0, count, 1);


    count = 0;
    for(QMap<QString, QStringList>::const_iterator i = arriving.begin(); i != arriving.end(); ++i){
        QStringList clothes;
        Garment::Info(i.key().toInt(), clothes);
        QApplication::processEvents();
        ui->tableWidget_C2->insertRow(count);
        ui->tableWidget_C2->setItem(count, 0, new QTableWidgetItem(warehouse.at(1)));
        ui->tableWidget_C2->setItem(count, 1, new QTableWidgetItem(i.key()));
        ui->tableWidget_C2->setItem(count, 2, new QTableWidgetItem(clothes.at(1)));
        ui->tableWidget_C2->setItem(count, 3, new QTableWidgetItem(clothes.at(2)));
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


/**
 * furry search init
 *
 * @author Zicun Hang
 */
void SystemCenter::warehouseEditComplete2(){
    QStringList wordlist;
    QSqlQuery query;
    QApplication::processEvents();
    SQLTool::search(query, "warehouse");
    QApplication::processEvents();
    while(query.next()){
        wordlist << query.value(0).toString() << query.value(1).toString();
        QApplication::processEvents();
    }
    Tool::QStringList_removeDuplicates(&wordlist);
    QCompleter *completer = new QCompleter(this);
    QStringListModel *string_list_model = new QStringListModel(wordlist, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(string_list_model);
    completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                      "background:rgba(255, 255, 255,200);"
                                      "color: rgb(76, 76, 76);"
                                      "	font: 17pt \"Times\" bold;");
    ui->warehouse_search_C->setCompleter(completer);
}

/**
 * on_pushButton_5_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_5_clicked()
{
    ui->tableWidget_C1->setRowCount(0);
    ui->tableWidget_C2->setRowCount(0);
    QApplication::processEvents();
    QString text = ui->warehouse_search_C->text();
    QSqlQuery query;
    QApplication::processEvents();
    SQLTool::search(query, "warehouse","name", text);
    QApplication::processEvents();
    int id;
    if(!query.next()){
        id = text.toInt();
    }else{
        id = query.value(0).toInt();
    }

    QApplication::processEvents();
    QVector<QStringList> warehouse;
    Warehouse::info(warehouse);
    int n_warehouse = warehouse.size();


    int count_i = 0;
    int count_j = 0;
    while(n_warehouse){
        QApplication::processEvents();
        QMap<QString, QString> stock;
        Warehouse::stock(warehouse.at(warehouse.size()-n_warehouse).at(0).toInt(), stock);
        QApplication::processEvents();
        int n = stock.size();
        for(QMap<QString, QString>::const_iterator i = stock.begin(); i != stock.end(); ++i){
            QStringList clothes;
            QApplication::processEvents();
            Garment::Info(i.key().toInt(), clothes);
            ui->tableWidget_C1->insertRow(count_i);
            ui->tableWidget_C1->setItem(count_i, 0, new QTableWidgetItem(warehouse.at(warehouse.size()-n_warehouse).at(1)));
            ui->tableWidget_C1->setItem(count_i, 1, new QTableWidgetItem(i.key()));
            ui->tableWidget_C1->setItem(count_i, 2, new QTableWidgetItem(clothes.at(1)));
            QApplication::processEvents();
            ui->tableWidget_C1->setItem(count_i, 3, new QTableWidgetItem(clothes.at(2)));
            ui->tableWidget_C1->setItem(count_i, 4, new QTableWidgetItem(i.value()));
            count_i++;
            QApplication::processEvents();
        }
        if(stock.size() > 1){
            ui->tableWidget_C1->setSpan(count_i-stock.size(), 0, stock.size(), 1);
        }

        QApplication::processEvents();

        QMap<QString, QStringList> arriving;
        Warehouse::arriving(warehouse.at(warehouse.size()-n_warehouse).at(0).toInt(), arriving);
        QApplication::processEvents();
        n = arriving.size();
        for(QMap<QString, QStringList>::const_iterator i = arriving.begin(); i != arriving.end(); ++i){
            QStringList clothes;
            Garment::Info(i.key().toInt(), clothes);
            QApplication::processEvents();
            ui->tableWidget_C2->insertRow(count_j);
            ui->tableWidget_C2->setItem(count_j, 0, new QTableWidgetItem(warehouse.at(warehouse.size()-n_warehouse).at(1)));
            ui->tableWidget_C2->setItem(count_j, 1, new QTableWidgetItem(i.key()));
            ui->tableWidget_C2->setItem(count_j, 2, new QTableWidgetItem(clothes.at(1)));
            QApplication::processEvents();
            ui->tableWidget_C2->setItem(count_j, 3, new QTableWidgetItem(clothes.at(2)));
            ui->tableWidget_C2->setItem(count_j, 4, new QTableWidgetItem(i.value().at(0)));
            QStringList s = i.value().at(1).split(QRegExp("[A-Z]"));
            ui->tableWidget_C2->setItem(count_j, 5, new QTableWidgetItem(s.at(0) + " " + s.at(1)));

            QApplication::processEvents();
            count_j++;
        }
        if(arriving.size() > 1){
            ui->tableWidget_C2->setSpan(count_j-arriving.size(), 0, arriving.size(), 1);
        }

        n_warehouse--;
    }


//    while(n_stock){
//        QStringList list = stock.at(stock.size() - n_stock);
//        int n = list.size();

//        QApplication::processEvents();
//        while(n-1){
//            QStringList clothes;
//            Garment::Info(list.at(n-2).toInt(), clothes);
//            ui->tableWidget_C1->insertRow(i);
//            ui->tableWidget_C1->setItem(i, 0, new QTableWidgetItem(list.at(0)));
//            ui->tableWidget_C1->setItem(i, 1, new QTableWidgetItem(list.at(n-2)));
//            ui->tableWidget_C1->setItem(i, 2, new QTableWidgetItem(clothes.at(1)));
//            ui->tableWidget_C1->setItem(i, 3, new QTableWidgetItem(clothes.at(2)));
//            ui->tableWidget_C1->setItem(i, 4, new QTableWidgetItem(list.at(n-1)));
//            QApplication::processEvents();
//            n -= 2;
//            i++;
//        }
//        ui->tableWidget_C1->setSpan(i-(list.size()-1)/2, 0, (list.size()-1)/2, 1);
//        n_stock--;
//        QApplication::processEvents();
//    }

//    while(n_arriving){
//        QStringList list = arriving.at(n_arriving-1);
//        int n = list.size();

//        QApplication::processEvents();
//        while(n-1){
//            QStringList clothes;
//            Garment::Info(list.at(n-3).toInt(), clothes);
//            QApplication::processEvents();
//            ui->tableWidget_C2->insertRow(j);
//            ui->tableWidget_C2->setItem(j, 0, new QTableWidgetItem(list.at(0)));
//            ui->tableWidget_C2->setItem(j, 1, new QTableWidgetItem(list.at(n-3)));
//            ui->tableWidget_C2->setItem(j, 2, new QTableWidgetItem(clothes.at(1)));
//            QApplication::processEvents();
//            ui->tableWidget_C2->setItem(j, 3, new QTableWidgetItem(clothes.at(2)));
//            ui->tableWidget_C2->setItem(j, 4, new QTableWidgetItem(list.at(n-2)));
//            ui->tableWidget_C2->setItem(j, 5, new QTableWidgetItem(list.at(n-1)));
//            QApplication::processEvents();
//            n -= 3;
//            j++;
//        }
//        QApplication::processEvents();
//        ui->tableWidget_C2->setSpan(j-(list.size()-1)/3, 0, (list.size()-1)/3, 1);
//        n_arriving--;
//    }


    progressBar();
    QApplication::processEvents();
    ui->tableWidget_C1->setRowCount(count_i);
    ui->tableWidget_C2->setRowCount(count_j);
}

/**
 * warehouse C information init
 *
 * @author Zicun Hang
 */
void SystemCenter::init_warehouse_C(){
    QApplication::processEvents();
    QSqlQuery query;

    QApplication::processEvents();

    int count1 = 0;
    int count2 = 0;

    SQLTool::search(query, "quantity", "stock");
    while(query.next()){
        count1 += query.value(0).toInt();
    }

    SQLTool::search(query, "quantity", "arriving");
    while(query.next()){
        count2 += query.value(0).toInt();
    }

    ui->label_20->setText(QString::number(count1));
    ui->label_27->setText(QString::number(count2));

    QApplication::processEvents();
    SQLTool::search(query, "clothes");
    ui->label_22->setText(QString::number(query.size()));
}

/**
 * transfer arriving clothes to stock
 *
 * @author Zicun Hang
 */
void SystemCenter::transfer(){
    QApplication::processEvents();
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString till_time = current_date_time.addSecs(300).toString("yyyy-MM-dd hh:mm:ss");

    QSqlQuery query, query2;
    QApplication::processEvents();


    SQLTool::search(query, "arriving");
    while(query.next()){
        QApplication::processEvents();

        QString arrive_date = query.value(3).toString();

        QStringList s = arrive_date.split(QRegExp("[-A-Z:]"));
        int year = s[0].toInt();
        int month = s[1].toInt();
        int day = s[2].toInt();
        int hour = s[3].toInt();
        int minute = s[4].toInt();
        int second = s[5].toInt();
        QApplication::processEvents();
        QTime time;
        time.setHMS(hour,minute,second);
        QDate date;
        date.setDate(year, month, day);
        QDateTime arrive_datetime;
        arrive_datetime.setDate(date);
        arrive_datetime.setTime(time);

        QApplication::processEvents();
        if(arrive_datetime < current_date_time){
            QString warehouse_id = query.value(0).toString();
            QString clothes_id = query.value(1).toString();
            QApplication::processEvents();
            int quantity = query.value(2).toInt();
            QStringList list;
            list.append("warehouse_id");
            list.append(warehouse_id);
            list.append("clothes_id");
            list.append(clothes_id);
            QApplication::processEvents();
            SQLTool::search(query2, "quantity", "stock", list);
            if(query2.next()){
                int stock = query2.value(0).toInt();
                SQLTool::update("stock", "quantity",
                                QString::number(stock + quantity), list);
                SQLTool::del("arriving", list);
            }else{
                qDebug() << "Update arriving failed!" << endl;
            }
            QApplication::processEvents();

        }

    }
}
