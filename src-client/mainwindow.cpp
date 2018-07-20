#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "record.h"

#include <QtMath>
#include <QFontDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QMetaEnum>
#include <QSpinBox>
#include <QDateTime>
#include <QTableWidget>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tcpsocket = new QTcpSocket(this);
    m_tcpsocket->abort();
    m_tcpsocket->connectToHost(QHostAddress::LocalHost,8848);//设置客户端的端口号
    connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readMessage()));//用于接受数据'

    m_socket = new QTcpSocket;
    m_socket->connectToHost(QHostAddress::LocalHost, 7777);
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(replyFinished()));


    sellSignal = false;
    purchaseSignal = false;

    tabSignal = false;
    tabInit();
    ui->progressBar_sell->setVisible(false);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    tabSignal = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::windowClose()
{
    this->close();
}

void MainWindow::removeSubTab(int index)
{
    ui->tabWidget->removeTab(index);
}

/**
 * @brief MainWindow::addFont
 * 在界面中添加FontAwesome图标
 */
void MainWindow::addFont(){
    // 添加字体文件
    int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf");
    QStringList fontFamilies_solid = QFontDatabase::applicationFontFamilies(fontId);

    int fontId2 = QFontDatabase::addApplicationFont(":/font/fa-brands-400.ttf");
    QStringList fontFamilies_brands = QFontDatabase::applicationFontFamilies(fontId2);

    //字体Size

    //Solid
    QFont font_solid28;
    font_solid28.setFamily(fontFamilies_solid.at(0));
    font_solid28.setPointSize(28);

    QFont font_solid14;
    font_solid14.setFamily(fontFamilies_solid.at(0));
    font_solid14.setPointSize(14);

    QFont font_solid11;
    font_solid11.setFamily(fontFamilies_solid.at(0));
    font_solid11.setPointSize(11);

    QFont font_solid10;
    font_solid10.setFamily(fontFamilies_solid.at(0));
    font_solid10.setPointSize(10);


    //Brand
    QFont font_brands10;
    font_brands10.setFamily(fontFamilies_brands.at(0));
    font_brands10.setPointSize(10);

    QFont font_brands13;
    font_brands13.setFamily(fontFamilies_brands.at(0));
    font_brands13.setPointSize(13);


    // 超市左上角图标
    ui->label->setFont(font_solid28);
    ui->label->setText(QChar(0xf54e));
    ui->label->setStyleSheet("color:rgb(1, 145, 255);");

    //功能选择图标——开始
    //图标1
    ui->label_titleIcon_1->setFont(font_brands13);
    ui->label_titleIcon_1->setText(QChar(0xf428));
    ui->label_titleIcon_1->setStyleSheet("color:rgb(1, 145, 255);");

    //图标2
    ui->label_titleIcon_2->setFont(font_solid11);
    ui->label_titleIcon_2->setText(QChar(0xf4d3));
    ui->label_titleIcon_2->setStyleSheet("color:rgb(1, 145, 255);");
    //功能选择图标——结束

    //退出图标
    ui->label_iconQuit->setFont(font_solid14);
    ui->label_iconQuit->setText(QChar(0xf011));

    //搜索图标
    ui->pushButton_storeSearch->setFont(font_solid10);
    ui->pushButton_storeSearch->setText(QChar(0xf002));

    ui->pushButton_sellSearch->setFont(font_solid10);
    ui->pushButton_sellSearch->setText(QChar(0xf002));

    ui->pushButton_purchaseSearch->setFont(font_solid10);
    ui->pushButton_purchaseSearch->setText(QChar(0xf002));

    //个人信息图标——开始
    //名字
    ui->label_font_name->setFont(font_solid10);
    ui->label_font_name->setText(QChar(0xf580));
    ui->label_font_name->setStyleSheet("color: rgb(106, 106, 106)");

    //职位
    ui->label_font_position->setFont(font_solid10);
    ui->label_font_position->setText(QChar(0xf57f));
    ui->label_font_position->setStyleSheet("color: rgb(106, 106, 106)");

    //性别
    ui->label_font_gender->setFont(font_solid10);
    ui->label_font_gender->setText(QChar(0xf578));
    ui->label_font_gender->setStyleSheet("color: rgb(106, 106, 106)");

    //邮件
    ui->label_font_mail->setFont(font_solid10);
    ui->label_font_mail->setText(QChar(0xf0e0));
    ui->label_font_mail->setStyleSheet("color: rgb(106, 106, 106)");
    //个人信息图标——结束

    //店铺信息图标——开始
    //省份
    ui->label_font_province->setFont(font_brands10);
    ui->label_font_province->setText(QChar(0xf511));
    ui->label_font_province->setStyleSheet("color: rgb(106, 106, 106)");

    //城市
    ui->label_font_city->setFont(font_brands10);
    ui->label_font_city->setText(QChar(0xf3dc));
    ui->label_font_city->setStyleSheet("color: rgb(106, 106, 106)");

    //地址
    ui->label_font_address->setFont(font_solid10);
    ui->label_font_address->setText(QChar(0xf3c5));
    ui->label_font_address->setStyleSheet("color: rgb(106, 106, 106)");
    //店铺信息图标——结束

    //售卖商品图标——开始
    //数量
    ui->label_font_totalCount->setFont(font_solid10);
    ui->label_font_totalCount->setText(QChar(0xf553));
    ui->label_font_totalCount->setStyleSheet("color: rgb(106, 106, 106)");

    //总价
    ui->label_font_totalPrice->setFont(font_solid10);
    ui->label_font_totalPrice->setText(QChar(0xf3d1));
    ui->label_font_totalPrice->setStyleSheet("color: rgb(106, 106, 106)");
    //售卖商品图标——结束

    //进货请求总计
    ui->label_font_totalCount_2->setFont(font_solid10);
    ui->label_font_totalCount_2->setText(QChar(0xf553));
    ui->label_font_totalCount_2->setStyleSheet("color: rgb(106, 106, 106)");
}

