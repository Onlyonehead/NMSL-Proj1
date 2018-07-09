#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "forgetpassword.h"

#include <QDebug>
#include <QBitmap>
#include <QPainter>
#include <QMessageBox>
#include <systemcenter.h>
#include <QFontDatabase>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDateTime>
#include <QTime>
#include <QDate>


/**
 * Login UI initialize
 *
 * @author Zicun Hang
 */
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    m_tcpsocket = new QTcpSocket(this);
    m_tcpsocket->abort();
    m_tcpsocket->connectToHost(QHostAddress::LocalHost,8848);//设置客户端的端口号
    connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage()));//用于接受数据


    this->setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("QFrame{border-radius:10px;}");

    connect(ui->lineEdit_2, SIGNAL(returnPressed()), ui->pushButton_2, SIGNAL(clicked()), Qt::UniqueConnection);
    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->pushButton_2, SIGNAL(clicked()), Qt::UniqueConnection);


    int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies.at(0));
    font.setPointSize(20);
    ui->pushButton_3->setFont(font);
    ui->pushButton_3->setText(QChar(0xf13e));
    ui->pushButton_3->setStyleSheet("QPushButton{border: 0px; color: rgb(120, 120, 120);} "
                                    "QPushButton:hover{border: 0px; color: rgba(15, 128, 255, 190);} ");

    ui->lineEdit->setFocus();

    QFile file(LOGIN_DIR);
    if(file.open(QIODevice::ReadOnly)){
        QString tmp_username, tmp_password;
        tmp_username = file.readLine().trimmed();
        tmp_password = file.readLine().trimmed();
        ui->lineEdit->setText(tmp_username);
        ui->lineEdit_2->setText("******");
        ui->lineEdit_2->setTextMargins(13,0,10,0);
        ui->label_pass->setText(tmp_password);
        ui->checkBox->setChecked(true);
    }
    file.close();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    pic_num = 1 + qrand() % (12 - 1);
    ui->titlepic->setStyleSheet("QFrame{border-image:url(:/background"+ QString::number(pic_num) +");border: 8px solid rgb(128, 128, 128);}");


}

/**
 * Login UI destory
 *
 * @author Zicun Hang
 */
Login::~Login()
{

    delete ui;

    qDebug() << "Destory : login" << endl;

}

/**
 * on_pushButton_clicked()
 *
 * @author Zicun Hang
 */
void Login::on_pushButton_clicked()
{
    this->close();
}

/**
 * on_pushButton_2_clicked()
 *
 * @author Zicun Hang
 */
void Login::on_pushButton_2_clicked()
{
    QString username = ui->lineEdit->text().trimmed();
    QString password = (ui->lineEdit_2->text() == "******") ?
                ui->label_pass->text() : ui->lineEdit_2->text();
    QFile file(LOGIN_DIR);
    if(file.open(QIODevice::ReadOnly)){
        QString tmp_username, tmp_password;
        tmp_username = file.readLine().trimmed();
        tmp_password = file.readLine().trimmed();
        if(tmp_username != username){
            file.remove();
            if(tmp_password == password){
                ui->lineEdit_2->clear();
                QMessageBox::warning(this,"警告", "\n请重新输入密码！",QMessageBox::Close);
                return ;
            }
        }

    }
    file.close();

    QStringList list;
    list.append("login");
    list.append(username);
    list.append(password);
    sendMessage(list);


}


/**
 * tool method
 *
 * @author Zicun Hang
 * @param username username
 */
void Login::sendSignalForLogin(QString username){
    QStringList list;
    list.append("info");
    list.append(username);
    sendMessage(list);
}




/**
 * on_pushButton_3_clicked
 *
 * @author Zicun Hang
 */
void Login::on_pushButton_3_clicked()
{
    ForgetPassword *fp = new ForgetPassword;
    connect(this, SIGNAL(send_pic_num(int)), fp, SLOT(init_pic(int)));
    emit send_pic_num(pic_num);
    this->close();
}

/**
 * slot method
 *
 * @author Zicun Hang
 */
