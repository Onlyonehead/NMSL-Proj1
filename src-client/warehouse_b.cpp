#include "systemcenter.h"
#include "sqltool.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


void SystemCenter::on_pushButton_8_clicked()
{
    ui->tableWidget_B->setRowCount(0);

    QVector<QStringList> result;
    Garment::Info(result);
    int n = result.size();
    QApplication::processEvents();

    QStringList *list = new QStringList();

    while(n){
        list->append("   " + result.at(result.size()-n).at(0) + " - "
                     + result.at(result.size()-n).at(1));
        n--;
    }

    Tool::QStringList_removeDuplicates(list);

    n = list->size();

    while(n){
        QApplication::processEvents();
        ui->tableWidget_B->insertRow(list->size()-n);
        ui->tableWidget_B->setItem(list->size()-n, 0, new QTableWidgetItem(list->at(list->size()-n)));
        n--;
    }

    ui->tableWidget_B->setRowCount(list->size());

    delete list;

    progressBar_fast();
}

void SystemCenter::warehouseEditComplete3(){
    QStringList wordlist;
    QVector<QStringList> result;
    QApplication::processEvents();
    Garment::Info(result);
    QApplication::processEvents();
    int n = result.size();
    while(n){
        QApplication::processEvents();
        wordlist << result.at(n-1).at(0) << result.at(n-1).at(1);
        n--;
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
    ui->warehouse_search_B->setCompleter(completer);
}

void SystemCenter::on_tableWidget_B_itemClicked(QTableWidgetItem *item){

    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QStringList result;
    QString s = item->text().split("-")[0].trimmed();
    Garment::Info(s.toInt(), result);
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

    QMap<QString, QString> warehouse;
    Warehouse::info(warehouse);

    QSqlQuery query;
    SQLTool::search(query, "stock", "clothes_id", id);

    int quantity_count = 0;

    int i = 0;

    while(query.next()){
        QApplication::processEvents();
        ui->tableWidget_B_2->insertRow(i);
        ui->tableWidget_B_2->setItem(i, 0, new QTableWidgetItem(warehouse.find(query.value(0).toString()).value()));
        ui->tableWidget_B_2->setItem(i, 1, new QTableWidgetItem(query.value(2).toString()));
        quantity_count += query.value(2).toInt();
        i++;

    }
    ui->tableWidget_B_2->setRowCount(i);
    ui->label_35->setText(QString::number(quantity_count));
    progressBar_fast();

}


void SystemCenter::on_pushButton_9_clicked()
{
    ui->warehouse_search_B->clear();
    ui->tableWidget_B->setRowCount(0);
    QPixmap *pixmap = new QPixmap(":/default.jpg");
    QApplication::processEvents();
    ui->label_clothes->setScaledContents(true);
    ui->label_clothes->setPixmap(*pixmap);

    delete pixmap;

    ui->label_29->clear();
    ui->label_30->clear();
    ui->label_31->clear();
    ui->label_32->clear();
    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QApplication::processEvents();
}


void SystemCenter::on_icon_search_B_clicked()
{
    ui->tableWidget_B->setRowCount(0);;

    QApplication::processEvents();
    QString s = ui->warehouse_search_B->text();
    if(s.toInt()){
        QStringList result;
        Garment::Info(s.toInt(), result);
        ui->tableWidget_B->insertRow(0);
        ui->tableWidget_B->setItem(0, 0, new QTableWidgetItem(result.at(0) + " - " + result.at(1)));
        ui->tableWidget_B->setRowCount(1);


        QApplication::processEvents();
    }else{
        QVector<QStringList> result;
        Garment::Info(s, result);
        int n = result.size();

        QStringList *list = new QStringList();

        while(n){
            list->append("   " + result.at(result.size()-n).at(0) + " - "
                         + result.at(result.size()-n).at(1));
            n--;
        }

        QApplication::processEvents();
        Tool::QStringList_removeDuplicates(list);

        n = list->size();

        while(n){
            QApplication::processEvents();
            ui->tableWidget_B->insertRow(list->size()-n);
            ui->tableWidget_B->setItem(list->size()-n, 0, new QTableWidgetItem(list->at(list->size()-n)));
            n--;
        }

        ui->tableWidget_B->setRowCount(list->size());
        delete list;
    }




}
