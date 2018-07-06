#include "forgetpassword.h"
#include "ui_forgetpassword.h"
#include "login.h"
#include <QDebug>
#include <QMessageBox>
#include "time.h"


/**
 * ForgetPassword UI initialize
 *
 * @author Zicun Hang
 */
ForgetPassword::ForgetPassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgetPassword)
{
    ui->setupUi(this);

    m_tcpsocket = new QTcpSocket(this);
    m_tcpsocket->abort();
    m_tcpsocket->connectToHost(QHostAddress::LocalHost,8848);//设置客户端的端口号
    connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage()));//用于接受数据

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("QFrame{border-radius:10px;}");
    connect(ui->lineEdit_2, SIGNAL(returnPressed()), ui->pushButton_2, SIGNAL(clicked()), Qt::UniqueConnection);
    connect(ui->lineEdit_5, SIGNAL(returnPressed()), ui->pushButton_3, SIGNAL(clicked()), Qt::UniqueConnection);
}

/**
 * ForgetPassword UI destory
 *
 * @author Zicun Hang
 */
ForgetPassword::~ForgetPassword()
{
    delete ui;
}

/**
 * on_pushButton_clicked
 *
 * @author Zicun Hang
 */
void ForgetPassword::on_pushButton_clicked()
{
    Login *lg = new Login;
    this->close();
    lg->show();
}

/**
 * initialize title picture
 *
 * @author Zicun Hang
 * @param i number of picture
 */
void ForgetPassword::init_pic(int i){
    this->show();

    ui->titlepic->setStyleSheet("QFrame{border-image:url(:/background"+ QString::number(i) +");border: 8px solid rgb(128, 128, 128);}");
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    this->securityCode = 111111 + qrand() % (999999 - 111111);
    qDebug() << securityCode << endl;
}

/**
 * on_pushButton_2_clicked
 *
 * @author Zicun Hang
 */
void ForgetPassword::on_pushButton_2_clicked()
{
    QStringList list;
    list.append("send");
    list.append(ui->lineEdit->text().trimmed());
    list.append(ui->lineEdit_2->text().trimmed());
    list.append(QString::number(this->securityCode));
    sendMessage(list);


}

/**
 * on_pushButton_3_clicked
 *
 * @author Zicun Hang
 */
void ForgetPassword::on_pushButton_3_clicked()
{


    QStringList list;
    list.append("check");
    list.append(this->username);
    list.append(ui->lineEdit_3->text().trimmed());
    list.append(ui->lineEdit_4->text());
    list.append(ui->lineEdit_5->text());
    list.append(QString::number(this->securityCode));
    sendMessage(list);
}

void ForgetPassword::sendMessage(QStringList list)
{

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << list;
    m_tcpsocket->write(message);
}

void ForgetPassword::readMessage()
{
    QDataStream in(m_tcpsocket);
    in.setVersion(QDataStream::Qt_5_7);
    QString from;
    in >> from;
    qDebug() << from << endl;

    if(from == "send"){
        int status;
        in >> status;
        switch(status){
            case 0:
                QMessageBox::information(this,"提示", "\n发送成功\n请在下方输入验证码",QMessageBox::Ok);
                this->username = ui->lineEdit->text();
                break;
            case -1:
                QMessageBox::warning(this,"警告", "\n请输入用户名和邮箱",QMessageBox::Close);
                break;
            case -2:
                QMessageBox::warning(this,"警告", "\n用户名和邮箱不匹配！",QMessageBox::Close);
                break;
            case -3:
                QMessageBox::warning(this,"警告", "\n找不到该用户！",QMessageBox::Close);
                break;
            case -4:
                QMessageBox::warning(this,"警告", "\n发送失败\n请重新尝试",QMessageBox::Close);
                break;
        }

    }
    if(from == "check"){

        int status;

        in >> status;
        QFile file(LOGIN_DIR);
        switch(status){
            case 0:
                QMessageBox::information(this,"提示", "\n密码修改成功",QMessageBox::Ok);
                if (file.exists()){
                    file.remove();
                }
                file.close();
                on_pushButton_clicked();
                break;
            case -1:
                QMessageBox::warning(this,"警告", "\n请输入密码",QMessageBox::Close);
                break;
            case -2:
                QMessageBox::warning(this,"警告", "\n验证码错误",QMessageBox::Close);
                break;
            case -3:
                QMessageBox::warning(this,"警告", "\n两次密码不相同",QMessageBox::Close);
                break;
        }
    }
}

