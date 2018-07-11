#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QVector>
#include "systemcenter.h"
#include "record.h"
#include <QtNetwork>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool eventFilter(QObject *watched, QEvent *event);
    void download(const QString &url, const QString &filePath);

private slots:
    void windowClose();
    void removeSubTab(int index);
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_shop_clicked();

    void on_pushButton_user_clicked();

    void showString(QString s1, QString s2, QString s3, QString s4, QString s5, QString s6);

    void on_tableWidget_warehouse_cellClicked(int row, int column);

    void on_pushButton_sell_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tableWidget_sellGoods_cellChanged(int row, int column);

    void replyFinished(QNetworkReply *reply);

    void on_lineEdit_sellSearch_textChanged(const QString &arg1);

    void on_pushButton_purchase_clicked();

    void on_pushButton_message_clicked();

    void on_tableWidget_delivery_cloth_cellChanged(int row, int column);

    void on_lineEdit_purchaseSearch_textChanged(const QString &arg1);

    void on_tableWidget_delivery_cloth_cellClicked(int row, int column);

    void sendMessage(QStringList);

    void readMessage();

    void on_pushButton_sendRequest_clicked();

private:
    void addFont();
    void setCursor();
    void tabInit();
    void sellCount(int*, double*);
    void purchaseCount(int *);

    void setTableWidget_warehouse();
    void setTableWidget_sellGoods();
    void setTableWidget_records();
    void setStackedWidget_delivery();
    int getTabIndex(const QString&);
    void searchTableWidget(QTableWidget*, const QString&, QVector<int>&);
    void setTableWidgetItemHidden(QTableWidget*, const QString&);
public:
    enum Option {
        Stock,
        Search,
        Delivery,
        Sell,
        Records
    };
private:
    Ui::MainWindow *ui;
    QString storeId;
    bool sellSignal;//防止在表格未完全初始化之前，调用计算价钱的函数
    bool purchaseSignal;
    bool tabSignal;
    QVector<Record> qv_record;
    QVector<QStringList> qv_clothes;
    QVector<QVector<QString>> qv_stock;
    QVector<QStringList> qv_allRequest;
    QMap<QString, QMap<QString, QString>> m_requestDetail;
    int record_size;

    QStringList qsl;//用于发送消息给服务器端

    QNetworkAccessManager netManager;
    QString filepath;
    QTcpSocket *m_tcpsocket;

    Q_ENUM(Option)
};

#endif // MAINWINDOW_H
