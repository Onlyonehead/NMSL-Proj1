#include "systemcenter.h"
#include "ui_systemcenter.h"

void SystemCenter::on_pushButton_19_clicked()
{
    ui->stackedWidget_sellD->setCurrentIndex(0);
}

void SystemCenter::on_pushButton_20_clicked()
{
    ui->stackedWidget_sellD->setCurrentIndex(1);
}

void SystemCenter::on_pushButton_49_clicked()
{
    ui->tw_sellD1->verticalHeader()->setVisible(false);
    ui->tw_sellD1->setRowCount(stores.size());
    ui->tw_sellD1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_sellD1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽

    int i=0;
    QVector<QStringList>::const_iterator it;
    for(it=stores.constBegin(); it!=stores.constEnd(); ++it, ++i){
        ui->tw_sellD1->setItem(i, 0, new QTableWidgetItem(it->at(1)));
    }
}

void SystemCenter::on_tw_sellD1_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    ui->comboBox_sellDUserName->clear();
    QString store_name = ui->tw_sellD1->item(row, 0)->text();
    QVector<QStringList>::const_iterator it;
    for(it=stores.constBegin(); it!=stores.constEnd(); ++it){
        if(it->at(1) == store_name){
            ui->label_sellDStoreId->setText(it->at(0));
            ui->lineEdit_sellDStoreName->setText(it->at(1));
            ui->lineEdit_sellDProvince->setText(it->at(2));
            ui->lineEdit_sellDCity->setText(it->at(3));
            ui->lineEdit_sellDAddress->setText(it->at(4));
            QString username = it->at(5);
            ui->comboBox_sellDUserName->addItem(username);
        }
    }
    QStringList qsl;
    qsl.append("changeUserName");
    sendMessage(qsl);
}

void SystemCenter::on_pushButton_24_clicked()
{
    QString id = ui->label_sellDStoreId->text();
    QString name = ui->lineEdit_sellDStoreName->text();
    QString province = ui->lineEdit_sellDProvince->text();
    QString city = ui->lineEdit_sellDCity->text();
    QString address = ui->lineEdit_sellDAddress->text();
    QString user = ui->comboBox_sellDUserName->currentText();
    QString exuser;
    qDebug()<<user;
    bool changed = false;

    if(name==""&&province==""&&city==""&&address==""&&user=="") {
        QMessageBox::warning(this, "Warning", "Informations should not be empty", QMessageBox::Yes);
        return;
    }

    //检测除店名外的信息是否修改
    QVector<QStringList>::const_iterator it;
    for(it=stores.constBegin(); it!=stores.constEnd(); ++it){
        if(it->at(0)==ui->label_sellDStoreId->text()) {
            exuser = it->at(5);
            if(it->at(1)==name&&it->at(2)==province&&it->at(3)==city&&it->at(4)==address&&it->at(5)==user){
                QMessageBox::warning(this, "Warning", "Information unchanged", QMessageBox::Yes);
                return;
            }
        }
    }

    //检测店名重复
    if(!changed){
        for(it=stores.constBegin(); it!=stores.constEnd(); ++it){
            if(name == it->at(1)) {
                QMessageBox::warning(this, "Warning", "Unusable store name", QMessageBox::Yes);
                return;
            }
        }
    }

    QStringList qsl;
    qsl.append("storeInfoChange");
    qsl << id << name << province << city << address << user << exuser;
    sendMessage(qsl);
}

void SystemCenter::on_pushButton_50_clicked()
{
    ui->tw_sellD1->setRowCount(0);
    ui->lineEdit_sellDStoreName->setText("");
    ui->lineEdit_sellDProvince->setText("");
    ui->lineEdit_sellDCity->setText("");
    ui->lineEdit_sellDAddress->setText("");
    ui->comboBox_sellDUserName->clear();
}

void SystemCenter::on_pushButton_53_clicked()
{
    ui->comboBox_2->clear();

    ui->tw_sellD2->verticalHeader()->setVisible(false);
    ui->tw_sellD2->setRowCount(clothes.size());
    ui->tw_sellD2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_sellD2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽

    int i=0;
    QVector<QStringList>::const_iterator it;
    for(it=clothes.constBegin(); it!=clothes.constEnd(); ++it, ++i){
        ui->tw_sellD2->setItem(i, 0, new QTableWidgetItem(it->at(1)+" "+it->at(2)));
    }

    QStringList qsl;
    qsl.append("changeUserName2");
    sendMessage(qsl);
}

