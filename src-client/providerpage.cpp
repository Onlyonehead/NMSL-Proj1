#include "systemcenter.h"
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
    ui->tableWidget_providerInfo->setRowCount(0);
    ui->label_providerID->clear();
    ui->lineEdit_changeProviderAds->clear();
    ui->lineEdit_changeProviderName->clear();
    ui->lineEdit_changeProvideProduct->clear();
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

    if(providerID == "" || changeProviderAds == "" || changeProviderName == "" ||
            changeProviderPruduct == ""){
        QMessageBox::warning(this,"警告", "\n请输入全部字段！",QMessageBox::Close);
        return;
    }
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
    Q_UNUSED(column);
    ui->label_providerID->setText(ui->tableWidget_providerInfo->item(row, 0)->text());
    ui->lineEdit_changeProviderAds->setText(ui->tableWidget_providerInfo->item(row, 1)->text());
    ui->lineEdit_changeProviderName->setText(ui->tableWidget_providerInfo->item(row, 2)->text());
    ui->lineEdit_changeProvideProduct->setText(ui->tableWidget_providerInfo->item(row, 3)->text());

}



/**
 * @brief SystemCenter::on_pushButton_addProviderInfo_clicked
 * add provider information
 * @author Yihan Dong
 */
void SystemCenter::on_pushButton_addProviderInfo_clicked()
{
    QString providerAds = ui->lineEdit_addProviderAds->text().trimmed();
    QString providerName = ui->lineEdit_addProviderName->text().trimmed();
    QString providerProduct = ui->lineEdit_addProvideProduct->text().trimmed();

    if(providerAds == "" || providerName == "" || providerProduct == ""){
        QMessageBox::warning(this,"警告", "\n请输入全部字段！",QMessageBox::Close);
        return;
    }

    QStringList list;
    list.append("pp_api");
    list.append(providerAds);
    list.append(providerName);
    list.append(providerProduct);
    sendMessage(list);
}

void SystemCenter::on_pushButton_addProviderInfo_2_clicked()
{
    ui->lineEdit_addProviderAds->clear();
    ui->lineEdit_addProviderName->clear();
    ui->lineEdit_addProvideProduct->clear();
}


