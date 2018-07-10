#include "systemcenter.h"
#include "sqltool.h"
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
    QStringList list;
    list.append("pp_sp");
    sendMessage(list);
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



void SystemCenter::on_pushButton_updateProviderInfo_clicked()
{
    QStringList list;
    QString changeProviderAds;
    QString changeProviderName;
    QString changeProviderPruduct;
    QString providerID;
    providerID = ui->label_providerID->text();
    changeProviderAds = ui->lineEdit_changeProviderAds->text();
    changeProviderName = ui->lineEdit_changeProviderName->text();
    changeProviderPruduct = ui->lineEdit_changeProvideProduct->text();
    list.append("pp_cpi");
    list.append(providerID);
    list.append(changeProviderAds);
    list.append(changeProviderName);
    list.append(changeProviderPruduct);
    sendMessage(list);

}


/**
 * @brief SystemCenter::on_tableWidget_providerInfo_cellClicked
 * @param row
 * @param column
 * show detailed information
 * @author Yihan Dong
 */
void SystemCenter::on_tableWidget_providerInfo_cellClicked(int row, int column)
{
    ui->label_providerID->setText(ui->tableWidget_providerInfo->item(row, 0)->text());
    ui->lineEdit_changeProviderAds->setText(ui->tableWidget_providerInfo->item(row, 1)->text());
    ui->lineEdit_changeProviderName->setText(ui->tableWidget_providerInfo->item(row, 2)->text());
    ui->lineEdit_changeProvideProduct->setText(ui->tableWidget_providerInfo->item(row, 3)->text());
    qDebug() << ui->tableWidget_providerInfo->item(row, 0)->text() << endl;
    qDebug() << ui->tableWidget_providerInfo->item(row, 1)->text() << endl;
    qDebug() << ui->tableWidget_providerInfo->item(row, 2)->text() << endl;
    qDebug() << ui->tableWidget_providerInfo->item(row, 3)->text() << endl;

}