void MainWindow::setCursor(){
    QList<QPushButton *> button = this->findChildren<QPushButton *>();
    for(int i=0; i < button.count(); i++)//通过i的范围确定需要设置哪些button
    {
        button.at(i)->setCursor(QCursor(Qt::PointingHandCursor));
    }
}


void MainWindow::tabInit(){
    while(ui->tabWidget->count()>1)
        ui->tabWidget->removeTab(ui->tabWidget->count()-1);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event){
    if(watched == ui->frame_exit){
        if(event->type() == QEvent::Enter){
            ui->label_iconQuit->setStyleSheet("color:black;");
            ui->label_tuichu->setStyleSheet("color:black;");
            ui->frame_exit->setCursor(Qt::PointingHandCursor);
        } else if(event->type() == QEvent::Leave){
            ui->label_iconQuit->setStyleSheet("color:white;");
            ui->label_tuichu->setStyleSheet("color:white;");
            ui->frame_exit->setCursor(Qt::ArrowCursor);
        } else if(event->type() == QEvent::MouseButtonRelease){
            Login *lg = new Login;
            lg->show();
            this->close();
        }
        return true;
    }
    return false;
}

/**
 * @brief MainWindow::getTabIndex
 * @param name
 * @return 页的当前页码，若该页不存在于界面中，则返回-1
 */
int MainWindow::getTabIndex(const QString &name){
    int total = ui->tabWidget->count();
    for(int i=0; i<total; ++i) {
        if(ui->tabWidget->tabText(i) == name)
            return i;
    }
    return -1;
}

void MainWindow::on_pushButton_1_clicked()
{
    QString s = "Stock";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_1, s);
    }

    //如果之前该页被关闭的话，则点击按钮不会立即显示该页。
    //    ui->tabWidget->setCurrentIndex(index);
    ui->tabWidget->setCurrentWidget(ui->tab_1);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString s = "Search";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_2, s);
    }
    ui->tabWidget->setCurrentWidget(ui->tab_2);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString s = "Delivery";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_3, s);
    }
    ui->tabWidget->setCurrentWidget(ui->tab_3);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString s = "Sell";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_4, s);
    }
    ui->tabWidget->setCurrentWidget(ui->tab_4);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString s = "Records";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_5, s);
    }
    ui->tabWidget->setCurrentWidget(ui->tab_5);
}

void MainWindow::on_pushButton_shop_clicked()
{
    QString s = "StoreInfo";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_shop, s);
    }
    ui->tabWidget->setCurrentWidget(ui->tab_shop);
}

