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

