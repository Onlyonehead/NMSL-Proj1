#include "systemcenter.h"
#include "ui_systemcenter.h"

/**
 * on_pushButton_4_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_4_clicked()
{
    wh_info_warehouse.clear();
    ui->tableWidget->setRowCount(0);
    QVector<QStringList> result = warehouse;
    int i = 0;
    for(QStringList list : result){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(list.at(0)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(list.at(1)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(list.at(2)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(list.at(3)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(list.at(4)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(list.at(5)));
        i++;
    }
    ui->tableWidget->setRowCount(i);
    progressBar();
}

/**
 * on_pushButton_6_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_6_clicked()
{
    ui->warehouse_search_A->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_A->setRowCount(0);
    ui->warehouse_id->clear();
    wh_info_warehouse.clear();
}

/**
 * furry search init
 *
 * @author Zicun Hang
 */
void SystemCenter::warehouseEditComplete(){
    QStringList list;
    list.append("info_whEC");
    sendMessage(list);

}


/**
 * on_icon_search_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_icon_search_clicked()
{
    QString text = ui->warehouse_search_A->text();
    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }

    ui->tableWidget->setRowCount(0);
    QVector<QStringList> result = warehouse;
    int i = 0;
    for(QStringList list: result){
        qDebug() << list.at(0) << endl;
        if(list.at(0) == text || list.at(1) == text ||
                list.at(2) == text || list.at(3) == text ||
                list.at(4) == text || list.at(5) == text) {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(list.at(0)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(list.at(1)));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(list.at(2)));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(list.at(3)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(list.at(4)));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(list.at(5)));
            i++;
        }
    }
    ui->tableWidget->setRowCount(i);
}



void SystemCenter::on_w_search_A_clicked()
{
    QString text = ui->warehouse_id->text();

    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入id！",QMessageBox::Close);
        return;
    }
    QByteArray ba = text.toLatin1();
    const char *s = ba.data();
    while(*s && *s>='0' && *s<='9') s++;

    if (*s)
    { //不是纯数字
        QMessageBox::warning(this,"警告", "\n请输入纯数字！",QMessageBox::Close);
        return;
    }

    QStringList msg;
    msg.append("wh_history");
    msg.append(text);
    sendMessage(msg);
}

void SystemCenter::on_tableWidget_A_itemClicked(QTableWidgetItem *item){
    QString s;
    s += "\n";
    s += ui->tableWidget_A->item(item->row(), 2)->text();
    s += "\n";
    s += "\n";
    s += ui->tableWidget_A->item(item->row(), 0)->text();
    s += "\n";
    s += ui->tableWidget_A->item(item->row(), 1)->text();
    s += "\n";
    s += "\n";
    for(QStringList l : wh_history){
        QStringList temp = l.at(0).split(QRegExp("[A-Z]"));
        if(l.at(1) == ui->tableWidget_A->item(item->row(), 0)->text().split(":")[1].trimmed() &&
                l.at(2) == ui->tableWidget_A->item(item->row(), 1)->text().split(":")[1].trimmed() &&
                temp.at(0) + " " + temp.at(1)
                == ui->tableWidget_A->item(item->row(), 2)->text()){
            s += l.at(3);
            break;
        }
    }
    QMessageBox::information(this,"历史", s,QMessageBox::Ok);
}

void SystemCenter::on_w_search_A_3_clicked()
{
    QStringList msg;
    msg.append("wh_history_all");
    sendMessage(msg);
}

void SystemCenter::on_pushButton_28_clicked() //cancel
{
    ui->add_warehouse->setVisible(false);
    ui->pushButton_22->setEnabled(true);
    ui->pushButton_23->setEnabled(true);
    ui->pushButton_24->setEnabled(true);
}

void SystemCenter::on_pushButton_22_clicked() // add button
{
    ui->add_warehouse->setVisible(true);
    ui->pushButton_23->setEnabled(false);
    ui->pushButton_24->setEnabled(false);
    ui->add_warehouse->raise();
}

void SystemCenter::on_pushButton_27_clicked()
{
    QString name = ui->warehouse_add_name->text();
    QString province = ui->warehouse_add_province->text();
    QString city = ui->warehouse_add_city->text();
    QString address = ui->warehouse_add_address->text();
    if(name.trimmed() == "" || province.trimmed() == "" ||
            address.trimmed() == ""){
        QMessageBox::warning(this," 警告", "\n请输入全部字段",QMessageBox::Close);
        return ;
    }
    QString msg = province + city + address;
    QNetworkAccessManager *m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
    QUrl url;
    url = QUrl("https://restapi.amap.com/v3/geocode/geo?key=be6f38b0c3801dd73bcba0e07165b068&address="
               + msg);

    QNetworkRequest request;
    request.setUrl(url);

    m_accessManager->get(request);
}

void SystemCenter::finishedSlot(QNetworkReply* reply){
    bool flag = false;
    if (reply->error() == QNetworkReply::NoError){
        QByteArray ba = reply->readAll();
            QJsonParseError jsonpe;
            QJsonDocument json = QJsonDocument::fromJson(ba, &jsonpe);
            if (jsonpe.error == QJsonParseError::NoError){
                if (json.isObject()){
                    QJsonObject obj = json.object();
                    if (obj.contains("error")){
                        qDebug() << "error:" << obj["error"];
                    }else{
                        QJsonArray jarray = obj.value("geocodes").toArray();

                        QString position = jarray[0].toObject().value("location").toString();

                        QString name = ui->warehouse_add_name->text();
                        QString province = ui->warehouse_add_province->text();
                        QString city = ui->warehouse_add_city->text();
                        QString address = ui->warehouse_add_address->text();
                        QString position_x = position.split(",")[0];
                        QString position_y = position.split(",")[1];

                        QStringList msg;
                        msg.append("add_warehouse");
                        msg.append(name);
                        msg.append(province);
                        msg.append(city);
                        msg.append(address);
                        msg.append(position_x);
                        msg.append(position_y);
                        sendMessage(msg);
                        flag = true;
                    }
                }else{
                    qDebug() << "error, shoud be json object";
                }
            }else{
                qDebug() << "error:" << jsonpe.errorString();
            }
    }else{
        qDebug() << "error:" << reply->errorString();
    }
    if(!flag){
        QMessageBox::warning(this," 警告", "\n添加失败",QMessageBox::Close);
        return ;
    }
}


void SystemCenter::on_tableWidget_itemClicked(QTableWidgetItem *item){
    wh_info_warehouse.clear();
    wh_info_warehouse.append(ui->tableWidget->item(item->row(),1)->text());
    wh_info_warehouse.append(ui->tableWidget->item(item->row(),2)->text());
    wh_info_warehouse.append(ui->tableWidget->item(item->row(),3)->text());
    wh_info_warehouse.append(ui->tableWidget->item(item->row(),4)->text());
    wh_info_warehouse.append(ui->tableWidget->item(item->row(),0)->text());
}

void SystemCenter::on_pushButton_30_clicked() //cancel
{
    ui->edit_warehouse->setVisible(false);
    ui->pushButton_22->setEnabled(true);
    ui->pushButton_23->setEnabled(true);
    ui->pushButton_24->setEnabled(true);
}

void SystemCenter::on_pushButton_29_clicked() //confirm
{
    if(ui->warehouse_edit_name->text().trimmed() == wh_info_warehouse.at(0) &&
            ui->warehouse_edit_province->text().trimmed()  == wh_info_warehouse.at(1) &&
            ui->warehouse_edit_city->text().trimmed()  == wh_info_warehouse.at(2) &&
            ui->warehouse_edit_address->text().trimmed()  == wh_info_warehouse.at(3)){
        QMessageBox::warning(this," 警告", "\n未进行任何修改",QMessageBox::Close);
        return ;
    }
    QString msg = ui->warehouse_edit_province->text().trimmed() +
            ui->warehouse_edit_city->text().trimmed() +
            ui->warehouse_edit_address->text().trimmed();
    QNetworkAccessManager *m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlotForEdit(QNetworkReply*)));
    QUrl url;
    url = QUrl("https://restapi.amap.com/v3/geocode/geo?key=be6f38b0c3801dd73bcba0e07165b068&address="
               + msg);

    QNetworkRequest request;
    request.setUrl(url);

    m_accessManager->get(request);
}



void SystemCenter::on_pushButton_23_clicked() //edit button
{
    if(wh_info_warehouse.isEmpty()){
        QMessageBox::warning(this," 警告", "\n请选中仓库",QMessageBox::Close);
        return ;
    }
    ui->edit_warehouse->setVisible(true);
    ui->pushButton_22->setEnabled(false);
    ui->pushButton_24->setEnabled(false);
    ui->warehouse_edit_name->setText(wh_info_warehouse.at(0));
    ui->warehouse_edit_province->setText(wh_info_warehouse.at(1));
    ui->warehouse_edit_city->setText(wh_info_warehouse.at(2));
    ui->warehouse_edit_address->setText(wh_info_warehouse.at(3));
    ui->edit_warehouse->raise();
}

void SystemCenter::finishedSlotForEdit(QNetworkReply* reply){
    bool flag = false;
    if (reply->error() == QNetworkReply::NoError){
        QByteArray ba = reply->readAll();
            QJsonParseError jsonpe;
            QJsonDocument json = QJsonDocument::fromJson(ba, &jsonpe);
            if (jsonpe.error == QJsonParseError::NoError){
                if (json.isObject()){
                    QJsonObject obj = json.object();
                    if (obj.contains("error")){
                        qDebug() << "error:" << obj["error"];
                    }else{
                        QJsonArray jarray = obj.value("geocodes").toArray();

                        QString position = jarray[0].toObject().value("location").toString();

                        QString name = ui->warehouse_edit_name->text();
                        QString province = ui->warehouse_edit_province->text();
                        QString city = ui->warehouse_edit_city->text();
                        QString address = ui->warehouse_edit_address->text();
                        QString position_x = position.split(",")[0];
                        QString position_y = position.split(",")[1];
                        qDebug() << position_x;
                        qDebug() << position_y;

                        QStringList msg;
                        msg.append("edit_warehouse");
                        msg.append(wh_info_warehouse.at(4));
                        msg.append(name);
                        msg.append(province);
                        msg.append(city);
                        msg.append(address);
                        msg.append(position_x);
                        msg.append(position_y);
                        sendMessage(msg);
                        flag = true;
                    }
                }else{
                    qDebug() << "error, shoud be json object";
                }
            }else{
                qDebug() << "error:" << jsonpe.errorString();
            }
    }else{
        qDebug() << "error:" << reply->errorString();
    }
    if(!flag){
        QMessageBox::warning(this," 警告", "\n添加失败",QMessageBox::Close);
        return ;
    }
}

void SystemCenter::on_pushButton_24_clicked() //delete
{
    if(wh_info_warehouse.isEmpty()){
        QMessageBox::warning(this," 警告", "\n请选中仓库",QMessageBox::Close);
        return ;
    }
    if(QMessageBox::Yes==QMessageBox::question(this, "警告", "1 ：Confirm to delete this warehouse ?",
                                               QMessageBox::Yes, QMessageBox::No)){
        if(QMessageBox::Yes==QMessageBox::question(this, "警告", "2 ：Confirm to delete this warehouse ?",
                                                   QMessageBox::Yes, QMessageBox::No)){
            if(QMessageBox::Yes==QMessageBox::question(this, "警告", "3 ：Confirm to delete this warehouse ?",
                                                       QMessageBox::Yes, QMessageBox::No)){
                QStringList msg;
                msg.append("del_warehouse");
                msg.append(wh_info_warehouse.at(4));
                sendMessage(msg);
            }
        }
    }
}


void SystemCenter::on_pushButton_20_clicked()
{

    QtMap *qtMap = new QtMap("http://39.108.155.50/project1/src/warehouse.html");
    connect(this, SIGNAL(webReturn(QVector<QStringList>)),
            qtMap, SLOT(webInit(QVector<QStringList>)));
    emit webReturn(warehouse);

    qtMap->exec();
}
