#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "store.h"
#include "sqltool.h"
#include <QVector>
#include <QProgressDialog>




/**
 * @brief MainWindow::setTableWidget_sellGoods
 */
void MainWindow::setTableWidget_sellGoods(){
    //初始化
    ui->tableWidget_sellGoods->clearContents();
    sellSignal = false;
    ui->label_sell_totalCount->setText(QString::number(0, 10));
    ui->label_sell_totalPrice->setText(QString::number(0.0));

    ui->tableWidget_sellGoods->verticalHeader()->setVisible(false); //设置表垂直头不可见
    //ui->tableWidget_sellGoods->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑,但是不会像设置Enable那样使界面变灰
    ui->tableWidget_sellGoods->setRowCount(qv_stock.size());//设置行数，与搜索结果size相同
    ui->tableWidget_sellGoods->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
    int i=0;//table的行坐标

    QVector<QVector<QString>>::iterator iter;
    for(iter=qv_stock.begin(); iter!=qv_stock.end(); iter++) {
        QApplication::processEvents();
        QSqlQuery sq_cloth;
        SQLTool::search(sq_cloth, "clothes", "ID", iter->at(0));
        sq_cloth.next();

        //从左到右 check id style size quantity price
        //插入复选框
        QTableWidgetItem *check = new QTableWidgetItem();
        check->setCheckState(Qt::Unchecked);
        ui->tableWidget_sellGoods->setItem(i,0,check);

        ui->tableWidget_sellGoods->setItem(i,1,new QTableWidgetItem(sq_cloth.value(0).toString()));
        ui->tableWidget_sellGoods->setItem(i,2,new QTableWidgetItem(QIcon(":/new/prefix1/"+sq_cloth.value(3).toString()), sq_cloth.value(1).toString()));
        ui->tableWidget_sellGoods->setItem(i,3,new QTableWidgetItem(sq_cloth.value(2).toString()));
        ui->tableWidget_sellGoods->setItem(i,4,new QTableWidgetItem(iter->at(1)));
        ui->tableWidget_sellGoods->setItem(i,5,new QTableWidgetItem(sq_cloth.value(4).toString()));
        ui->tableWidget_sellGoods->setItem(i,6,new QTableWidgetItem("0"));

        if(0==iter->at(1).toInt())
            ui->tableWidget_sellGoods->item(i, 0)->setFlags(Qt::NoItemFlags);
        ui->tableWidget_sellGoods->item(i, 1)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_sellGoods->item(i, 2)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_sellGoods->item(i, 3)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_sellGoods->item(i, 4)->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget_sellGoods->item(i, 5)->setFlags(Qt::ItemIsEnabled);
        ++i;
    }
    sellSignal = true;
}

void MainWindow::on_pushButton_sell_clicked()
{
    if("0"!=ui->label_sell_totalCount->text()){
        QString message = "交易总额为"+ui->label_sell_totalPrice->text()+"，共有"+ui->label_sell_totalCount->text()+"件服装。";
        if(QMessageBox::Yes==QMessageBox::question(this, tr("交易确认"), message, QMessageBox::Yes, QMessageBox::No)) {

            //交易进度条
            QProgressDialog dialog(tr("交易进度"), tr("取消"), 0, 100, this);
            dialog.setWindowTitle(tr("交易进行中"));
            dialog.setWindowModality(Qt::WindowModal);
            dialog.show();

            //存入服装Id和数量信息
            QVector<int> qv;
            for (int i=0; i<ui->tableWidget_sellGoods->rowCount(); ++i) {
                if(Qt::Checked==ui->tableWidget_sellGoods->item(i, 0)->checkState()){
                    qv<<ui->tableWidget_sellGoods->item(i, 1)->text().toInt()<<ui->tableWidget_sellGoods->item(i, 6)->text().toInt();
                }
            }
            if(Store::sellGoods(storeId, ui->label_sell_totalPrice->text().toDouble(), qv)){
                qDebug()<<"交易成功";
                dialog.setValue(10);

                QApplication::processEvents();
                Store::getRecord(storeId, record_size, qv_record);//重新获取交易记录
                dialog.setValue(40);

                QApplication::processEvents();
                Store::getStock(storeId, qv_stock);//重新获取库存
                dialog.setValue(70);

                QApplication::processEvents();
                setTableWidget_sellGoods();//刷新页面
                dialog.setValue(100);
            } else{
                qDebug()<<"交易失败";
            }

        } else {
            qDebug()<<"放弃";
        }
    }
}

void MainWindow::on_tableWidget_sellGoods_cellChanged(int row, int column)
{
    if(sellSignal){

        //CheckBox状态改变
        if(0==column){
            if(Qt::Unchecked==ui->tableWidget_sellGoods->item(row, 0)->checkState()&&ui->tableWidget_sellGoods->item(row, 6)->text()!="0"){
                ui->tableWidget_sellGoods->item(row, 6)->setText(QString::number(0, 10));
                int amount=0;
                double price=0;
                sellCount(&amount, &price);
                ui->label_sell_totalCount->setText(QString::number(amount, 10));
                ui->label_sell_totalPrice->setText(QString::number(price));
            }
        }

        //数量被修改
        if(6==column){
            if(Qt::Checked==ui->tableWidget_sellGoods->item(row, 0)->checkState()){
                int max_amount = ui->tableWidget_sellGoods->item(row, 4)->text().toInt();
                int sell_amount = ui->tableWidget_sellGoods->item(row, column)->text().toInt();
                if(sell_amount>max_amount)
                    ui->tableWidget_sellGoods->item(row, column)->setText(QString::number(max_amount, 10));
            } else {
                ui->tableWidget_sellGoods->item(row, column)->setText(QString::number(0, 10));
            }

            int amount=0;
            double price=0;
            sellCount(&amount, &price);
            ui->label_sell_totalCount->setText(QString::number(amount, 10));
            ui->label_sell_totalPrice->setText(QString::number(price));
        }
    }
}

void MainWindow::sellCount(int *countClothes, double *countPrices){
    for (int i=0; i<ui->tableWidget_sellGoods->rowCount(); ++i) {
        if(Qt::Checked==ui->tableWidget_sellGoods->item(i, 0)->checkState()){
            *countClothes += ui->tableWidget_sellGoods->item(i, 6)->text().toInt();
            *countPrices += ui->tableWidget_sellGoods->item(i, 5)->text().toDouble()*ui->tableWidget_sellGoods->item(i, 6)->text().toInt();
        }
    }
}

void MainWindow::on_lineEdit_sellSearch_textChanged(const QString &arg1)
{
    setTableWidgetItemHidden(ui->tableWidget_sellGoods, arg1);
}
