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
#include <QFileDialog>
#include <QByteArray>
#include <QDataStream>


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
    ui->tableWidget_updateShowStaffInfo->setRowCount(0);
    ui->label_updateShowUsername->clear();
    ui->lineEdit_updateStaffName->clear();
    ui->lineEdit_updateStaffEmail->clear();
    ui->label_showEditPortrait->clear();
    ui->label_showEditPortraitPath->clear();
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
    ui->comboBox_updateStaffGender->setCurrentText("          " + ui->tableWidget_updateShowStaffInfo->item(row, 2)->text());
    ui->comboBox_updateStaffPosition->setCurrentText("      " + ui->tableWidget_updateShowStaffInfo->item(row, 3)->text());
    ui->lineEdit_updateStaffEmail->setText(ui->tableWidget_updateShowStaffInfo->item(row, 4)->text());
    Q_UNUSED(column);
}



//老子写的
void SystemCenter::on_pushButton_addNewPortrait_2_clicked()
{
    QStringList picture = QFileDialog::getOpenFileNames(this, tr("open file"),
                                                        tr("图片文件(*png *jpg)"));
    if(picture.isEmpty()){
        return ;
    }

    QImage tempPortrait(picture.at(0));
    QPixmap portrait = QPixmap::fromImage(tempPortrait.scaled(92, 92, Qt::IgnoreAspectRatio));
    ui->label_showEditPortraitPath->setText(picture.at(0));
    ui->label_showEditPortrait->setPixmap(portrait);
    ui->label_showEditPortrait->show();
}



//老子写的
void SystemCenter::on_pushButton_changeStaffInfo_clicked()
{
    QString username = ui->label_updateShowUsername->text().trimmed();
    QString name = ui->lineEdit_updateStaffName->text().trimmed();
    QString gender = ui->comboBox_updateStaffGender->currentText().trimmed();
    QString position = ui->comboBox_updateStaffPosition->currentText().trimmed();
    QString email = ui->lineEdit_updateStaffEmail->text().trimmed();


    QString pic = username +".jpg";
    QString picPath = ui->label_showEditPortraitPath->text().trimmed();

    QBuffer buffer;
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    QImage img;

    if(username == "" || name == "" || gender == "" ||
            position == "" || email == ""){
        QMessageBox::warning(this,"警告", "\n请输入全部信息！",QMessageBox::Close);
        return ;
    }

    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "Confirm to edit this user ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        QStringList list;
        list.append("pp3_csi");
        list.append(username);
        list.append(name);
        list.append(gender);
        list.append(position);
        list.append(email);
        sendMessage(list);

        out.setVersion(QDataStream::Qt_5_7);
        buffer.open(QIODevice::ReadWrite);
        img.load(picPath);
        img.save(&buffer,"JPG");
        out << qint32(buffer.size());
        out << QString("/users/" + pic);
        out << buffer.data();

        m_socket->write(message);
        m_socket->flush();

        QFile file(DIR + QString("/users/") + pic);
        if (file.exists()){
            file.remove();
        }
    }
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
    ui->label_showEditPortrait->setText("Preview");
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

    if(email.trimmed() == "" || ui->lineEdit_updateStaffOldpassword->text().
            trimmed() == "" || ui->lineEdit_updateStaffNewpassword->text().
            trimmed() == "" || ui->lineEdit_updateStaffUsername->text().
            trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入全部信息！",QMessageBox::Close);
        return ;
    }
    list.append("pp4_csp");
    list.append(email);
    list.append(newPassword);
    list.append(newUsername);
    sendMessage(list);
}


//老子写的
void SystemCenter::on_pushButton_cancelStaffpasswordChange_clicked()
{
    ui->lineEdit_inputStaffEmail->clear();
    ui->lineEdit_updateStaffUsername->clear();
    ui->lineEdit_updateStaffOldpassword->clear();
    ui->lineEdit_updateStaffNewpassword->clear();
}


