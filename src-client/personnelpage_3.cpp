#include "systemcenter.h"
#include "ui_systemcenter.h"
#include "sqltool.h"
#include <QDebug>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QComboBox>
#include <QMessageBox>







/**
 * @brief SystemCenter::on_pushButton_updatePageShowStaff_clicked
 * personnel page 3 show staff info
 */
void SystemCenter::on_pushButton_updatePageShowStaff_clicked()
{
    QStringList list;
    list.append("pp3_upss");
    sendMessage(list);
}


/**
 * @brief SystemCenter::on_pushButton_updatePageClearStaff_clicked
 * clear staff information table
 */
void SystemCenter::on_pushButton_updatePageClearStaff_clicked()
{
    ui->tableWidget_updateShowStaffInfo->clear();
    QStringList header;
    header << tr("用户名") << tr("姓名") << tr("性别") << tr("职位") << tr("邮箱");
    ui->tableWidget_updateShowStaffInfo->setHorizontalHeaderLabels(header);
}




/**
 * @brief SystemCenter::on_tableWidget_updateShowStaffInfo_cellClicked
 * @param row
 * @param column
 * show provider current information
 * @author Yihan Dong
 */
void SystemCenter::on_tableWidget_updateShowStaffInfo_cellClicked(int row, int column)
{
    ui->label_updateShowUsername->setText(ui->tableWidget_updateShowStaffInfo->item(row, 0)->text());
    ui->lineEdit_updateStaffName->setText(ui->tableWidget_updateShowStaffInfo->item(row, 1)->text());
    ui->comboBox_updateStaffGender->setCurrentText(ui->tableWidget_updateShowStaffInfo->item(row, 2)->text());
    ui->comboBox_updateStaffPosition->setCurrentText(ui->tableWidget_updateShowStaffInfo->item(row, 3)->text());
    ui->lineEdit_updateStaffEmail->setText(ui->tableWidget_updateShowStaffInfo->item(row, 4)->text());
    Q_UNUSED(column);
}




/**
 * @brief SystemCenter::on_pushButton_changeStaffInfo_clicked
 * update staff information
 * @author Yihan Dong
 */
void SystemCenter::on_pushButton_changeStaffInfo_clicked()
{
    QStringList list;
    QString username = ui->label_updateShowUsername->text();
    QString name = ui->lineEdit_updateStaffName->text();
    QString gender = ui->comboBox_updateStaffGender->currentText();
    QString position = ui->comboBox_updateStaffPosition->currentText();
    QString email = ui->lineEdit_updateStaffEmail->text();
    list.append("pp3_csi");
    list.append(username);
    list.append(name);
    list.append(gender);
    list.append(position);
    list.append(email);
    sendMessage(list);
}


/**
 * @brief SystemCenter::on_pushButton_cancelStaffInfoChange_clicked
 * clear update information
 * @author Yihan Dong
 */
void SystemCenter::on_pushButton_cancelStaffInfoChange_clicked()
{
    ui->label_updateShowUsername->clear();
    ui->lineEdit_updateStaffName->clear();
    ui->lineEdit_updateStaffEmail->clear();
}


/**
 * @brief SystemCenter::on_lineEdit_inputStaffEmail_editingFinished
 * check if the email exists
 * @author Yihan Dong
 */
void SystemCenter::on_lineEdit_inputStaffEmail_editingFinished()
{
    QStringList list;
    QString email = ui->lineEdit_inputStaffEmail->text();
    list.append("pp4_ise");
    list.append(email);
    sendMessage(list);
}

/**
 * @brief SystemCenter::on_lineEdit_updateStaffOldpassword_editingFinished
 * check if old password right
 * @author Yihan Dong
 */
void SystemCenter::on_lineEdit_updateStaffOldpassword_editingFinished()
{
    QStringList list;
    QString email = ui->lineEdit_inputStaffEmail->text();
    QString oldPassword = ui->lineEdit_updateStaffOldpassword->text();
    list.append("pp4_cop");
    list.append(email);
    list.append(oldPassword);
    sendMessage(list);
}



/**
 * @brief SystemCenter::on_pushButton_changeStaffpassword_clicked
 * change staff password & username
 */
void SystemCenter::on_pushButton_changeStaffpassword_clicked()
{
    QStringList list;
    QString email = ui->lineEdit_inputStaffEmail->text();
    QString newPassword = ui->lineEdit_updateStaffNewpassword->text();
    QString newUsername = ui->lineEdit_updateStaffUsername->text();
    list.append("pp4_csp");
    list.append(email);
    list.append(newPassword);
    list.append(newUsername);
    sendMessage(list);
}



