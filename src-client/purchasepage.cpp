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
 * tableWidget_generateOrder show garment information
 *
 * @author Yihan Dong
 * @return void
 *
 * done
 */



void SystemCenter::on_pushButton_3_clicked()
{
    QStringList list;
    list.append("pcp_sg");
    sendMessage(list);
}

/**
 * add order information to QTableWidget_orderGarment
 *
 * @author Yihan Dong
 * @return void
 *
 * done
 */



void SystemCenter::on_pushButton_addGarment_clicked()
{
    int count = ui->tableWidget_orderGarment->rowCount();
    for(int i = 0 ; i < count ; i++){
        if(ui->tableWidget_generateOrder->currentItem()->text().toInt()
                == ui->tableWidget_orderGarment->item(i, 0)->text().toInt()){
            ui->tableWidget_orderGarment->item(i,1)->setText(
                        QString::number(ui->lineEdit_garmentNum->text().toInt()
                                        + ui->tableWidget_orderGarment->item(i,1)->text().toInt()));
            return;
        }
    }

    ui->tableWidget_orderGarment->insertRow(count);

    ui->tableWidget_orderGarment->setItem(count, 0, new QTableWidgetItem(
                                              ui->tableWidget_generateOrder->currentItem()->text()));

    ui->tableWidget_orderGarment->setItem(count, 1, new QTableWidgetItem(
                                              ui->lineEdit_garmentNum->text()));
    ui->tableWidget_orderGarment->setRowCount(count + 1);





}

/**
 * delete order information to tableWidget_orderGarment
 *
 * @author Yihan Dong
 * @return void
 *
 * done
 */




void SystemCenter::on_pushButton_deleteGarment_clicked()
{

   QVector<int> rowIndex;
   QItemSelectionModel *selections = ui->tableWidget_orderGarment->selectionModel();
   QModelIndexList selectedrows = selections->selectedRows();

   for(int i = 0 ; i < selectedrows.count() ; i++){
       rowIndex.append(selectedrows.at(i).row());
   }

   for(int j = 0 ; j < rowIndex.size() ; j++){
       ui->tableWidget_orderGarment->removeRow(rowIndex.at(j));
   }

}


/**
* show order garment table to deliver page order table
*
* @author Yihan Dong
* @return void
* done
*/

void SystemCenter::on_pushButton_ConfirmOrder_clicked()
{
    QMessageBox msgbox;
    msgbox.setText(tr("订单信息已生成。"));
    msgbox.setInformativeText(tr("确认订单信息吗？"));
    msgbox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Save);
    int ret  = msgbox.exec();
    switch (ret) {
    case QMessageBox::Save:

        ui->tableWidget_deliverGarment->setRowCount(ui->tableWidget_orderGarment->rowCount());
        for(int i = 0; i < ui->tableWidget_orderGarment->rowCount() ; i++){
            for(int j = 0 ; j < ui->tableWidget_orderGarment->columnCount() ; j++){
                ui->tableWidget_deliverGarment->setItem(i, j, new QTableWidgetItem(
                                                            ui->tableWidget_orderGarment->item(i, j)->text()));
            }
        }

        ui->frame_pA->setVisible(false);
        ui->frame_pB->setVisible(true);

        break;
    case QMessageBox::Cancel:
        break;
    }



}


/**
 * cancel order generation & clear all tablewidget
 *
 * @author Yihan Dong
 * @return void
 *
 * done
 */


void SystemCenter::on_pushButton_cancelOrder_clicked()
{
    QStringList generateOrderHeader, orderGarmentHeader;
    ui->tableWidget_generateOrder->clear();
    ui->tableWidget_generateOrder->setRowCount(0);
    generateOrderHeader << tr("服装编号") << tr("服装样式")
                        << tr("服装大小") << tr("服装图片") << tr("服装价格");
    orderGarmentHeader << tr("服装编号") << tr("服装数量");
    ui->tableWidget_generateOrder->setHorizontalHeaderLabels(generateOrderHeader);
    ui->tableWidget_orderGarment->clear();
    ui->tableWidget_orderGarment->setRowCount(0);
    ui->tableWidget_orderGarment->setHorizontalHeaderLabels(orderGarmentHeader);
    ui->lineEdit_garmentNum->clear();
    ui->label_purchaseShowID->clear();
    ui->label_purchaseShowPic->clear();
    ui->label_purchaseShowPrice->clear();
    ui->label_purchaseShowSize->clear();
    ui->label_purchaseShowStyle->clear();

}




/**
 * @brief SystemCenter::timer_deal_slot_function
 *
 * show current time automocally
 * @author Yihan Dong
 */
void SystemCenter::timer_deal_slot_function()
{
    QDateTime datetime = QDateTime::currentDateTime();
    int y = datetime.date().year();
    int m = datetime.date().month();
    int d = datetime.date().day();
    QString strTime = datetime.time().toString();
    ui->label_showOrderTime->setText(QString::number(y) + "-" + QString::number(m) +
                                     "-" + QString::number(d) + " " + strTime);
    ui->label_showOrderTime_2->setText(QString::number(y) + "-" + QString::number(m) +
                                       "-" + QString::number(d) + " " + strTime);
}



/**
 * @brief SystemCenter::on_tableWidget_generateOrder_cellClicked
 * @param row
 * @param column
 * show garment detailed information
 * @author Yihan Dong
 */
void SystemCenter::on_tableWidget_generateOrder_cellClicked(int row, int column)
{
    QString ID = ui->tableWidget_generateOrder->item(row, 0)->text();
    Q_UNUSED(column);
    QStringList list;
    list.append("pcp_sgdi");
    list.append(ID);
    sendMessage(list);
}

