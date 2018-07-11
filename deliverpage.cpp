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
 * @brief SystemCenter::on_pushButton_deliverShowProvider_clicked
 * deliver page show provider
 *
 * @author Yihan Dong
 * @return all providers IDs
 */
void SystemCenter::on_pushButton_deliverShowProvider_clicked()
{
    QStringList list;
    list.append("dp_sp");
    sendMessage(list);
}


/**
 * @brief SystemCenter::on_tableWidget_deliverProvider_cellClicked
 * @param row
 * @param column
 * click tablewidget deliver page provider id to display provider detailed information
 * @author Yihan Dong
 */
void SystemCenter::on_tableWidget_deliverProvider_cellClicked(int row, int column)
{
    QString ID = ui->tableWidget_deliverProvider->item(row, 0)->text();
    QStringList list;
    list.append("dp_spdi");
    list.append(ID);
    sendMessage(list);
}


/**
 * @brief SystemCenter::on_pushButton_deliverOrder_clicked
 * deliver order to provider
 * @author Yihan Dong
 *
 */
void SystemCenter::on_pushButton_deliverOrder_clicked()
{
    QVector<int> rowIndex;
    QItemSelectionModel *selection = ui->tableWidget_deliverGarment->selectionModel();
    QModelIndexList selectedRows = selection->selectedIndexes();

    for(int i = 0 ; i < selectedRows.count() ; i++){
        rowIndex.append(selectedRows.at(i).row());
    }

    QVector<QString> productInfo;
    for(int j = 0 ; j < rowIndex.size() ; j++){
        productInfo.append(ui->tableWidget_deliverGarment->item(rowIndex.at(j), 0)->text());
    }

    QString providerTempProduct = ui->label_deliverShowProduct->text();
    QStringList providerProduct = providerTempProduct.split(",");

    for(QString iter : productInfo){
        if(!providerProduct.contains(iter)){
            QMessageBox::critical(NULL, tr("警告！"), tr("所选供货商不能生产订单中的某类商品！"),
                                                      QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }



    QStringList list;
    list.append("dp_do");


}


