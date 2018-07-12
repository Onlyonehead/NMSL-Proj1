#include "systemcenter.h"
#include "ui_systemcenter.h"
#include "sqltool.h"
#include <QDebug>
#include <QTableWidget>
#include <QAbstractItemView>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QComboBox>
#include <QMessageBox>







/**
 * @brief SystemCenter::on_pushButton_updatePageShowStaff_clicked
 * personnel page 3 show staff info
 */
void SystemCenter::on_pushButton_updatePageShowStaff_clicked()
{
    QStringList list;
    list.append("pp3_upss");
    sendMessage(list);
}
