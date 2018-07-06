#include "systemcenter.h"
#include "ui_systemcenter.h"
#include "sqltool.h"
#include "staff.h"
#include <QDebug>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QComboBox>




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
    ui->tableWidget_showStaffInfo->setRowCount(0);
    ui->tableWidget_showStaffInfo->setAlternatingRowColors(true);
    ui->tableWidget_showStaffInfo->verticalHeader()->setVisible(false);

    QVector<QStringList> staffInfo;
    Staff::Info(staffInfo);
    int i = 0;
    int n = staffInfo.size();
    ui->tableWidget_showStaffInfo->setRowCount(staffInfo.size());
    while (n) {
        ui->tableWidget_showStaffInfo->setItem(i, 0, new QTableWidgetItem(staffInfo.at(i).at(0)));
        ui->tableWidget_showStaffInfo->setItem(i, 1, new QTableWidgetItem(staffInfo.at(i).at(2)));
        ui->tableWidget_showStaffInfo->setItem(i, 2, new QTableWidgetItem(staffInfo.at(i).at(3)));
        ui->tableWidget_showStaffInfo->setItem(i, 3, new QTableWidgetItem(staffInfo.at(i).at(4)));
        ui->tableWidget_showStaffInfo->setItem(i, 4, new QTableWidgetItem(staffInfo.at(i).at(5)));
        i++;
        n--;
    }
    ui->tableWidget_showStaffInfo->setRowCount(i);
    progressBar();
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
    QStringList showStaffInfoHeader;
    showStaffInfoHeader << "用户名" << "姓名" << "性别" << "职位" << "邮箱";
    ui->tableWidget_showStaffInfo->clear();
    ui->tableWidget_showStaffInfo->setRowCount(0);
    ui->tableWidget_showStaffInfo->setHorizontalHeaderLabels(showStaffInfoHeader);
}


/**
 * search staff information
 *
 * @author Yihan Dong
 * @return information
 *
 * done
 */


void SystemCenter::on_pushButton_searchStaffInfo_clicked()
{
    QString searchAttribute, searchValue;
    QStringList staffInfo_1;
    QVector<QStringList> staffInfo_2;
    QStringList showStaffInfoHeader;
    showStaffInfoHeader << "用户名" << "姓名" << "性别" << "职位" << "邮箱";
    if(ui->comboBox_searchStaffChosen->currentText() == "username" ||
            ui->comboBox_searchStaffChosen->currentText() == "email"){

        searchAttribute = ui->comboBox_searchStaffChosen->currentText();
        searchValue = ui->lineEdit_searchStaffValue->text();
        Staff::Info(searchAttribute, searchValue, staffInfo_1);
        ui->tableWidget_showStaffInfo->clear();
        ui->tableWidget_showStaffInfo->setHorizontalHeaderLabels(showStaffInfoHeader);
        ui->tableWidget_showStaffInfo->setRowCount(1);
        ui->tableWidget_showStaffInfo->setAlternatingRowColors(true);
        ui->tableWidget_showStaffInfo->verticalHeader()->setVisible(false);
        ui->tableWidget_showStaffInfo->setItem(0, 0, new QTableWidgetItem(staffInfo_1.at(0)));
        ui->tableWidget_showStaffInfo->setItem(0, 1, new QTableWidgetItem(staffInfo_1.at(2)));
        ui->tableWidget_showStaffInfo->setItem(0, 2, new QTableWidgetItem(staffInfo_1.at(3)));
        ui->tableWidget_showStaffInfo->setItem(0, 3, new QTableWidgetItem(staffInfo_1.at(4)));
        ui->tableWidget_showStaffInfo->setItem(0, 4, new QTableWidgetItem(staffInfo_1.at(5)));
        progressBar();

    }else{
        searchAttribute = ui->comboBox_searchStaffChosen->currentText();
        searchValue = ui->lineEdit_searchStaffValue->text();
        Staff::Info(searchAttribute, searchValue, staffInfo_2);
        ui->tableWidget_showStaffInfo->clear();
        ui->tableWidget_showStaffInfo->setRowCount(0);
        ui->tableWidget_showStaffInfo->setHorizontalHeaderLabels(showStaffInfoHeader);
        ui->tableWidget_showStaffInfo->setAlternatingRowColors(true);
        ui->tableWidget_showStaffInfo->verticalHeader()->setVisible(false);
        ui->tableWidget_showStaffInfo->setRowCount(staffInfo_2.size());
        int i = 0;
        int n = staffInfo_2.size();
        while (n) {
            ui->tableWidget_showStaffInfo->setItem(i, 0, new QTableWidgetItem(staffInfo_2.at(i).at(0)));
            ui->tableWidget_showStaffInfo->setItem(i, 1, new QTableWidgetItem(staffInfo_2.at(i).at(2)));
            ui->tableWidget_showStaffInfo->setItem(i, 2, new QTableWidgetItem(staffInfo_2.at(i).at(3)));
            ui->tableWidget_showStaffInfo->setItem(i, 3, new QTableWidgetItem(staffInfo_2.at(i).at(4)));
            ui->tableWidget_showStaffInfo->setItem(i, 4, new QTableWidgetItem(staffInfo_2.at(i).at(5)));
            i++;
            n--;
        }
        ui->tableWidget_showStaffInfo->setRowCount(i);
        progressBar();
    }
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
    int rowIndex = ui->tableWidget_showStaffInfo->currentRow();
    QString username = ui->tableWidget_showStaffInfo->item(rowIndex, 0)->text();
    ui->tableWidget_showStaffInfo->removeRow(rowIndex);
    Staff::deleteStaffInfo(username);



}


