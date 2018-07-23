#include "systemcenter.h"
#include "ui_systemcenter.h"
#include <QDebug>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QComboBox>
#include <QMessageBox>




/**
 * tableWidget_showStaffInfo show staff information
 *
 * @author Yihan Dong
 * @return void
 *
 * done
 */


void SystemCenter::on_pushButton_showStaff_clicked()
{
    QStringList list;
    list.append("pp1_ss");
    sendMessage(list);


    ui->tableWidget_showStaffInfo->setRowCount(0);
    ui->tableWidget_showStaffInfo->setAlternatingRowColors(true);
    ui->tableWidget_showStaffInfo->verticalHeader()->setVisible(false);
}


/**
 * clear tablewidget_showStaffInfo information
 *
 * @author Yihan Dong
 * @return void
 *
 * done
 */


void SystemCenter::on_pushButton_clearStaff_clicked()
{
    ui->tableWidget_showStaffInfo->setRowCount(0);
    ui->lineEdit_searchStaffValue->clear();
}


/**
 * search staff information
 *
 * @author Yihan Dong
 * @return information
 *
 * done
 */


void SystemCenter::on_pushButton_font_sellSearch_2_clicked()
{
    QStringList list;
    QString searchValue;
    searchValue = ui->lineEdit_searchStaffValue->text();

    if(searchValue.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }
    list.append("pp1_ssi");
    list.append(searchValue);
    sendMessage(list);

}


/**
 * delete staff information
 *
 * @author Yihan Dong
 * @return void
 *
 * undone
 */


void SystemCenter::on_pushButton_deleteStaffInfo_clicked()
{
    QStringList list;

    if(ui->tableWidget_showStaffInfo->currentItem() == NULL){
        QMessageBox::warning(this,"警告", "\n请选中一个员工！",QMessageBox::Close);
        return ;
    }

    int rowIndex = ui->tableWidget_showStaffInfo->currentRow();
    QString username = ui->tableWidget_showStaffInfo->item(rowIndex, 0)->text();


    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "Confirm to delete this staff ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        list.append("pp1_dsi");
        list.append(username);
        sendMessage(list);
        ui->tableWidget_showStaffInfo->removeRow(rowIndex);
    }

}


