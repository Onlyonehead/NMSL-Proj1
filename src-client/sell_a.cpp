#include "systemcenter.h"
#include "ui_systemcenter.h"

void SystemCenter::on_pushButton_showStores_clicked()
{
    ui->lineEdit_sell_search->clear();
    QStringList qsl;
    qsl.append("showStores");
    sendMessage(qsl);
}

void SystemCenter::on_tableWidget_stores_cellClicked(int row, int column)
{
    Q_UNUSED(column);
    QStringList qsl;
    qsl.append("storesClicked");
    qsl.append(ui->tableWidget_stores->item(row, 0)->text());
    sendMessage(qsl);
}

void SystemCenter::on_pushButton_clearStores_clicked()
{
    ui->tableWidget_stores->setRowCount(0);
    ui->tableWidget_storeRecord->setRowCount(0);
    ui->lineEdit_sell_search->setText("");
}

void SystemCenter::searchTableWidget(QTableWidget* table, const QString &arg1, QVector<int> &qv_row){
    for(int i=0; i<table->rowCount(); ++i){
        for(int j=0; j<6; ++j){
            if(-1!=table->item(i, j)->text().indexOf(arg1, 0, Qt::CaseInsensitive)){
                qv_row.append(i);
                break;
            }
        }
    }
}
void SystemCenter::setTableWidgetItemHidden(QTableWidget *table, const QString &arg1){
    QVector<int> qv_row;

    //输入为空，显示所有Item
    if(arg1==""){
        for(int i=0; i<table->rowCount(); ++i){
            table->setRowHidden(i, false);
        }
    } else{
        searchTableWidget(table, arg1, qv_row);
        QVector<int>::iterator it;
        for(int i=0; i<table->rowCount(); ++i){
            table->setRowHidden(i, true);
        }
        for(it=qv_row.begin(); it!=qv_row.end(); ++it){
            table->setRowHidden(*it, false);
        }
    }
}

void SystemCenter::on_lineEdit_sell_search_textChanged(const QString &arg1)
{
    setTableWidgetItemHidden(ui->tableWidget_stores, arg1);
}
