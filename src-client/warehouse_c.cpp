#include "systemcenter.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>


/**
 * on_pushButton_7_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_7_clicked()
{
    ui->warehouse_search_C->clear();
    ui->tableWidget_C1->setRowCount(0);
    ui->tableWidget_C2->setRowCount(0);
}

/**
 * on_icon_search_C_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_icon_search_C_clicked()
{

    QString text = ui->warehouse_search_C->text();
    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }
    QApplication::processEvents();

    QStringList list;
    list.append("isC");
    list.append(text);
    sendMessage(list);

}

/**
 * on_pushButton_5_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_5_clicked()
{

    ui->tableWidget_C1->setRowCount(0);
    ui->tableWidget_C2->setRowCount(0);

    QMap<QString, QString> warehouse = this->warehouse_map;

    QMap<QString,QMap<QString, QString>> stock = stock_map;

    QMap<QString, QMap<QString, QStringList>> arriving = arriving_map;

    QVector<QStringList> clothes = this->clothes;

    int count_i = 0;
    int count_j = 0;

    for (QMap<QString,QMap<QString, QString>>::const_iterator j
         = stock.begin(); j != stock.end(); ++j){
        QApplication::processEvents();
        for(QMap<QString, QString>::const_iterator i = j.value().begin(); i != j.value().end(); ++i){
            QStringList list;
            for(QStringList l : clothes){
                if(l.at(0) == i.key()){
                    list = l;
                    break;
                }
            }
            QApplication::processEvents();

            ui->tableWidget_C1->insertRow(count_i);
            ui->tableWidget_C1->setItem(count_i, 0, new QTableWidgetItem(warehouse.find(j.key()).value()));
            ui->tableWidget_C1->setItem(count_i, 1, new QTableWidgetItem(i.key()));
            ui->tableWidget_C1->setItem(count_i, 2, new QTableWidgetItem(list.at(1)));
            QApplication::processEvents();
            ui->tableWidget_C1->setItem(count_i, 3, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_C1->setItem(count_i, 4, new QTableWidgetItem(i.value()));
            count_i++;
            QApplication::processEvents();
        }
        if(j.value().size() > 1){
//                ui->tableWidget_C1->item(count_i-j.value().size(), 0)->setBackground(QBrush(QColor(255,255,255)));
            ui->tableWidget_C1->setSpan(count_i-j.value().size(), 0, j.value().size(), 1);

        }
    }

    for (QMap<QString,QMap<QString, QStringList>>::const_iterator j
         = arriving.begin(); j != arriving.end(); ++j){
        QApplication::processEvents();
        for(QMap<QString, QStringList>::const_iterator i =
            j.value().begin(); i != j.value().end(); ++i){
            QStringList list;
            for(QStringList l : clothes){
                if(l.at(0) == i.key()){
                    list = l;
                    break;
                }
            }
            QApplication::processEvents();
            ui->tableWidget_C2->insertRow(count_j);
            ui->tableWidget_C2->setItem(count_j, 0, new QTableWidgetItem(warehouse.find(j.key()).value()));
            ui->tableWidget_C2->setItem(count_j, 1, new QTableWidgetItem(i.key()));
            ui->tableWidget_C2->setItem(count_j, 2, new QTableWidgetItem(list.at(1)));
            QApplication::processEvents();
            ui->tableWidget_C2->setItem(count_j, 3, new QTableWidgetItem(list.at(2)));
            ui->tableWidget_C2->setItem(count_j, 4, new QTableWidgetItem(i.value().at(0)));
            QStringList s = i.value().at(1).split(QRegExp("[A-Z]"));
            ui->tableWidget_C2->setItem(count_j, 5, new QTableWidgetItem(s.at(0) + " " + s.at(1)));

            QApplication::processEvents();
            count_j++;
        }
        if(j.value().size() > 1){
//                ui->tableWidget_C2->item(count_i-j.value().size(), 0)->setBackground(QBrush(QColor(255,255,255)));
            ui->tableWidget_C2->setSpan(count_j-j.value().size(), 0, j.value().size(), 1);

        }

    }

    progressBar();
    QApplication::processEvents();
    ui->tableWidget_C1->setRowCount(count_i);
    ui->tableWidget_C2->setRowCount(count_j);

}

void SystemCenter::transfer(){
    QStringList list;
    list.append("transfer");
    sendMessage(list);
}
