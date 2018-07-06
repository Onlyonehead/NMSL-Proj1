#include "systemcenter.h"
#include "sqltool.h"
#include "garment.h"
#include "order.h"
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
    ui->tableWidget_generateOrder->setRowCount(0);
    ui->tableWidget_generateOrder->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_generateOrder->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_generateOrder->setAlternatingRowColors(true);
    ui->tableWidget_generateOrder->verticalHeader()->setVisible(false);
    int i = 0;
    QVector<QStringList> garmentInfo;
    Garment::Info(garmentInfo);
    int n = garmentInfo.size();
    ui->tableWidget_generateOrder->setRowCount(garmentInfo.size());
    while (n) {
        ui->tableWidget_generateOrder->setItem(i, 0, new QTableWidgetItem(garmentInfo.at(i).at(0)));
        ui->tableWidget_generateOrder->setItem(i, 1, new QTableWidgetItem(garmentInfo.at(i).at(1)));
        ui->tableWidget_generateOrder->setItem(i, 2, new QTableWidgetItem(garmentInfo.at(i).at(2)));
        ui->tableWidget_generateOrder->setItem(i, 3, new QTableWidgetItem(garmentInfo.at(i).at(3)));
        ui->tableWidget_generateOrder->setItem(i, 4, new QTableWidgetItem(garmentInfo.at(i).at(4)));
        i++;
        n--;
    }
    ui->tableWidget_generateOrder->setRowCount(i);
    progressBar();
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
    ui->tableWidget_generateOrder->setStyleSheet("selection-background-color::lightblue");
    garmentID = ui->tableWidget_generateOrder->item(rowIndex, 0)->text().toInt();
    garmentNum = ui->spinBox_garmentNum->value();
    static QVector<QStringList> orderInfo;
    QStringList list;
    list.clear();
    list.append(QString::number(garmentID, 10));
    list.append(QString::number(garmentNum, 10));
    orderInfo.append(list);
    QStringList *data;
    data = orderInfo.data();
//    QString temp = data->join(",");
//    QString temp1 = temp.section(",", 0, 0);
//    QString temp2 = temp.section(",", 1, 1);


/**
  *show information in tabelWidget_orderGarment
  *
  * @author Yihan Dong
  *
*/

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
* done
*
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
    Order order(1, datetime, productInfo);

    Order::saveOrder(order);
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
    ui->spinBox_garmentNum->clear();

}
