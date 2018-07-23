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
    Q_UNUSED(column);
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
    static QString isFirstOrder = "Y";
    QVector<int> rowIndex;
    QItemSelectionModel *selection = ui->tableWidget_deliverGarment->selectionModel();
    QModelIndexList selectedRows = selection->selectedRows();

    if(selectedRows.count() == 0){
        QMessageBox::warning(this,"警告", "\n请选中条目！",QMessageBox::Close);
        return;
    }

    for(int i = 0 ; i < selectedRows.count() ; i++){
        rowIndex.append(selectedRows.at(i).row());
    }

    QVector<QString> product;
    for(int j = 0 ; j < rowIndex.size() ; j++){
        product.append(ui->tableWidget_deliverGarment->item(rowIndex.at(j), 0)->text().split(":")[1].trimmed());
    }

    QString providerTempProduct = ui->label_deliverShowProduct->text();
    QStringList providerProduct = providerTempProduct.split(",");
    for(QString iter : product){
        if(!providerProduct.contains(iter)){
            QMessageBox::critical(NULL, tr("警告！"), tr("所选供货商不能生产订单中的某类商品！"),
                                                      QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
    }

    QStringList productTempInfo;
    for(int n = 0 ; n < rowIndex.size() ; n++){
        productTempInfo.append(product.at(n));
        productTempInfo.append(ui->tableWidget_deliverGarment->item(rowIndex.at(n), 1)->text().split(":")[1].trimmed());
    }
    QString productInfo = productTempInfo.join("#");


    for(int m = 0 ; m < rowIndex.size() ; m++){
        ui->tableWidget_deliverGarment->removeRow(rowIndex.at(m)-m);
    }

    qDebug() << productInfo;



    QString providerID = ui->label_deliverShowID->text();
    QString datetime = ui->label_showOrderTime_2->text();
    QStringList list;
    list.append("dp_do");
    list.append(providerID);
    list.append(datetime);
    list.append(productInfo);
    list.append(isFirstOrder);
    sendMessage(list);

    isFirstOrder = "N";

}


/**
 * @brief SystemCenter::on_pushButton_deliverCancelChoose_clicked
 * cancel choose provider
 *
 * @author ドンドン
 * @return void
 */
void SystemCenter::on_pushButton_deliverCancelChoose_clicked()
{
    ui->label_deliverShowID->clear();
    ui->label_deliverShowAds->clear();
    ui->label_deliverShowName->clear();
    ui->label_deliverShowProduct->clear();
    QMessageBox::information(NULL, tr("提示"), tr("供货商信息已被清空，请选择新的供货商！"), QMessageBox::Yes, QMessageBox::Yes);
}

