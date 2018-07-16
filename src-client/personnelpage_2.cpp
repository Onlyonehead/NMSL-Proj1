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
    QStringList list;
    list.append("pp2_ane");
    QString email = ui->lineEdit_addNewEmail->text();
    list.append(email);
    sendMessage(list);

}




/**
 * @brief SystemCenter::on_pushButton_addNewPortrait_clicked
 * add new staff portrait
 * @author Yihan Dong
 * @return void
 */
void SystemCenter::on_pushButton_addNewPortrait_clicked()
{
    QStringList picture = QFileDialog::getOpenFileNames(this, tr("open file"),
                                                        tr("图片文件(*png *jpg)"));
    if(picture.isEmpty()){
        return ;
    }

    QImage tempPortrait(picture.at(0));
    QPixmap portrait = QPixmap::fromImage(tempPortrait.scaled(142, 142, Qt::IgnoreAspectRatio));
    ui->label_showNewPortraitPath->setText(picture.at(0));
    ui->label_showNewPortrait->setPixmap(portrait);
    ui->label_showNewPortrait->show();

}


/**
 * @brief SystemCenter::on_pushButton_confirmNewStaff_clicked
 * confirm create new staff
 * @author Yihan Dong
 * @return void
 */
void SystemCenter::on_pushButton_confirmNewStaff_clicked()
{
    QString username;
    QString password;
    QString name;
    QString gender;
    QString position;
    QString email;
    QString pic;
    username = ui->lineEdit_addNewUsername->text().trimmed();
    password = ui->lineEdit_addNewPassword->text().trimmed();
    name = ui->lineEdit_addNewName->text().trimmed();
    gender = ui->comboBox_addNewGender->currentText().trimmed();
    position = ui->comboBox_addNewPosition->currentText().trimmed();
    email = ui->lineEdit_addNewEmail->text().trimmed();
    pic = username +".jpg";
    QString picPath = ui->label_showNewPortraitPath->text().trimmed();
    QBuffer buffer;
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    QImage img;

    if(username == "" || password == "" || name == "" || gender == "" ||
            position == "" || email == "" || picPath == ""){
        QMessageBox::warning(this,"警告", "\n请输入全部信息！",QMessageBox::Close);
        return ;
    }

    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "Confirm to add this user ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        QStringList list;
        list.append("pp2_cns");

        list.append(username);
        list.append(password);
        list.append(name);
        list.append(gender);
        list.append(position);
        list.append(email);
        list.append(pic);
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

