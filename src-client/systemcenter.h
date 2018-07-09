#ifndef SYSTEMCENTER_H
#define SYSTEMCENTER_H

#include <QWidget>
#include <QFont>
#include <QTabBar>

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QFontDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QTime>
#include <QDateTime>
#include <QDate>
#include "garment.h"
#include <QCompleter>
#include <QStringListModel>
#include <QtNetwork>


namespace Ui {
class SystemCenter;
}

class SystemCenter : public QWidget
{
    Q_OBJECT

public:
    explicit SystemCenter(QWidget *parent = 0);
    ~SystemCenter();
    void getRoundPixmap(QPixmap* src,QSize size);
    void download(const QString &url, const QString &filePath);
    void transfer();


private slots:
    void sendMessage(QStringList);

    void readMessage();

    void showString(QString s1, QString s2, QString s3, QString s4, QString s5, QString s6);

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_B_clicked();

    void on_pushButton_C_clicked();

    void on_pushButton_D_clicked();

    void on_pushButton_A_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void warehouseEditComplete();

    void on_icon_search_clicked();

    void on_pushButton_7_clicked();

    void on_icon_search_C_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_cancelAddG_clicked();

    void on_pushButton_showGarment_clicked();

    void on_pushButton_clearGarment_clicked();

    void on_pushButton_setGPic_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_addGarment_clicked();

    void on_pushButton_8_clicked();

    void on_tableWidget_B_itemClicked(QTableWidgetItem *item);

    void on_pushButton_9_clicked();

    void replyFinished(QNetworkReply *reply);

    void on_pushButton_deleteGarment_clicked();

    void on_pushButton_ConfirmOrder_clicked();

    void on_pushButton_confirmAddG_clicked();

    void on_icon_search_B_clicked();


    void on_pushButton_cancelOrder_clicked();

    void on_pushButton_showStaff_clicked();

    void on_pushButton_clearStaff_clicked();

    void on_pushButton_searchStaffInfo_clicked();

    void on_pushButton_deleteStaffInfo_clicked();

    void on_pushButton_showProvider_clicked();

    void on_pushButton_clearProvider_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_switch_clicked();

    void on_lineEdit_addNewUsername_editingFinished();

    void on_lineEdit_repeatPassword_editingFinished();

    void on_lineEdit_addNewEmail_editingFinished();

    void on_pushButton_cancelNewStaff_clicked();

    void on_pushButton_showStores_clicked();

    void on_lineEdit_sell_search_textChanged(const QString &arg1);

    void on_tableWidget_stores_cellClicked(int row, int column);

    void on_pushButton_clearStores_clicked();

signals:
    void stringReturn(QString);

private:
    Ui::SystemCenter *ui;
    void progressBar_fast();
    void progressBar();
    void init_warehouse_C();

    void searchTableWidget(QTableWidget*, const QString&, QVector<int>&);
    void setTableWidgetItemHidden(QTableWidget*, const QString&);

    QNetworkAccessManager netManager;
    QString filepath;
    QTcpSocket *m_tcpsocket;

};


#endif // SYSTEMCENTER_H