void MainWindow::on_pushButton_user_clicked()
{
    QString s = "PrivateInfo";
    int index = getTabIndex(s);
    if(-1 == index) {
        ui->tabWidget->addTab(ui->tab_userInfo, s);
    }
    ui->tabWidget->setCurrentWidget(ui->tab_userInfo);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(tabSignal){
        QString title = ui->tabWidget->tabText(index);
        QMetaEnum myEnum = QMetaEnum::fromType<MainWindow::Option>();
        int page = myEnum.keyToValue(title.toStdString().c_str());

        switch (page) {
        case 0:
            setTableWidget_warehouse();//显示仓库信息
            break;
        case 1:
            break;
        case 2:
            setStackedWidget_delivery();//请求进货
            break;
        case 3:
            setTableWidget_sellGoods();//商品售卖
            break;
        case 4:
            setTableWidget_records();//查看记录
            break;
        default:
            break;
        }
    }
}


/**
 * download picture
 *
 * @author hzc
 * @param surl pic url
 * @param filePath local file path
 */
void MainWindow::download(const QString &url, const QString &filePath)
{

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out << (quint32) (sizeof(QString));
    out << url;
    out.device()->seek(0);
    m_socket->write(message);

    this->filepath = filePath;

}

/**
 * save picture
 *
 * @author hzc
 * @param reply NetworkReply
 */
void MainWindow::replyFinished()
{
    QDataStream in(m_socket);
    in.setVersion (QDataStream::Qt_5_7);

    if(dataSize == 0)
    {
       qDebug() << m_socket->bytesAvailable();
       qDebug() << (sizeof(quint32)+sizeof(QString));
       if(m_socket->bytesAvailable() < (sizeof(quint32)+sizeof(QString)))
       {
            return;
       }
       in >> dataSize;
       in >> fileName;
       qDebug() << dataSize;
       qDebug() << fileName;
    }

    if(dataSize > qint32(m_socket->bytesAvailable()))
    {
       return;
    }

    QByteArray data;

    in>>data;

    QImage img;
    img.loadFromData(data);

    img.save(DIR + fileName);

    qDebug() << "Download: " + fileName;

    dataSize = 0;
    fileName.clear();
}

/**
 * slot method
 *
 * @param s1 username
 * @param s2 name
 * @param s3 position
 * @param s4 gender
 * @param s5 email
 */
void MainWindow::showString(QString s1, QString s2, QString s3, QString s4, QString s5, QString s6)
{
    addFont();
    this->show();

    QElapsedTimer t;

    ui->progressBar->setRange(0, 100);//设置进度条范围
    ui->progressBar->setValue(0);

    //设置用户信息
    ui->label_name->setText(s2);
    ui->label_position->setText(s3);
    ui->pushButton_user->setText(s2+QString(" | ")+s3);
    ui->label_gender->setText(s4);
    ui->label_mail->setText(s5);

    QApplication::processEvents();
    //初始化店铺信息
    qsl.clear();
    qsl.append("getStoreInfo");
    qsl.append(s1);
    qsl.append(QString::number(5, 10));
    sendMessage(qsl);
    ui->progressBar->setValue(10);

    m_tcpsocket->flush();
    t.start();
    while(t.elapsed()<1000)
        QCoreApplication::processEvents();


    QApplication::processEvents();
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));
    ui->frame_exit->installEventFilter(this);
    setCursor();
    ui->progressBar->setValue(20);

    QApplication::processEvents();

    QPixmap *pixmap = new QPixmap(DIR + QString("/users/") + s6);
    if (pixmap->isNull()){
        download("/users/" + s6, DIR + QString("/users/") + s6);
    }

    if (pixmap->isNull()){
        pixmap = new QPixmap(":/user.png");
    }
    QApplication::processEvents();
    ui->label_user->setScaledContents(true);
    ui->label_user->setPixmap(*pixmap);
    ui->progressBar->setValue(40);

    QApplication::processEvents();
    qsl.clear();
    qsl.append("MainWindowInit");
    qsl.append(storeId);
    sendMessage(qsl);
    ui->progressBar->setValue(50);

    m_tcpsocket->flush();

}

/**
 * search the row index of items according to user input
 * @param arg1 user input
 * @param qv_row result set
 */
