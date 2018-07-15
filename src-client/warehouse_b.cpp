#include "systemcenter.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


void SystemCenter::on_pushButton_8_clicked()
{
    QStringList msg;
    msg.append("pB8");
    sendMessage(msg);

}

void SystemCenter::on_tableWidget_B_itemClicked(QTableWidgetItem *item){

    ui->tableWidget_B_2->setRowCount(0);
    ui->label_35->clear();
    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

<<<<<<< HEAD
    QStringList msg;
    msg.append("tWBiC");
    msg.append(s);
    sendMessage(msg);
=======
    QStringList result;

    for(QStringList l : this->clothes){
        if(l.at(0) == s){
            result = l;
            break;
        }
    }

    QMap<QString, QString> warehouse = this->warehouse_map;
    QVector<QStringList> stock = this->stock;


    QString id = result.at(0);
    QString style = result.at(1);
    QString size = result.at(2);
    QString path = result.at(3);
    QString price = result.at(4);

    QApplication::processEvents();
    QPixmap *pixmap = new QPixmap(USER_DIR + path);
    if(pixmap->isNull()){
        download("http://39.108.155.50/project1/clothes/" + path, USER_DIR + path);
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
>>>>>>> dc53185c74bac0e0ea59db6aef92386714638b80

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
    QString text = ui->warehouse_search_B->text();

    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }

    QVector<QStringList> result = this->clothes;

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
