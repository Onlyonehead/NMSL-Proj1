#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetPassword(QWidget *parent = 0);
    ~ForgetPassword();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void init_pic(int);

    void sendMessage(QStringList);

    void readMessage();

private:
    Ui::ForgetPassword *ui;
    QTcpSocket *m_tcpsocket;
    int securityCode;
    QString username;

};

#endif // FORGETPASSWORD_H