void MainWindow::searchTableWidget(QTableWidget* table, const QString &arg1, QVector<int> &qv_row){
    QString check = "check";

    if(arg1.length()==5&&0==check.indexOf(arg1, 0, Qt::CaseInsensitive)){//如果输入的字符串为check（不区分大小写）
        for(int i=0; i<table->rowCount(); ++i){
            if(Qt::Checked==table->item(i, 0)->checkState())
                qv_row.append(i);
        }
    } else{
        for(int i=0; i<table->rowCount(); ++i){
            for(int j=1; j<=3; ++j){
                if(-1!=table->item(i, j)->text().indexOf(arg1, 0, Qt::CaseInsensitive)){
                    qv_row.append(i);
                    break;
                }
            }
        }
    }
}

void MainWindow::setTableWidgetItemHidden(QTableWidget *table, const QString &arg1){
    QVector<int> qv_row;

    //输入为空，显示所有Item
    if(arg1==""){
        for(int i=0; i<table->rowCount(); ++i){
            table->setRowHidden(i, false);
        }
    } else{
        searchTableWidget(table, arg1, qv_row);
        QVector<int>::iterator it;
        for(int i=0; i<table->rowCount(); ++i){
            table->setRowHidden(i, true);
        }
        for(it=qv_row.begin(); it!=qv_row.end(); ++it){
            table->setRowHidden(*it, false);
        }
    }
}

void MainWindow::sendMessage(QStringList list)
{

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_7);
    out << (quint16) 0;
    out << list;
    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    m_tcpsocket->write(message);
}


void MainWindow::readMessage()
{
    QDataStream in(m_tcpsocket);
    in.setVersion(QDataStream::Qt_5_7);
    quint16 blocksize = 0;
    if (m_tcpsocket->bytesAvailable() < (int)sizeof(quint16)){
        return;

    }
    in >> blocksize;

    if(m_tcpsocket->bytesAvailable() < blocksize){
        return;
    }
    QString from;
    in >> from;
    qDebug() << from << endl;

    if(from == "getStoreInfo"){

        QVector<QString> qv;
        in >> qv;
        ui->pushButton_shop->setText(qv.at(1));

        storeId = qv.at(0);//储存店铺id
        ui->label_province->setText(qv.at(2));
        ui->label_city->setText(qv.at(3));
        ui->label_address->setText(qv.at(4));
    }

    if(from == "getStock"){

        qv_stock.clear();
        in >> qv_stock;
    }

    if(from == "sellGoods"){
        QString message;
        in >> message;
        qDebug()<<message;
        ui->progressBar_sell->setValue(60);

        qv_stock.clear();
        in >> qv_stock;

        int qv_size;//获取QVector的大小
        QString id_trans;
        QString id_store;
        QString date;
        QString prices;
        QMap<QString, QString> m;
        in >> qv_size;
        qDebug()<<"记录大小："<<qv_size;
        qv_record.clear();
        for(int i=0; i<qv_size; ++i){
            in >> id_trans >> id_store >> date >> prices >> m;
            Record r(id_trans, id_store, date, prices);
            r.loadDetails(m);
            qv_record.append(r);
        }
        in >> record_size;
        ui->progressBar_sell->setValue(100);
        ui->progressBar_sell->setVisible(false);
        setTableWidget_sellGoods();//刷新页面
    }

    if(from == "MainWindowInit"){
        in >> qv_clothes;
        in >> qv_stock;
        QApplication::processEvents();
        ui->progressBar->setValue(100);
        QTime t;
        t.start();
        while(t.elapsed()<100)
            QCoreApplication::processEvents();

        int qv_size;//获取QVector的大小
        QString id_trans;
        QString id_store;
        QString date;
        QString prices;
        QMap<QString, QString> m;
        in >> qv_size;
        qDebug()<<"记录大小："<<qv_size;
        for(int i=0; i<qv_size; ++i){
            in >> id_trans >> id_store >> date >> prices >> m;
            Record r(id_trans, id_store, date, prices);
            r.loadDetails(m);
            qv_record.append(r);
        }
        QApplication::processEvents();
        in >> record_size;
        ui->progressBar->setVisible(false);
    }

    if(from == "sendRequest"){
        QString message;
        in >> message;
        qDebug()<<message;

        setStackedWidget_delivery();
    }

    if(from == "getRequests"){
        in >> qv_allRequest >> m_requestDetail;
    }
}
