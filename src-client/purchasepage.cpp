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
 * undone
 * todo:增加相同编号的服装 在表格中显示为一行
 */



void SystemCenter::on_pushButton_addGarment_clicked()
{
    //prepare job
    QString orderID;
    QString orderDatetime;
    int garmentID;
    int garmentNum;
    int rowIndex = ui->tableWidget_generateOrder->currentRow();
    orderDatetime = ui->label_showOrderTime->text();
    orderID = orderDatetime;
    garmentID = ui->tableWidget_generateOrder->item(rowIndex, 0)->text().toInt();
    garmentNum = ui->lineEdit_garmentNum->text().toInt();
    static QVector<QStringList> orderInfo;
    QStringList list;
    list.clear();
    list.append(QString::number(garmentID, 10));
    list.append(QString::number(garmentNum, 10));
    orderInfo.append(list);
    bool isRepeated = false;
    int i = 0;
    while (i < ui->tableWidget_orderGarment->rowCount()) {
        if(ui->tableWidget_orderGarment->item(i, 0)->text().toInt() == garmentID){
            int tempNum = ui->tableWidget_orderGarment->item(i, 1)->text().toInt();
            tempNum += garmentNum;
            ui->tableWidget_orderGarment->setItem(i, 1, new QTableWidgetItem(QString::number(tempNum)));
            isRepeated = true;
        }
        i++;
    }

    if(!isRepeated){
        static int rowIndex2 = 0;
        ui->tableWidget_orderGarment->setRowCount(orderInfo.size());
        ui->tableWidget_orderGarment->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_orderGarment->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_orderGarment->setAlternatingRowColors(true);
        ui->tableWidget_orderGarment->verticalHeader()->setVisible(false);

        ui->tableWidget_orderGarment->setItem(rowIndex2, 0,
                                              new QTableWidgetItem(QString::number(garmentID)));
        ui->tableWidget_orderGarment->setItem(rowIndex2, 1,
                                              new QTableWidgetItem(QString::number(garmentNum)));

        rowIndex2++;
    }

//    QStringList *data;
//    data = orderInfo.data();
//    QString temp = data->join(",");
//    QString temp1 = temp.section(",", 0, 0);
//    QString temp2 = temp.section(",", 1, 1);


/**
  *show information in tabelWidget_orderGarment
  *
  * @author Yihan Dong
  *
*/




/**
* merge the same garment ID order in tableWidget_OrderGarment
*
* @author Yihan dong
* undone
*
* todo:把生成行和生成内容的语句也要放在这一块 应该是成功了 这段不注释下面的表什么都没有 但是最开始检查的是这次
* 输入的服装的ID和已经显示的服装ID 所以一定会冲突
* 在显示之前就整理好应该显示的信息
*/

//    int j = 0;
//    while (j < ui->tableWidget_orderGarment->rowCount()) {
//        if(ui->tableWidget_orderGarment->item(j, 0)->text() == QString::number(garmentID)){
//            QString temp = data[j].join(",");
//            QString temp1 = temp.section(",", 0, 0);//订单记录中相同编号
//            QString temp2 = temp.section(",", 1, 1);//相同编号的服装数量
//            int temp3 = temp2.toInt() + garmentNum;
//            temp2 = QString::number(temp3);
//            orderInfo.remove(j);
//            orderInfo.removeLast();
//            list.clear();
//            list.append(temp1);
//            list.append(temp2);
//            ui->tableWidget_orderGarment->setRowCount(orderInfo.size());
//            ui->tableWidget_orderGarment->setItem(j, 0, new QTableWidgetItem(temp1));
//            ui->tableWidget_orderGarment->setItem(j, 0, new QTableWidgetItem(temp2));
//            ui->tableWidget_orderGarment->removeRow(rowIndex2);

//        }
//    }




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

    int rowIndex = ui->tableWidget_orderGarment->currentRow();
    ui->tableWidget_orderGarment->removeRow(rowIndex);

}


/**
* confirm & save order & update the database
*
* @author Yihan Dong
* @return void
* undone
* need to redo
*/

void SystemCenter::on_pushButton_ConfirmOrder_clicked()
{
    int rowIndex = 0;
    QStringList productInfo;
    QString datetime;
    datetime = ui->label_showOrderTime->text();
    while (rowIndex < ui->tableWidget_orderGarment->rowCount()) {
        productInfo.append(ui->tableWidget_orderGarment->item(rowIndex, 0)->text());
        productInfo.append(ui->tableWidget_orderGarment->item(rowIndex, 1)->text());
        rowIndex++;
    }
//    Order order(1, datetime, productInfo);

//    Order::saveOrder(order);
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
    ui->label_showOrderTime->setText(QString::number(y) + "/" + QString::number(m) +
                                     "/" + QString::number(d) + " " + strTime);
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
    ui->label_purchaseShowID->setText(ui->tableWidget_orderGarment->item(row, 0)->text());
    ui->label_purchaseShowStyle->setText(ui->tableWidget_orderGarment->item(row, 1)->text());
    ui->label_purchaseShowSize->setText(ui->tableWidget_orderGarment->item(row,2)->text());
    ui->label_purchaseShowPrice->setText(ui->tableWidget_orderGarment->item(row, 4)->text());
    QStringList list;
    list.append("pcp_sgdi");
    list.append(ui->tableWidget_orderGarment->item(row, 0)->text());
    sendMessage(list);
}

