#include "systemcenter.h"
#include "ui_systemcenter.h"

/**
 * on_pushButton_4_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_4_clicked()
{
    ui->tableWidget->setRowCount(0);
    QVector<QStringList> result = warehouse;
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

/**
 * on_pushButton_6_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_6_clicked()
{
    ui->warehouse_search_A->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_A->setRowCount(0);
    ui->warehouse_id->clear();
}

/**
 * furry search init
 *
 * @author Zicun Hang
 */
void SystemCenter::warehouseEditComplete(){
    QStringList list;
    list.append("info_whEC");
    sendMessage(list);

}


/**
 * on_icon_search_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_icon_search_clicked()
{
    QString text = ui->warehouse_search_A->text();
    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }

    ui->tableWidget->setRowCount(0);
    QVector<QStringList> result = warehouse;
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



void SystemCenter::on_w_search_A_clicked()
{
    QString text = ui->warehouse_id->text();

    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入id！",QMessageBox::Close);
        return;
    }
    QByteArray ba = text.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        QMessageBox::warning(this,"警告", "\n请输入纯数字！",QMessageBox::Close);
        return;
    }

    QStringList msg;
    msg.append("wh_history");
    msg.append(text);
    sendMessage(msg);
}

void SystemCenter::on_tableWidget_A_itemClicked(QTableWidgetItem *item){
    QString s;
    s += "\n";
    s += ui->tableWidget_A->item(item->row(), 2)->text();
    s += "\n";
    s += "\n";
    s += ui->tableWidget_A->item(item->row(), 0)->text();
    s += "\n";
    s += ui->tableWidget_A->item(item->row(), 1)->text();
    s += "\n";
    s += "\n";
    for(QStringList l : wh_history){
        QStringList temp = l.at(0).split(QRegExp("[A-Z]"));
        if(l.at(1) == ui->tableWidget_A->item(item->row(), 0)->text().split(":")[1].trimmed() &&
                l.at(2) == ui->tableWidget_A->item(item->row(), 1)->text().split(":")[1].trimmed() &&
                temp.at(0) + " " + temp.at(1)
                == ui->tableWidget_A->item(item->row(), 2)->text()){
            s += l.at(3);
            break;
        }
    }
    QMessageBox::information(this,"历史", s,QMessageBox::Ok);
}

void SystemCenter::on_w_search_A_3_clicked()
{
    QStringList msg;
    msg.append("wh_history_all");
    sendMessage(msg);
}
