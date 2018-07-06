#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "store.h"

#include <QVector>



/**
 * @brief MainWindow::setStackedWidget_delivery
 */
void MainWindow::setStackedWidget_delivery(){
    ui->stackedWidget_delivery->setCurrentIndex(0);
    ui->tableWidget_delivery_cloth->clearContents();
    purchaseSignal = false;

    ui->tableWidget_delivery_cloth->verticalHeader()->setVisible(false); //设置表垂直头不可见
    //    ui->tableWidget_delivery_clo                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      th->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑,但是不会像设置Enable那样使界面变灰
    ui->tableWidget_delivery_cloth->setRowCount(qv_clothes.size());//设置行数，与公司所有私服种数相同
    ui->tableWidget_delivery_cloth->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽

    //QVector<QStringList> qv_clothes;
    //QVector<QVector<QString>> qv_stock;
    //对照qv_clothes和qv_stock
    QVector<QStringList>::const_iterator it_c;
    QVector<QVector<QString> >::const_iterator it_s;
    int i=0;
    for(it_c=qv_clothes.constBegin(), it_s=qv_stock.constBegin(); it_c!=qv_clothes.constEnd(); ++it_c){

        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->tableWidget_delivery_cloth->setItem(i,0,check);
        ui->tableWidget_delivery_cloth->setItem(i,1,new QTableWidgetItem(it_c->at(0))); //id_cloth
        ui->tableWidget_delivery_cloth->setItem(i,2,new QTableWidgetItem(it_c->at(1))); //style
        ui->tableWidget_delivery_cloth->setItem(i,3,new QTableWidgetItem(it_c->at(2))); //size
        ui->tableWidget_delivery_cloth->setItem(i,4,new QTableWidgetItem(it_c->at(4))); //pric
        ui->tableWidget_delivery_cloth->setItem(i,6,new QTableWidgetItem(QString::number(0, 10))); //purchase

        //如果服装id匹配
        if(it_s!=qv_stock.constEnd()&&it_c->at(0)==it_s->at(0)){
            ui->tableWidget_delivery_cloth->setItem(i,5,new QTableWidgetItem(it_s->at(1))); //exist
            ++it_s;
        } else {
            ui->tableWidget_delivery_cloth->setItem(i,5,new QTableWidgetItem(QString::number(0, 10))); //exist
            ui->tableWidget_delivery_cloth->item(i, 0)->setBackground(QBrush(Qt::lightGray));
            ui->tableWidget_delivery_cloth->item(i, 1)->setBackground(QBrush(Qt::lightGray));
            ui->tableWidget_delivery_cloth->item(i, 2)->setBackground(QBrush(Qt::lightGray));
            ui->tableWidget_delivery_cloth->item(i, 3)->setBackground(QBrush(Qt::lightGray));
            ui->tableWidget_delivery_cloth->item(i, 4)->setBackground(QBrush(Qt::lightGray));
            ui->tableWidget_delivery_cloth->item(i, 5)->setBackground(QBrush(Qt::lightGray));
            ui->tableWidget_delivery_cloth->item(i, 6)->setBackground(QBrush(Qt::lightGray));
        }

        ui->tableWidget_delivery_cloth->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_delivery_cloth->item(i, 2)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_delivery_cloth->item(i, 3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_delivery_cloth->item(i, 4)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_delivery_cloth->item(i, 5)->setFlags(Qt::ItemIsEnabled);

        ++i;
    }
    purchaseSignal = true;

}

void MainWindow::on_pushButton_purchase_clicked()
{
    ui->stackedWidget_delivery->setCurrentIndex(0);
}

void MainWindow::on_pushButton_message_clicked()
{
    ui->stackedWidget_delivery->setCurrentIndex(1);
}


void MainWindow::on_tableWidget_delivery_cloth_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    if(0!=column){
        QString path = Store::getPicPath(ui->tableWidget_delivery_cloth->item(row, 1)->text());

        QPixmap *pixmap = new QPixmap("./" + path);
        if (pixmap->isNull()){
            download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
        }
        if (pixmap->isNull()){
            pixmap = new QPixmap(":/default.jpg");
        }

        ui->label_delivery_pic->setScaledContents(true);
        ui->label_delivery_pic->setPixmap(*pixmap);
        ui->label_delivery_style->setText(ui->tableWidget_delivery_cloth->item(row, 2)->text());//直接从表格获取style值
    }
}

void MainWindow::on_tableWidget_delivery_cloth_cellChanged(int row, int column)
{
    if(purchaseSignal){

        //CheckBox状态改变
        if(0==column){
            if(Qt::Unchecked==ui->tableWidget_delivery_cloth->item(row, 0)->checkState()&&ui->tableWidget_delivery_cloth->item(row, 6)->text()!="0"){
                ui->tableWidget_delivery_cloth->item(row, 6)->setText(QString::number(0, 10));
                int amount=0;
                purchaseCount(&amount);
                ui->label_purchase_totalCount->setText(QString::number(amount, 10));
            }
        }

        //数量被修改
        if(6==column){
            if(Qt::Checked==ui->tableWidget_delivery_cloth->item(row, 0)->checkState()){
                int max_amount = 1000;
                int sell_amount = ui->tableWidget_delivery_cloth->item(row, column)->text().toInt();
                if(sell_amount>max_amount)
                    ui->tableWidget_delivery_cloth->item(row, column)->setText(QString::number(max_amount, 10));
            } else {
                ui->tableWidget_delivery_cloth->item(row, column)->setText(QString::number(0, 10));
            }

            int amount=0;
            purchaseCount(&amount);
            ui->label_purchase_totalCount->setText(QString::number(amount, 10));
        }
    }
}

void MainWindow::purchaseCount(int *countClothes){
    for (int i=0; i<ui->tableWidget_delivery_cloth->rowCount(); ++i) {
        if(Qt::Checked==ui->tableWidget_delivery_cloth->item(i, 0)->checkState()){
            *countClothes += ui->tableWidget_delivery_cloth->item(i, 6)->text().toInt();
        }
    }
}

void MainWindow::on_lineEdit_purchaseSearch_textChanged(const QString &arg1)
{
    setTableWidgetItemHidden(ui->tableWidget_delivery_cloth, arg1);
}