void Login::showString(QString s){
    QApplication::processEvents();
    Login *lg = new Login;
    lg->ui->lineEdit->setText(s);
    lg->ui->lineEdit_2->setFocus();
    lg->show();
}

/**
 * check pwd.data and auto save password to file
 *
 * @author Zicun Hang
 * @param username username
 * @param passwordEntered password entered by user
 * @param status check status of checkbox
 */
int Login::checkpass(QString username, QString passwordEntered, bool status){
    if(status){
        QFile *file = new QFile(LOGIN_DIR);
        if(!file->exists()){
            if (file->open(QFile::ReadWrite | QFile::Text)){
                QByteArray bytePwd = passwordEntered.toLatin1();
                QByteArray bytePwdMd5 = QCryptographicHash::hash(bytePwd, QCryptographicHash::Md5);
                QString strPwdMd5 = bytePwdMd5.toHex();
                QTextStream out(file);
                out << username << "\n";
                out << strPwdMd5;
            }else{
                qDebug()<<"打开失败";
                return -1;
            }
        }
        file->close();
    }else{
        QFile file(LOGIN_DIR);
        if (file.exists()){
            file.remove();
        }
        file.close();
    }
    return 0;

}


void Login::sendMessage(QStringList list)
{

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << list;
    m_tcpsocket->write(message);
}

void Login::readMessage()
{
    QDataStream in(m_tcpsocket);
    in.setVersion(QDataStream::Qt_5_7);
    QString from;
    in >> from;
    qDebug() << from << endl;

    if(from == "login"){

        int status;
        in >> status;


        QString username = ui->lineEdit->text().trimmed();
        QString password = (ui->lineEdit_2->text() == "******") ?
                    ui->label_pass->text() : ui->lineEdit_2->text();
        bool isChecked = ui->checkBox->isChecked();

        if(status == 0){
            status = checkpass(username, password, isChecked);
        }

        switch(status){
            case -1:
                QMessageBox::warning(this,"警告", "\n保存密码失败！",QMessageBox::Close);
                break;
            case -2:
                QMessageBox::warning(this,"警告", "\n请输入用户名！",QMessageBox::Close);
                break;
            case -3:
                QMessageBox::warning(this,"警告", "\n请输入密码！",QMessageBox::Close);
                break;
            case -4:
                QMessageBox::warning(this,"警告", "\n请稍后再试。", QMessageBox::Close);
                break;
            case -5:
                QMessageBox::warning(this,"警告", "\n密码错误！\n剩余次数：0 次。\n请5分钟后再试。",QMessageBox::Close);
                break;
            case -6:
                QMessageBox::warning(this,"警告", "\n密码错误！\n剩余次数：1 次。",QMessageBox::Close);
                break;
            case -7:
                QMessageBox::warning(this,"警告", "\n密码错误！\n剩余次数：2 次。",QMessageBox::Close);
                break;
            case -8:
                QMessageBox::warning(this,"警告", "\n找不到该用户！",QMessageBox::Close);
                break;
            case 0:
                sendSignalForLogin(username);
                break;
        }
    }
    if(from == "info"){

        QStringList list;
        in >> list;

        if(list.at(2) == "管理员"){
            QApplication::processEvents();
            SystemCenter *sc = new SystemCenter;
            connect(this, SIGNAL(stringReturn1(QString, QString, QString, QString, QString, QString)),
                    sc, SLOT(showString(QString, QString, QString, QString, QString, QString)));
            emit stringReturn1(list.at(0),list.at(1),list.at(2),list.at(3),list.at(4),list.at(5));
        }
        if(list.at(2) == "门店人员"){
            QApplication::processEvents();
            MainWindow *m = new MainWindow;
            connect(this, SIGNAL(stringReturn2(QString, QString, QString, QString, QString, QString)),
                    m, SLOT(showString(QString, QString, QString, QString, QString, QString)));
            emit stringReturn2(list.at(0),list.at(1),list.at(2),list.at(3),list.at(4),list.at(5));
        }

        this->close();
    }
}
