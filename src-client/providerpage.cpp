#include "systemcenter.h"
#include "sqltool.h"
#include "order.h"
#include "provider.h"
#include "ui_systemcenter.h"
#include <QDebug>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QSqlQuery>
#include <QVector>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QStringList>
#include <QList>
#include <QMessageBox>


/**
*
* display all providers information
*
* @author Yihan Dong
* @return information
*/


void SystemCenter::on_pushButton_showProvider_clicked()
{
    ui->tableWidget_providerInfo->setRowCount(0);
    int i = 0;
    QVector<QStringList> providerInfo;
    Provider::Info(providerInfo);
    int n = providerInfo.size();
    ui->tableWidget_providerInfo->setRowCount(providerInfo.size());
    while (n) {
        ui->tableWidget_providerInfo->setItem(i, 0, new QTableWidgetItem(providerInfo.at(i).at(0)));
        ui->tableWidget_providerInfo->setItem(i, 1, new QTableWidgetItem(providerInfo.at(i).at(1)));
        ui->tableWidget_providerInfo->setItem(i, 2, new QTableWidgetItem(providerInfo.at(i).at(2)));
        ui->tableWidget_providerInfo->setItem(i, 3, new QTableWidgetItem(providerInfo.at(i).at(3)));
        QTableWidgetItem *item = ui->tableWidget_providerInfo->item(i, 0);
        item->setFlags(item->flags() & (Qt::ItemIsEditable));
        i++;
        n--;
    }
    ui->tableWidget_providerInfo->setRowCount(i);
    progressBar();
}


/**
 * clear all provider information
 *
 * @author Yihan Dong
*/


void SystemCenter::on_pushButton_clearProvider_clicked()
{
    QStringList providerInfoHeader;
    providerInfoHeader << tr("供货商编号") << tr("供货商地址") << tr("供货商名称") << tr("所提供服装");
    ui->tableWidget_providerInfo->clear();
    ui->tableWidget_providerInfo->setRowCount(0);
    ui->tableWidget_providerInfo->setHorizontalHeaderLabels(providerInfoHeader);
}



/**
 * when cell changed , update the database
 *
 * @author Yihan Dong
 * undone
*/




//void SystemCenter::on_tableWidget_providerInfo_cellDoubleClicked(int row, int column)
//{
//    QString alterAttribute, alterValue;
//    QTableWidgetItem *item = ui->tableWidget_providerInfo->item(row, column);
////    int rowIndex, columnIndex;
////    rowIndex = ui->tableWidget_providerInfo->currentRow();
////    columnIndex = ui->tableWidget_providerInfo->currentColumn();
//    QMessageBox message(QMessageBox::Warning, "Concern", "Confirm changing data?", QMessageBox::Yes|QMessageBox::No, NULL);
//    if(message.exec() == QMessageBox::Yes ){
//        int providerID = ui->tableWidget_providerInfo->item(row, 0)->text().toInt();
//        alterValue = ui->tableWidget_providerInfo->item(row, column)->text();
//        if(column == 1){
//            alterAttribute = "address";
//        }else if(column == 2){
//            alterAttribute = "name";
//        }else if(column == 3){
//            alterAttribute = "productInfo";
//        }
//        Provider::updateProviderInfo(providerID, alterAttribute, alterValue);
//    }else{
//        ui->tableWidget_providerInfo->setItem(row, column, item);
//    }

//}


