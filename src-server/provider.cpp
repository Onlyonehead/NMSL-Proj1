#include "provider.h"
#include "sqltool.h"
#include <QSqlQuery>
#include <QList>
#include <QSql>


Provider::Provider()
{

}

/**
  * add new provider information to database
  *
  * @author Yihan Dong
  * @return void
*/



void Provider::addNewPrvider(QString providerName, QString providerAddress, QString produceInfo)
{
    QStringList providerInfo;
    providerInfo.append("0");
    providerInfo.append(providerAddress);
    providerInfo.append(providerName);
    providerInfo.append(produceInfo);
    SQLTool::insert("provider", providerInfo);

}


/**
  * search provider information by provider ID
  *
  * @author Yihan Dong
  * @return information
*/



void Provider::Info(int providerID, QStringList &providerInfo)
{
    QString ID = QString::number(providerID, 10);
    QSqlQuery query;
    SQLTool::search(query, "provider", "ID", ID);
    if (query.next()) {
      providerInfo.append(query.value(0).toString());
      providerInfo.append(query.value(1).toString());
      providerInfo.append(query.value(2).toString());
      providerInfo.append(query.value(3).toString());
    }
}


/**
  * return all providers information
  *
  * @author Yihan Dong
  * @return information
*/




void Provider::Info(QVector<QStringList> &providerInfo)
{
    QStringList list;
    QSqlQuery query;
    SQLTool::search(query, "provider");
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        providerInfo.append(list);
    }

}


/**
 * update provider information by provider ID
 *
 * @author Yihan Dong
 * @return void
*/

void Provider::updateProviderInfo(int ID, QString alterAttribute, QString alterValue)
{
    QStringList providerID;
    providerID.append("ID");
    providerID.append(QString::number(ID));
    SQLTool::update("provider", alterAttribute, alterValue, providerID);
}



