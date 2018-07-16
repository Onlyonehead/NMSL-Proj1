#ifndef HOME_H
#define HOME_H

#include <QWidget>
#include <QtNetwork>

#define LOGIN_DIR "/Users/Haibara/Documents/qt build files/Clientfiles/pwd.data"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void showString(QString s);

    void sendMessage(QStringList);

    void readMessage();


signals:
    void stringReturn1(QString, QString, QString, QString, QString, QString);
    void stringReturn2(QString, QString, QString, QString, QString, QString);
    void send_pic_num(int);



private:
    Ui::Login *ui;
    bool isBanned;
    QTcpSocket *m_tcpsocket;
    QTcpSocket *m_socket;

    //check pwd.data and auto save password to file
    int checkpass(QString, QString, bool);

    //tool method
    void sendSignalForLogin(QString);

    int pic_num;
};

#endif // HOME_H
