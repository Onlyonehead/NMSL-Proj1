#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "store.h"
#include "sqltool.h"
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
    for(iter=qv_stock.begin(); iter!=qv_stock.end(); iter++) {
        QApplication::processEvents();
        QSqlQuery sq_cloth;
        SQLTool::search(sq_cloth, "clothes", "ID", iter->at(0));
        sq_cloth.next();
        ui->tableWidget_warehouse->setItem(i,0,new QTableWidgetItem(sq_cloth.value(0).toString()));
        ui->tableWidget_warehouse->setItem(i,1,new QTableWidgetItem(sq_cloth.value(1).toString()));
        ui->tableWidget_warehouse->setItem(i,2,new QTableWidgetItem(sq_cloth.value(2).toString()));
        ui->tableWidget_warehouse->setItem(i,3,new QTableWidgetItem(iter->at(1)));
        ui->tableWidget_warehouse->setItem(i,4,new QTableWidgetItem(sq_cloth.value(4).toString()));
        ++i;
    }
}

void MainWindow::on_tableWidget_warehouse_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    QString path = Store::getPicPath(ui->tableWidget_warehouse->item(row, 0)->text());

    QPixmap *pixmap = new QPixmap("./" + path);
    if (pixmap->isNull()){
        download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
    }
    if (pixmap->isNull()){
        pixmap = new QPixmap(":/default.jpg");
    }

    ui->label_store_clothPic->setScaledContents(true);
    ui->label_store_clothPic->setPixmap(*pixmap);
    ui->label_store_clothStyle->setText(ui->tableWidget_warehouse->item(row, 1)->text());//直接从表格获取style值
}


