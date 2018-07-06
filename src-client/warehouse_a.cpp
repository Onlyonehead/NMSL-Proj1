#include "systemcenter.h"
#include "sqltool.h"
#include "ui_systemcenter.h"
#include <QCompleter>
#include <QStringListModel>

/**
 * on_pushButton_4_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_4_clicked()
{
    ui->tableWidget->setRowCount(0);
    QVector<QStringList> result;
    Warehouse::info(result);
    int n = result.size();
    int i = 0;
    while(n){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(result.at(i).at(0)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(result.at(i).at(1)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(result.at(i).at(2)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(result.at(i).at(3)));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(result.at(i).at(4)));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(result.at(i).at(5)));
        i++;
        n--;
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
}

/**
 * furry search init
 *
 * @author Zicun Hang
 */
void SystemCenter::warehouseEditComplete1(){
    QStringList wordlist;
    QVector<QStringList> result;
    QApplication::processEvents();
    Warehouse::info(result);
    QApplication::processEvents();
    int n = result.size();
    while(n){
        wordlist << result.at(n-1).at(0) << result.at(n-1).at(1) <<
                result.at(n-1).at(2) << result.at(n-1).at(3) <<
                result.at(n-1).at(4) << result.at(n-1).at(5);
        n--;
    }
    Tool::QStringList_removeDuplicates(&wordlist);
    QCompleter *completer = new QCompleter(this);
    QStringListModel *string_list_model = new QStringListModel(wordlist, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setModel(string_list_model);
    completer->popup()->setStyleSheet("border: 2px solid rgb(169, 169, 169);border-radius:0px;"
                                      "background:rgba(255, 255, 255,200);"
                                      "color: rgb(76, 76, 76);"
                                      "	font: 17pt \"Times\" bold;");
    ui->warehouse_search_A->setCompleter(completer);
}


/**
 * on_icon_search_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_icon_search_clicked()
{
    ui->tableWidget->setRowCount(0);
    QString text = ui->warehouse_search_A->text();
    if(text.trimmed() == ""){
        QMessageBox::warning(this,"警告", "\n请输入关键字！",QMessageBox::Close);
        return ;
    }

    QVector<QStringList> result;
    Warehouse::info(result);
    int n = result.size();
    int i = 0;
    while(n){
        qDebug() << result.at(n-1).at(0) << endl;
        if(result.at(n-1).at(0) == text || result.at(n-1).at(1) == text ||
                result.at(n-1).at(2) == text || result.at(n-1).at(3) == text ||
                result.at(n-1).at(4) == text || result.at(n-1).at(5) == text) {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(result.at(n-1).at(0)));
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(result.at(n-1).at(1)));
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(result.at(n-1).at(2)));
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(result.at(n-1).at(3)));
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(result.at(n-1).at(4)));
            ui->tableWidget->setItem(i, 5, new QTableWidgetItem(result.at(n-1).at(5)));
            i++;
        }
        n--;
    }
    ui->tableWidget->setRowCount(i);
}

