#include "store.h"
#include "sqltool.h"

#include <QSqlQuery>
#include <QDateTime>

/**
 * get pic path according to pic id
 *
 * @author Chang Chen
 * @param id cloth's id
 * @return picture path
 */
QString Store::getPicPath(QString id){
    QStringList qsl;
    qsl.append(QString("path"));
    QSqlQuery sq;

    //获取该行第一列的值，即cloth的ID,然后在clothes数据库中搜索该服装的详细信息
    SQLTool::search(sq, qsl, "clothes", "ID", id);
    sq.next();
    return sq.value(0).toString();
}

QString Store::getClothStyle(QString id){
    QStringList qsl;
    qsl.append(QString("style"));
    qsl.append(QString("size"));
    QSqlQuery sq;

    //获取该行第一列的值，即cloth的ID,然后在clothes数据库中搜索该服装的详细信息
    SQLTool::search(sq, qsl, "clothes", "ID", id);
    sq.next();
    return sq.value(0).toString()+"  "+sq.value(1).toString();
}

/**
 * get store info
 *
 * @author Chang Chen
 * @param username belongs to store manager
 * @param size number of values
 * @return
 */
void Store::getStoreInfo(QString username, int size, QVector<QString>& qv){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery sq(db);
    SQLTool::search(sq, "store", "username", username);
    sq.next();
    qv.clear();
    for(int i=0; i<size; ++i){
        qv<<sq.value(i).toString();
    }
}

/**
 * get the stock info of the store
 *
 * @author Chang Chen
 * @param warehouse_n table name of the warehouse
 * @return groups of cloth's id and amount
 */
void Store::getStock(int store_id, QVector<QVector<QString> >&qv){
    QStringList qsl;
    qsl.append("clothes_id");
    qsl.append("quantity");
    QSqlQuery sq;
    qv.clear();
    SQLTool::search(sq, qsl, "store_warehouse", "store_id", QString::number(store_id, 10));//读取店铺库存信息
    while(sq.next()){
        QVector<QString> qv2;
        qv2<<sq.value(0).toString()<<sq.value(1).toString();
        qv.append(qv2);
    }
}

/**
 * get the store records according to store id,
 *
 * @brief Store::getRecord
 * @param id_store the id of the store
 * @param size the total amount of record.(decide the row number of table)
 */
void Store::getRecord(int &id_store, int &size, QVector<Record>& qv){
    int count = 0;
    QSqlQuery sq;
    SQLTool::search(sq, "transrecord", "id_store", QString::number(id_store, 10));

    QStringList qsl;
    qsl.append("id_cloth");
    qsl.append("amount");
    qv.clear();
    while(sq.next()){
        Record re(sq.value(0).toString(), sq.value(1).toString(),
                  sq.value(2).toString(), sq.value(3).toString());

        QSqlQuery sq2;
        SQLTool::search(sq2, qsl, "transdetail", "id_trans", sq.value(0).toString());

        QMap<QString, QString> map;
        while(sq2.next()){
            map.insert(Store::getClothStyle(sq2.value(0).toString()), sq2.value(1).toString());
            count++;
        }
        re.loadDetails(map);
        qv.append(re);
    }
    size = count;
}

/**
 * Store::sellGoods
 *
 * @author Chang Chen
 * @param storeId
 * @param totalPrices the total prices in this transaction
 * @param clothes_amount the amount of clothes in this transaction
 * @return
 */
bool Store::sellGoods(int storeId, double totalPrices, QVector<int> clothes_amount){
    QSqlQuery sq;

    //获取交易时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");

    //添加一条交易记录
    QStringList qsl;
    qsl.append("0");
    qsl.append(QString::number(storeId, 10));
    qsl.append(current_date);
    qsl.append(QString::number(totalPrices));
    SQLTool::insert(sq, "transrecord", qsl);//添加一条交易记录

    //获得交易记录id
    QStringList qsl2;
    qsl2.append("id_trans");
    SQLTool::search(sq, qsl2, "transrecord", "date", current_date);
    sq.next();
    int id_trans = sq.value(0).toInt();

    QStringList qsl3;//用于写入交易详细记录
    for(int i=0; i<clothes_amount.size();){
        qsl3.clear();
        qsl3.append(QString::number(id_trans, 10));
        int clothId = clothes_amount.value(i++);//被售卖的服装id
        int amount = clothes_amount.value(i++);//服装数量

        QStringList qsl4;//用于查询和更新服装数量
        qsl4.append("store_id");qsl4.append(QString::number(storeId, 10));
        qsl4.append("clothes_id");qsl4.append(QString::number(clothId, 10));

        //获取在库服装数量
        SQLTool::search(sq, "quantity", "store_warehouse", qsl4);
        sq.next();

        //更新服装数量
        SQLTool::update("store_warehouse", "quantity", QString::number(sq.value(0).toInt()-amount, 10), qsl4);

        //写入交易详细记录
        qsl3.append(QString::number(clothId, 10));
        qsl3.append(QString::number(amount, 10));
        SQLTool::insert(sq, "transdetail", qsl3);
    }
    return true;
}
