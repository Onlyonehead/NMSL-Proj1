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
 * check if username is existed
 *
 * @author Yihan Dong
*/


void SystemCenter::on_lineEdit_addNewUsername_editingFinished()
{
    QStringList list;
    list.append("pp2_anu");
    QString username = ui->lineEdit_addNewUsername->text();
    list.append(username);
    sendMessage(list);

}

/**
 * check if repeated password is same as password
 *
 * @author Yihan Dong
 * @return void
*/



void SystemCenter::on_lineEdit_repeatPassword_editingFinished()
{
    QStringList list;
    QString repeatPassword = ui->lineEdit_repeatPassword->text();
    QString password = ui->lineEdit_addNewPassword->text();
    list.append("pp2_rp");
    list.append(password);
    list.append(repeatPassword);

}

/**
 *check if email is existed
 *
 * @author Yihan Dong
 * @return void
*/



void SystemCenter::on_lineEdit_addNewEmail_editingFinished()
{
    QStringList list;
    list.append("pp2_ane");
    QString email = ui->lineEdit_addNewEmail->text();
    list.append(email);
    sendMessage(list);

}

/**
 * @brief SystemCenter::on_pushButton_confirmNewStaff_clicked
 * confirm create new staff
 * @author Yihan Dong
 * @return void
 */
void SystemCenter::on_pushButton_confirmNewStaff_clicked()
{
    QMessageBox msgbox;
    msgbox.setText(tr("员工信息已生成"));
    msgbox.setInformativeText(tr("确认员工信息并保存吗？"));
    msgbox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Save);
    QStringList list;
    QString username;
    QString password;
    QString name;
    QString gender;
    QString position;
    QString email;
    QString pic;
    int ret = msgbox.exec();
    switch (ret) {
    case QMessageBox::Save:
        list.append("pp2_cns");
        username = ui->lineEdit_addNewUsername->text();
        password = ui->lineEdit_addNewPassword->text();
        name = ui->lineEdit_addNewName->text();
        gender = ui->comboBox_addNewGender->currentText();
        position = ui->comboBox_addNewPosition->currentText();
        email = ui->lineEdit_addNewEmail->text();
        pic = ui->label_showNewPortraitName->text();
        list.append(username);
        list.append(password);
        list.append(name);
        list.append(gender);
        list.append(position);
        list.append(email);
        list.append(pic);
        sendMessage(list);
        break;
    case QMessageBox::Cancel:
        break;
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
