#include "systemcenter.h"
#include "ui_systemcenter.h"

void SystemCenter::on_pushButton_25_clicked()
{
    on_pushButton_19_clicked();

    QStringList result;

    for(QStringList l : warehouse){
        result.append("Warehouse id:  " + l.at(0) + "\n- Name: "
                     + l.at(1));
    }

    int n = result.size();

    while(n){
        QApplication::processEvents();
        ui->tableWidget_logistics_C1->insertRow(result.size()-n);
        ui->tableWidget_logistics_C1->setItem(result.size()-n, 0, new QTableWidgetItem(result.at(result.size()-n)));
        n--;
    }

    ui->tableWidget_logistics_C1->setRowCount(result.size());

    result.clear();


    for(QStringList l : stores){
        result.append("Store id:  S" + l.at(0) + "\n- Name: "
                     + l.at(1));
    }

    n = result.size();

    while(n){
        QApplication::processEvents();
        ui->tableWidget_logistics_C2->insertRow(result.size()-n);
        ui->tableWidget_logistics_C2->setItem(result.size()-n, 0, new QTableWidgetItem(result.at(result.size()-n)));
        n--;
    }

    ui->tableWidget_logistics_C2->setRowCount(result.size());
}

void SystemCenter::on_pushButton_19_clicked()
{

    ui->tableWidget_logistics_C1->setRowCount(0);
    ui->tableWidget_logistics_C2->setRowCount(0);
    ui->tableWidget_route_via->setRowCount(0);
    ui->label_recently_selected->setText("-");

    siteSelected.clear();

    ui->route_from->clear();
    ui->route_to->clear();
    siteSelected.clear();
    siteFrom.clear();
    siteTo.clear();
    siteVia.clear();

}

void SystemCenter::on_tableWidget_logistics_C1_itemClicked(QTableWidgetItem *item){
    siteSelected.clear();
    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();
    QString recently_selected = item->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            item->text().split(QRegExp("[-:]"))[3].trimmed();

    for(QStringList l : warehouse){
        if(l.at(0) == s){
            siteSelected = l;
            break;
        }
    }
    QList<QTableWidgetItem *> list = ui->tableWidget_logistics_C2->selectedItems();
    if(list.size() == 1){
        list.at(0)->setSelected(false);
    }

    ui->label_recently_selected->setText(recently_selected);

}

void SystemCenter::on_tableWidget_logistics_C2_itemClicked(QTableWidgetItem *item){
    siteSelected.clear();
    QString s = item->text().split(QRegExp("[-:]"))[1].trimmed();

    QString recently_selected = item->text().split(QRegExp("[-:]"))[1].trimmed() + " - " +
            item->text().split(QRegExp("[-:]"))[3].trimmed();

    for(QStringList l : stores){
        if("S" + l.at(0) == s){
            siteSelected = l;
            break;
        }
    }
    QList<QTableWidgetItem *> list = ui->tableWidget_logistics_C1->selectedItems();
    if(list.size() == 1){
        list.at(0)->setSelected(false);
    }

    ui->label_recently_selected->setText(recently_selected);

}

void SystemCenter::on_pushButton_add1_clicked()
{

    if(siteSelected.isEmpty()){
        QMessageBox::warning(this,"警告", "请选中条目",QMessageBox::Ok);
        return ;
    }

    if(!siteFrom.isEmpty() && siteSelected.at(1) == siteFrom.at(1)){
        QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
        return ;
    }

    if(!siteTo.isEmpty() && siteSelected.at(1) == siteTo.at(1)){
        QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
        return ;
    }

    for(QStringList l : siteVia){
        if(siteSelected.at(1) == l.at(1)){
            QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
            return ;
        }
    }
    siteFrom.clear();
    QString s = ui->label_recently_selected->text();
    ui->route_from->setText(s);
    siteFrom = siteSelected;
}

void SystemCenter::on_pushButton_add2_clicked()
{
    if(siteSelected.isEmpty()){
        QMessageBox::warning(this,"警告", "请选中条目",QMessageBox::Ok);
        return ;
    }

    if(!siteFrom.isEmpty() && siteSelected.at(1) == siteFrom.at(1)){
        QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
        return ;
    }

    if(!siteTo.isEmpty() && siteSelected.at(1) == siteTo.at(1)){
        QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
        return ;
    }

    for(QStringList l : siteVia){
        if(siteSelected.at(1) == l.at(1)){
            QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
            return ;
        }
    }

    QString s = ui->label_recently_selected->text();

    int row_count = ui->tableWidget_route_via->rowCount();


    ui->tableWidget_route_via->insertRow(row_count);
    ui->tableWidget_route_via->setItem(row_count, 0, new QTableWidgetItem(s));
    ui->tableWidget_route_via->item(row_count,0)->setTextAlignment(Qt::AlignCenter);
    siteVia.append(siteSelected);
}

void SystemCenter::on_pushButton_add3_clicked()
{
    if(siteSelected.isEmpty()){
        QMessageBox::warning(this,"警告", "请选中条目",QMessageBox::Ok);
        return ;
    }

    if(!siteFrom.isEmpty() && siteSelected.at(1) == siteFrom.at(1)){
        QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
        return ;
    }

    if(!siteTo.isEmpty() && siteSelected.at(1) == siteTo.at(1)){
        QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
        return ;
    }

    for(QStringList l : siteVia){
        if(siteSelected.at(1) == l.at(1)){
            QMessageBox::warning(this,"警告", "请添加未添加过的条目",QMessageBox::Ok);
            return ;
        }
    }
    siteTo.clear();
    QString s = ui->label_recently_selected->text();
    ui->route_to->setText(s);
    siteTo = siteSelected;
}

void SystemCenter::on_pushButton_showRoute_clicked()
{
    if(siteFrom.isEmpty() || siteTo.isEmpty()){
        QMessageBox::warning(this,"警告", "请添加条目",QMessageBox::Ok);
        return ;
    }
    QtMap *qtMap = new QtMap("http://39.108.155.50/project1/src/route.html");
    connect(this, SIGNAL(webReturn(QVector<QStringList>)),
            qtMap, SLOT(webInit(QVector<QStringList>)));
    QVector<QStringList> sites = siteVia;
    sites.insert(0, siteFrom);
    sites.append(siteTo);
    emit webReturn(sites);

    qtMap->exec();
}
