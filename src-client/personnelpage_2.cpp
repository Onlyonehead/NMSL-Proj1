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
 * check if username is existed
 *
 * @author Yihan Dong
*/


void SystemCenter::on_lineEdit_addNewUsername_editingFinished()
{
    QString username = ui->lineEdit_addNewUsername->text();
    if(Staff::isUsernameExisted(username)){
        ui->label_newStaffUsernameTip->setVisible(true);
        ui->lineEdit_addNewPassword->setEnabled(false);
        ui->lineEdit_repeatPassword->setEnabled(false);
        ui->lineEdit_addNewName->setEnabled(false);
        ui->lineEdit_addNewEmail->setEnabled(false);
        ui->pushButton_addNewPortrait->setEnabled(false);
        ui->pushButton_confirmNewStaff->setEnabled(false);
    }else {
        ui->label_newStaffUsernameTip->setVisible(false);
        ui->lineEdit_addNewPassword->setEnabled(true);
        ui->lineEdit_repeatPassword->setEnabled(true);
        ui->lineEdit_addNewName->setEnabled(true);
        ui->lineEdit_addNewEmail->setEnabled(true);
        ui->pushButton_addNewPortrait->setEnabled(true);
        ui->pushButton_confirmNewStaff->setEnabled(true);
    }

}

/**
 * check if repeated password is same as password
 *
 * @author Yihan Dong
 * @return void
*/



void SystemCenter::on_lineEdit_repeatPassword_editingFinished()
{
    QString repeatPassword = ui->lineEdit_repeatPassword->text();
    QString password = ui->lineEdit_addNewPassword->text();
    if(repeatPassword != password){
        ui->label_repeatPasswordTip->setVisible(true);
        ui->lineEdit_addNewName->setEnabled(false);
        ui->lineEdit_addNewEmail->setEnabled(false);
        ui->pushButton_addNewPortrait->setEnabled(false);
        ui->pushButton_confirmNewStaff->setEnabled(false);
    }else {
        ui->label_repeatPasswordTip->setVisible(false);
        ui->lineEdit_addNewName->setEnabled(true);
        ui->lineEdit_addNewEmail->setEnabled(true);
        ui->pushButton_addNewPortrait->setEnabled(true);
        ui->pushButton_confirmNewStaff->setEnabled(true);

    }
}

/**
 *check if email is existed
 *
 * @author Yihan Dong
 * @return void
*/



void SystemCenter::on_lineEdit_addNewEmail_editingFinished()
{
    QString email = ui->lineEdit_addNewEmail->text();
    if(Staff::isEmailExisted(email)){
        ui->label_newStaffEmailTip->setVisible(true);
        ui->pushButton_addNewPortrait->setEnabled(false);
        ui->pushButton_confirmNewStaff->setEnabled(false);
    }else {
        ui->label_newStaffEmailTip->setVisible(false);
        ui->pushButton_addNewPortrait->setEnabled(true);
        ui->pushButton_confirmNewStaff->setEnabled(true);
    }
}

/**
 * @brief SystemCenter::on_pushButton_cancelNewStaff_clicked
 * cancel add new staff
 * @author Yihan Dong
 * @return void
 */


void SystemCenter::on_pushButton_cancelNewStaff_clicked()
{
    ui->lineEdit_addNewUsername->clear();
    ui->lineEdit_addNewPassword->clear();
    ui->lineEdit_repeatPassword->clear();
    ui->lineEdit_addNewName->clear();
    ui->lineEdit_addNewEmail->clear();
    ui->label_showNewPortrait->clear();
}