void SystemCenter::on_tw_sellD2_cellClicked(int row, int column)
{
    Q_UNUSED(column);

    QString path;
    QString style = ui->tw_sellD2->item(row, 0)->text();
    QStringList qsl = style.split(" ");
    QVector<QStringList>::const_iterator it;
    for(it=clothes.constBegin(); it!=clothes.constEnd(); ++it){
        if(qsl.at(0)==it->at(1)&&qsl.at(1)==it->at(2)){
            path = it->at(3);
        }
    }

    QPixmap *pixmap = new QPixmap("./" + path);
    if (pixmap->isNull()){
        download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
    }
    if (pixmap->isNull()){
        pixmap = new QPixmap(":/default.jpg");
    }
    ui->label_sellDClothes->setScaledContents(true);
    ui->label_sellDClothes->setPixmap(*pixmap);

    ui->label_sellDStyle->setText(style);
}

void SystemCenter::on_pushButton_sell_right_clicked()
{
    QString style = ui->label_sellDStyle->text();
    if(style!=""){
        int count = ui->tw_sellD3->rowCount();
        QString amount = ui->lineEdit_sellDAmount->text();
        if(amount!=0){
            for(int i=0; i<count; ++i){
                if(ui->tw_sellD3->item(i, 0)->text()==style){
                    ui->tw_sellD3->item(i, 1)->setText(amount);
                    return;
                }
            }

            int count = ui->tw_sellD3->rowCount();
            ui->tw_sellD3->insertRow(count);
            ui->tw_sellD3->setItem(count, 0, new QTableWidgetItem(style));
            ui->tw_sellD3->setItem(count, 1, new QTableWidgetItem(amount));

            ui->lineEdit_sellDAmount->setText("");
        }
    }
}

void SystemCenter::on_pushButton_sell_left_clicked()
{
    int rowIndex = ui->tw_sellD3->currentRow();
    if(rowIndex != -1){

        QString path;
        QString style = ui->tw_sellD3->item(rowIndex, 0)->text();
        QStringList qsl = style.split(" ");
        QVector<QStringList>::const_iterator it;
        for(it=clothes.constBegin(); it!=clothes.constEnd(); ++it){
            if(qsl.at(0)==it->at(1)&&qsl.at(1)==it->at(2)){
                path = it->at(3);
            }
        }

        QPixmap *pixmap = new QPixmap("./" + path);
        if (pixmap->isNull()){
            download("http://39.108.155.50/project1/clothes/" + path, "./" + path);
        }
        if (pixmap->isNull()){
            pixmap = new QPixmap(":/default.jpg");
        }
        ui->label_sellDClothes->setScaledContents(true);
        ui->label_sellDClothes->setPixmap(*pixmap);

        ui->label_sellDStyle->setText(style);

        ui->tw_sellD3->removeRow(rowIndex);

    }
}

/**
 * @author sissyVI
 */
void SystemCenter::on_pushButton_23_clicked()
{
    QString name, province, city, address, username;
    name = ui->lineEdit_501->text();
    province = ui->lineEdit_502->text();
    city = ui->lineEdit_503->text();
    address = ui->lineEdit_504->text();
    username = ui->comboBox_2->currentText();
    if(name==""||province==""||city==""||address==""||username==""){
        QMessageBox::warning(this, "Warning", "Informations should not be empty", QMessageBox::Yes);
        return;
    }

    QVector<QStringList>::const_iterator it;
    for(it=stores.constBegin(); it!=stores.constEnd(); ++it){
        if(name == it->at(1)) {
            QMessageBox::warning(this, "Warning", "Unusable store name", QMessageBox::Yes);
            return;
        }
    }

    QStringList qsl;
    qsl.append("createStore");
    qsl << name << province << city << address << username;

    for(int i=0; i<ui->tw_sellD3->rowCount(); ++i){
        QStringList style = ui->tw_sellD3->item(i, 0)->text().split(" ");
        for(it=clothes.constBegin(); it!=clothes.constEnd(); ++it){
            if(it->at(1)==style.at(0)&&it->at(2)==style.at(1)){
                qsl << it->at(0);//id
                qsl << ui->tw_sellD3->item(i, 1)->text();//amount
                break;
            }
        }
    }
    sendMessage(qsl);
}

void SystemCenter::on_pushButton_54_clicked()
{
    ui->tw_sellD2->setRowCount(0);
    ui->tw_sellD3->setRowCount(0);
    QPixmap *pixmap = new QPixmap(":/default.jpg");
    ui->label_sellDClothes->setPixmap(*pixmap);
    ui->label_sellDStyle->setText("");
    ui->lineEdit_sellDAmount->setText("");
    ui->lineEdit_501->setText("");
    ui->lineEdit_502->setText("");
    ui->lineEdit_503->setText("");
    ui->lineEdit_504->setText("");
    ui->comboBox_2->clear();
}
