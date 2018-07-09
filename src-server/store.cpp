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

QStringList Store::getClothDetail(QString id){
    QStringList qsl;
    QSqlQuery sq_cloth;
    SQLTool::search(sq_cloth, "clothes", "ID", id);
    sq_cloth.next();
    qsl<<sq_cloth.value(0).toString()<<sq_cloth.value(1).toString()
        <<sq_cloth.value(2).toString()<<sq_cloth.value(3).toString()
        <<sq_cloth.value(4).toString();
    return qsl;
}

void Store::getAllClothes(QVector<QStringList>& clothes){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    SQLTool::search(query, "clothes");
    QStringList list;
    while (query.next()) {
        list.clear();
        list.append(query.value(0).toString());
        list.append(query.value(1).toString());
        list.append(query.value(2).toString());
        list.append(query.value(3).toString());
        list.append(query.value(4).toString());
        qDebug()<<list;
        clothes.append(list);
    }
}

/**
 * get store info
 *
 * @author Chang Chen
 * @param username belongs to store manager
 * @param size number of values
 * @return
 */
QVector<QString> Store::getStoreInfo(QString username, QString s_size){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery sq(db);
    SQLTool::search(sq, "store", "username", username);
    sq.next();
    QVector<QString> qv;
    int size = s_size.toInt();
    for(int i=0; i<size; ++i){
        qv<<sq.value(i).toString();
    }
    return qv;
}

/**
 * get the stock info of the store
 *
 * @author Chang Chen
 * @param warehouse_n table name of the warehouse
 * @return groups of cloth's id and amount
 */
QVector<QVector<QString> > Store::getStock(QString store_id){
    QStringList qsl;
    qsl.append("clothes_id");
    qsl.append("quantity");
    QSqlQuery sq;
    QVector<QVector<QString> > qv;
    SQLTool::search(sq, qsl, "store_warehouse", "store_id", store_id);//读取店铺库存信息
    while(sq.next()){
        QVector<QString> qv2;
        qv2<<sq.value(0).toString()<<sq.value(1).toString();
        qv.append(qv2);
    }
    return qv;
}

/**
 * get the store records according to store id,
 *
 * @brief Store::getRecord
 * @param id_store the id of the store
 * @param size the total amount of record.(decide the row number of table)
 */
QVector<Record> Store::getRecord(int id_store, int& size){
    int count = 0;
    QSqlQuery sq;
    SQLTool::search(sq, "transrecord", "id_store", QString::number(id_store, 10));

    QStringList qsl;
    qsl.append("id_cloth");
    qsl.append("amount");
    QVector<Record> qv;
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
    return qv;
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
bool Store::sellGoods(QString storeId, QString totalPrices, QVector<int> clothes_amount){
    QSqlQuery sq;

    //获取交易时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");

    //添加一条交易记录
    QStringList qsl;
    qsl.append("0");
    qsl.append(storeId);
    qsl.append(current_date);
    qsl.append(totalPrices);
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
        qsl4.append("store_id");qsl4.append(storeId);
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
