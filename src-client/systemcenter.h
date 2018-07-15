#ifndef SYSTEMCENTER_H
#define SYSTEMCENTER_H

#define USER_DIR "/Users/Haibara/Documents/qt build files/Userfiles/"

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
#include "tool.h"
#include "qtmap.h"
#include "ui_qtmap.h"
#include <QDesktopWidget>


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

    void on_pushButton_setGPic_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_addGarment_clicked();

    void on_pushButton_8_clicked();

    void on_tableWidget_B_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_D1_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_D2_itemClicked(QTableWidgetItem *item);

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

    void on_clearGarment_clicked();

    void on_pushButton_updateProviderInfo_clicked();

    void timer_deal_slot_function();

    void on_tableWidget_providerInfo_cellClicked(int row, int column);

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_clothes_ADD_clicked();

    void on_order_send_clicked();

    void on_icon_search_D_clicked();

    void on_w_search_A_clicked();

    void on_tableWidget_A_itemClicked(QTableWidgetItem *item);

    void on_w_search_A_3_clicked();

    void on_pushButton_showRequests_clicked();

    void on_tableWidget_check_cellClicked(int row, int column);

    void on_tableWidget_checkDetail_cellClicked(int row, int column);

    void on_pushButton_change_clicked();

    void on_pushButton_clearRequests_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_tableWidget_logistics_A_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_logistics_B_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_logistics_C_itemClicked(QTableWidgetItem *item);

    void on_style_change_clicked();

    void on_logistics_ADD_clicked();

    void on_logistics_send_clicked();

    void on_pushButton_commit_clicked();

    void on_pushButton_reject_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_tableWidget_logistics_2A_itemClicked(QTableWidgetItem *item);

    void on_pushButton_18_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_27_clicked();

    void finishedSlot(QNetworkReply*);

    void on_pushButton_30_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_23_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void finishedSlotForEdit(QNetworkReply* reply);

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_19_clicked();

    void on_tableWidget_logistics_C1_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_logistics_C2_itemClicked(QTableWidgetItem *item);

    void on_pushButton_add1_clicked();

    void on_pushButton_add2_clicked();

    void on_pushButton_add3_clicked();

    void on_pushButton_showRoute_clicked();
	
	void on_pushButton_deliverCancelChoose_clicked();

    void on_pushButton_deliverShowProvider_clicked();

    void on_pushButton_deliverOrder_clicked();

    void on_tableWidget_deliverProvider_cellClicked(int row, int column);

    void on_pushButton_addProviderInfo_clicked();

    void on_pushButton_confirmNewStaff_clicked();

    void on_pushButton_addNewPortrait_clicked();

    void on_pushButton_updatePageShowStaff_clicked();

    void on_pushButton_updatePageClearStaff_clicked();

    void on_tableWidget_updateShowStaffInfo_cellClicked(int row, int column);

    void on_pushButton_changeStaffInfo_clicked();

    void on_pushButton_cancelStaffInfoChange_clicked();

    void on_lineEdit_inputStaffEmail_editingFinished();

    void on_lineEdit_updateStaffOldpassword_editingFinished();

    void on_pushButton_changeStaffpassword_clicked();

    void on_tableWidget_generateOrder_itemClicked(QTableWidgetItem *item);

signals:
    void stringReturn(QString);

    void webReturn(QVector<QStringList>);

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
	QTcpSocket *m_socket;

    // For transfer
    QVector<QStringList> stock;
    QVector<QStringList> arriving;
    QVector<QStringList> clothes;
    QVector<QStringList> warehouse;
    QVector<QStringList> stores;
    QMap<QString,QMap<QString, QString>> stock_map;
    QMap<QString, QMap<QString, QStringList>> arriving_map;
    QMap<QString, QString> warehouse_map;

    int count_dealt;
    int count_ongoing;
    int count_rejected;

    QVector<QStringList> orderList; // For logistic A
    QVector<QStringList> wh_history; // For warehouse A
    QStringList wh_info_warehouse; // For warehouse A

    QMap<QString, QMap<QString, QString>> replenishment; // For logistics A
    QString wh_id; // For logistics A
    QString order_id; // For logistics A
    QStringList wh_info; // For logistics A
    QString order_time; // For logistics A

    QVector<QStringList> orderCheckedList; // For logistic B
    QString orderCheckedId; // For logistic B

    QStringList siteSelected; // For logistic C

    QStringList siteFrom; // For logistic C
    QStringList siteTo; // For logistic C
    QVector<QStringList> siteVia; // For logistic C

    QStringList current_selected; // For purchasepage

    bool style;

    QVector<QStringList> qv_requests;

};


#endif // SYSTEMCENTER_H
