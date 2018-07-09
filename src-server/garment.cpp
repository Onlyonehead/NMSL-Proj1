#include "garment.h"
#include "sqltool.h"
#include <QDebug>
#include <QSqlQuery>
#include <QList>
#include <QSql>


Garment::Garment()
{

}

/**
 * submit new garment's information to database
 *
 * @author Yihan Dong
 * @return void
 */
void Garment::addGarmentForm(QString garmentStyle, QString garmentSize,
                             QString garmentPic, QString garmentValue)

{
    QStringList garmentInfo;
    garmentInfo.append("0");
    garmentInfo.append(garmentStyle);
    garmentInfo.append(garmentSize);
    garmentInfo.append(garmentPic);
    garmentInfo.append(garmentValue);
    SQLTool::insert("clothes", garmentInfo);

}
/**
 * search garment;s information by ID
 *
 * @author Yihan Dong
 * @return information
 */


void Garment::Info(int i, QStringList &garmentInfo)
{
    QString ID = QString::number(i, 10);
    QSqlQuery query;
    SQLTool::search(query, "clothes", "ID", ID);
    if(query.next()){
        garmentInfo.append(query.value(0).toString());
        garmentInfo.append(query.value(1).toString());
        garmentInfo.append(query.value(2).toString());
        garmentInfo.append(query.value(3).toString());
        garmentInfo.append(query.value(4).toString());
    }
}

/**
 * return all garments' information
 *
 * @author Yihan Dong
 * @return information
 */


void Garment::Info(QVector<QStringList> &garmentInfo)
{
    QSqlQuery query;
    SQLTool::search(query, "clothes");
    QStringList list;
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        garmentInfo.append(list);
    }
}

/**
 * return a garment's information with given style
 *
 * @author Yihan Dong
 * @return information
 */


void Garment::Info(QString garmentStyle, QVector<QStringList> &garmentInfo)
{
    QSqlQuery query;
    SQLTool::search(query, "clothes", "style", garmentStyle);
    QStringList list;
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        garmentInfo.append(list);
    }
}

/**
* update a garment's information by ID
*
* @author Yihan Dong
* @return void
*/

void Garment::updateGarmentInfo(int ID, QString alterAttribute, QString alterValue)
{
    QStringList garmentInfo;
    Garment::Info(ID, garmentInfo);
    qDebug() << garmentInfo;
    QStringList alterID;
    alterID.append("ID");
    alterID.append(QString::number(ID));
    SQLTool::update("clothes", alterAttribute, alterValue, alterID);
}
