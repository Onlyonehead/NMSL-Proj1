#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>


/**
 * @brief MainWindow::setTableWidget_warehouse
 */
void MainWindow::setTableWidget_warehouse(){
    ui->tableWidget_warehouse->clearContents();

    ui->tableWidget_warehouse->verticalHeader()->setVisible(false); //设置表垂直头不可见
    ui->tableWidget_warehouse->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑,但是不会像设置Enable那样使界面变灰
    ui->tableWidget_warehouse->setRowCount(qv_stock.size());//设置行数，与搜索结果size相同
    ui->tableWidget_warehouse->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
    int i=0;//table的行坐标

    QVector<QVector<QString>>::iterator iter;
    QVector<QStringList>::iterator it_c;
    for(iter=qv_stock.begin(); iter!=qv_stock.end(); iter++) {

        //QStringList qsl = Store::getClothDetail(iter->at(0));
        for(it_c=qv_clothes.begin(); it_c!=qv_clothes.end(); ++it_c){
            if(iter->at(0)==it_c->at(0)){
                ui->tableWidget_warehouse->setItem(i,0,new QTableWidgetItem(iter->at(0)));
                ui->tableWidget_warehouse->setItem(i,1,new QTableWidgetItem(it_c->at(1)));
                ui->tableWidget_warehouse->setItem(i,2,new QTableWidgetItem(it_c->at(2)));
                ui->tableWidget_warehouse->setItem(i,3,new QTableWidgetItem(iter->at(1)));
                ui->tableWidget_warehouse->setItem(i,4,new QTableWidgetItem(it_c->at(4)));
                break;
            }
        }
        ++i;
    }
}

void MainWindow::on_tableWidget_warehouse_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    QVector<QStringList>::const_iterator it;
    QString path, style;
    for(it=qv_clothes.constBegin(); it!=qv_clothes.constEnd(); ++it){
        if(it->at(0)==ui->tableWidget_warehouse->item(row, 0)->text()){
            path = it->at(3);
            style = it->at(1)+" "+it->at(2);
        }
    }

    QPixmap *pixmap = new QPixmap(USER_DIR + path);
    if (pixmap->isNull()){
        download("http://39.108.155.50/project1/clothes/" + path, USER_DIR + path);
    }
    if (pixmap->isNull()){
        pixmap = new QPixmap(":/default.jpg");
    }
    ui->label_store_clothPic->setScaledContents(true);
    ui->label_store_clothPic->setPixmap(*pixmap);
    ui->label_store_clothStyle->setText(style);
}


