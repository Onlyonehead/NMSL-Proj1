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

    QStringList list;
    list.append("pB5");
    sendMessage(list);

}

/**
 * warehouse C information init
 *
 * @author Zicun Hang
 */
void SystemCenter::init_warehouse_C(){

    QStringList list;
    list.append("iwhC");
    sendMessage(list);
}

void SystemCenter::transfer(){
    QStringList list;
    list.append("transfer");
    sendMessage(list);
}
