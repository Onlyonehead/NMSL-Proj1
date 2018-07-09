#include "systemcenter.h"
#include "ui_systemcenter.h"

/**
 * on_pushButton_4_clicked slot
 *
 * @author Zicun Hang
 */
void SystemCenter::on_pushButton_4_clicked()
{
    ui->tableWidget->setRowCount(0);
    QStringList list;
    list.append("info_pB4");
    sendMessage(list);
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

    QStringList list;
    list.append("info_isA");
    sendMessage(list);
}

