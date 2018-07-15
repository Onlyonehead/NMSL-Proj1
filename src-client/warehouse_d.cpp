#include "systemcenter.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


void SystemCenter::on_pushButton_10_clicked()
{
    ui->tableWidget_D1->setRowCount(0);

    QVector<QStringList> g = this->clothes;

    QStringList result1;

    for(QStringList l : g){
        result1.append("Clothes id:  " + l.at(0) + "\n- Style: "
                       + l.at(1));
    }

    Tool::QStringList_removeDuplicates(&result1);

    QVector<QStringList> w = this->warehouse;

    QStringList result2;

    for(QStringList l : w){
        result2.append("Warehouse id:  " + l.at(0) + "\n- Name: "
                     + l.at(1));
    }

    Tool::QStringList_removeDuplicates(&result2);


    QStringList list;

    list = result1;

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

    list = result2;
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

void SystemCenter::on_pushButton_11_clicked()
{
    ui->warehouse_search_D->clear();
    ui->tableWidget_D1->setRowCount(0);
    ui->tableWidget_D2->setRowCount(0);
    ui->tableWidget_D3->setRowCount(0);
    ui->tableWidget_D4->setRowCount(0);
    QPixmap *pixmap = new QPixmap(":/default.jpg");
    QApplication::processEvents();
    ui->label_clothes_D->setScaledContents(true);
    ui->label_clothes_D->setPixmap(*pixmap);

    delete pixmap;

    ui->label_72->clear();
    ui->label_73->clear();
    ui->label_74->clear();
    ui->label_75->clear();
    ui->warehouse_label_D->clear();
    ui->quantity_D->clear();

    QApplication::processEvents();
}

void SystemCenter::on_tableWidget_D1_itemClicked(QTableWidgetItem *item){

    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

    QStringList result;

    for(QStringList l : this->clothes){
        if(l.at(0) == s){
            result = l;
            break;
        }
    }

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

void SystemCenter::on_tableWidget_D2_itemClicked(QTableWidgetItem *item){

    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

    ui->warehouse_label_D->setText(item->text().split(QRegExp("[-:]"))[3].trimmed());

    QMap<QString, QString> stock;

    stock = this->stock_map.value(s);

    QVector<QStringList> g = this->clothes;

    QMap<QString, QString> clothes;

    for(QStringList l : g){
        clothes.insert(l.at(0), l.at(1));
    }

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


void SystemCenter::on_clothes_ADD_clicked()
{

    QString quantity = ui->quantity_D->text();
    if(quantity.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入数量！",QMessageBox::Close);
        return;
    }
    QByteArray ba = quantity.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        QMessageBox::warning(this,"警告", "\n请输入纯数字！",QMessageBox::Close);
        return;
    }

    if(!ui->tableWidget_D2->currentItem() || !ui->tableWidget_D1->currentItem()){
        QMessageBox::warning(this,"警告", "\n请选中仓库和货物！",QMessageBox::Close);
        return;
    }

    int count = ui->tableWidget_D4->rowCount();
    QString s1 = ui->tableWidget_D1->currentItem()->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            ui->tableWidget_D1->currentItem()->text().split(QRegExp("[-:]"))[3].trimmed();
    QString s2 = ui->tableWidget_D2->currentItem()->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            ui->tableWidget_D2->currentItem()->text().split(QRegExp("[-:]"))[3].trimmed();
    for(int i = 0; i < count; i++){
        if(ui->tableWidget_D4->item(i, 0)->text().trimmed() == s1 &&
                ui->tableWidget_D4->item(i, 1)->text().trimmed() == s2){
            ui->tableWidget_D4->item(i, 2)->setText(
                        QString::number(quantity.toInt() +
                        ui->tableWidget_D4->item(i, 2)->text().toInt()));
            return ;
        }

    }
    ui->tableWidget_D4->insertRow(count);

    ui->tableWidget_D4->setItem(count, 0, new QTableWidgetItem(s1));

    ui->tableWidget_D4->setItem(count, 1, new QTableWidgetItem(s2));

    ui->tableWidget_D4->setItem(count, 2, new QTableWidgetItem(ui->quantity_D->text()));

    ui->tableWidget_D4->setRowCount(count+1);
}


void SystemCenter::on_order_send_clicked()
{
    if(ui->tableWidget_D4->rowCount() == 0){
        QMessageBox::warning(this,"警告", "\n请添加订单！",QMessageBox::Close);
        return;
    }
    QMap<QString, QMap<QString, QString>> orders;
    int count = ui->tableWidget_D4->rowCount();
    for(int i = 0; i < count; i++){
        QString c_id = ui->tableWidget_D4->item(i, 0)->text().split("-")[0].trimmed();
        QString w_id = ui->tableWidget_D4->item(i, 1)->text().split("-")[0].trimmed();
        QString quantity = ui->tableWidget_D4->item(i, 2)->text().trimmed();
        QMap<QString, QString> map;
        map.clear();
        map[c_id] = quantity;
        if(orders.contains(w_id)){
            map = orders.value(w_id);
            map.insert(c_id, quantity);
        }
        orders.insert(w_id, map);
    }
    QStringList list;
    list.append("order_send");

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << (quint16) 0;

    out << list;
    out << orders;

    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    m_tcpsocket->write(message);
}

void SystemCenter::on_icon_search_D_clicked()
{
    ui->tableWidget_D1->setRowCount(0);;
    QString text = ui->warehouse_search_D->text();

    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }

    QVector<QStringList> result = this->clothes;

    int i = 0;
    for(QStringList list : result){
        if(list.at(0) == text || list.at(1) == text){
            ui->tableWidget_D1->insertRow(i);
            ui->tableWidget_D1->setItem(i, 0, new QTableWidgetItem(list.at(0) + " - " + list.at(1)));
            i++;
            QApplication::processEvents();
        }
    }
    ui->tableWidget_D1->setRowCount(i);

    result = this->warehouse;
    i = 0;
    for(QStringList list : result){
        if(list.at(0) == text || list.at(1) == text){
            ui->tableWidget_D2->insertRow(i);
            ui->tableWidget_D2->setItem(i, 0, new QTableWidgetItem(list.at(0) + " - " + list.at(1)));
            i++;
            QApplication::processEvents();
        }
    }
    ui->tableWidget_D2->setRowCount(i);
}
