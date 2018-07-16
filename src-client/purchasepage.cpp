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

//老子写的
void SystemCenter::on_tableWidget_generateOrder_itemClicked(QTableWidgetItem *item){
    current_selected.clear();
    current_selected.append(ui->tableWidget_generateOrder->item(item->row(),0)->text());
    current_selected.append(ui->tableWidget_generateOrder->item(item->row(),1)->text());
    current_selected.append(ui->tableWidget_generateOrder->item(item->row(),2)->text());
    current_selected.append(ui->tableWidget_generateOrder->item(item->row(),3)->text());
    current_selected.append(ui->tableWidget_generateOrder->item(item->row(),4)->text());

    QString s = ui->tableWidget_generateOrder->item(item->row(), 0)->text();

    QStringList result;

    for(QStringList l : this->clothes){
        if(l.at(0) == s){
            result = l;
            break;
        }
    }
    QString id = result.at(0);
    QString style = result.at(1);
    QString size = result.at(2);
    QString path = result.at(3);
    QString price = result.at(4);

    QApplication::processEvents();

    QPixmap *pixmap = new QPixmap(DIR + QString("/clothes/") + path);
    if (pixmap->isNull()){
        download("/clothes/" + path, DIR +QString("/clothes/")+ path);
    }

    if (pixmap->isNull()){
        pixmap = new QPixmap(":/default.jpg");
    }
    QApplication::processEvents();
    ui->label_purchaseShowPic->setScaledContents(true);
    ui->label_purchaseShowPic->setPixmap(*pixmap);
    delete pixmap;
    QApplication::processEvents();

    ui->label_purchaseShowID->setText(id);
    ui->label_purchaseShowPrice->setText(price);
    ui->label_purchaseShowSize->setText(size);
    ui->label_purchaseShowStyle->setText(style);
    QApplication::processEvents();
}





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
    QString quantity = ui->lineEdit_garmentNum->text();
    if(quantity.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入数量！",QMessageBox::Close);
        return;
    }
    QByteArray ba = quantity.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        QMessageBox::warning(this,"警告", "\n请输入纯数字！",QMessageBox::Close);
        return;
    }

    if(current_selected.isEmpty()){
        QMessageBox::warning(this,"警告", "\n请选中货物！",QMessageBox::Close);
        return;
    }

    int count = ui->tableWidget_orderGarment->rowCount();
    for(int i = 0 ; i < count ; i++){
        if("Clothes id: " + current_selected.at(0)
                == ui->tableWidget_orderGarment->item(i, 0)->text()){
            ui->tableWidget_orderGarment->item(i,1)->setText("Quantity: " +
                        QString::number(ui->lineEdit_garmentNum->text().toInt()
                                        + ui->tableWidget_orderGarment->item(i,1)->text().split(":")[1].toInt()));
            return;
        }
    }

    ui->tableWidget_orderGarment->insertRow(count);

    ui->tableWidget_orderGarment->setItem(count, 0, new QTableWidgetItem("Clothes id: " +
                                              current_selected.at(0)));

    ui->tableWidget_orderGarment->setItem(count, 1, new QTableWidgetItem("Quantity: " +
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
    if(ui->tableWidget_orderGarment->rowCount() == 0){
        QMessageBox::warning(this,"警告", "\n请添加货物！",QMessageBox::Close);
        return;
    }
    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "Confirm to send this order ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        ui->tableWidget_deliverGarment->setRowCount(ui->tableWidget_orderGarment->rowCount());
        for(int i = 0; i < ui->tableWidget_orderGarment->rowCount() ; i++){
            for(int j = 0 ; j < ui->tableWidget_orderGarment->columnCount() ; j++){
                ui->tableWidget_deliverGarment->setItem(i, j, new QTableWidgetItem(
                                                            ui->tableWidget_orderGarment->item(i, j)->text()));
            }
        }
    }

    QMessageBox::information(this,"提示", "\n添加成功！",QMessageBox::Close);

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
//    generateOrderHeader << tr("服装编号") << tr("服装样式")
//                        << tr("服装大小") << tr("服装图片") << tr("服装价格");
//    orderGarmentHeader << tr("服装编号") << tr("服装数量");
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


