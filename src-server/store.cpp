#include "store.h"
#include "sqltool.h"

#include <QSqlQuery>
#include <QDateTime>

/**
 * get all clothes' details
 *
 * @brief Store::getAllClothes
 * @param clothes
 */
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
 * @author sissyVI
 * @param username belongs to store manager
 * @param size number of values
 * @return
 */
void Store::getStoreInfo(QString username, QString s_size, QVector<QString>& qv){
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery sq(db);
    SQLTool::search(sq, "store", "username", username);
    sq.next();
    int size = s_size.toInt();
    for(int i=0; i<size; ++i){
        qv<<sq.value(i).toString();
    }
}

/**
 * get the stock info of the store
 *
 * @author sissyVI
 * @param warehouse_n table name of the warehouse
 * @return groups of cloth's id and amount
 */
void Store::getStock(QString store_id, QVector<QVector<QString> >& qv){
    QStringList qsl;
    qsl.append("clothes_id");
    qsl.append("quantity");
    QSqlQuery sq;
    SQLTool::search(sq, qsl, "store_warehouse", "store_id", store_id);//读取店铺库存信息
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
void Store::getRecord(int id_store, int& size, QVector<Record>& qv){
    int count = 0;
    QSqlQuery sq;
    SQLTool::search(sq, "transrecord", "id_store", QString::number(id_store, 10));

    QStringList qsl;
    qsl.append("id_cloth");
    qsl.append("amount");
    while(sq.next()){
        Record re(sq.value(0).toString(), sq.value(1).toString(),
                  sq.value(2).toString(), sq.value(3).toString());

        QSqlQuery sq2;
        SQLTool::search(sq2, qsl, "transdetail", "id_trans", sq.value(0).toString());

        QMap<QString, QString> map;
        while(sq2.next()){
            map.insert(sq2.value(0).toString(), sq2.value(1).toString());//插入服装id和数量
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
 * @author sissyVI
 * @param storeId
 * @param totalPrices the total prices in this transaction
 * @param clothes_amount the amount of clothes in this transaction
 * @return
 */
bool Store::sellGoods(QString storeId, QString totalPrices, QVector<int>& clothes_amount){
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

void Store::getStores(QVector<QStringList> &qv){
    QStringList qsl;
    QSqlQuery sq;
    SQLTool::search(sq, "store");
    while(sq.next()){
        qsl.clear();
        for(int i=0; i<6; ++i){
            qsl<<sq.value(i).toString();
        }
        qv.append(qsl);
    }
}

void Store::purchase(QString store_id, QMap<QString, QString> &m){
    QSqlQuery sq;
    QMap<QString, QString>::const_iterator mit;
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");

    QStringList qsl;
    qsl.append("0");
    qsl.append(store_id);
    qsl.append(current_date);
    qsl.append("0");
    qsl.append(current_date);
    SQLTool::insert(sq, "store_pRecord", qsl);
    SQLTool::search(sq, "store_pRecord", "date", current_date);
    sq.next();
    QString id_pur = sq.value(0).toString();

    for(mit=m.constBegin(); mit!=m.constEnd(); ++mit){
        qsl.clear();
        qsl.append(id_pur);
        qsl.append(mit.key());
        qsl.append(mit.value());
        SQLTool::insert(sq, "store_pDetail", qsl);
    }
}

/**
 * get store info and clothes info
 *
 * @author sissyVI
 * @param purchase_id the only id of a purchase request
 * @param store_id
 * @param qsl to keep store info
 * @param qv to keep clothes' info
 */
void Store::getPurchaseInfo(QString purchase_id, QString store_id, QStringList& qsl, QVector<QStringList>& qv){
    QSqlQuery sq, sq3;
    SQLTool::search(sq, "store", "id_store", store_id);
    sq.next();
    qsl.append(sq.value(1).toString());//name
    qsl.append(sq.value(5).toString());//user
    QString p, c;
    p = sq.value(2).toString();
    c = sq.value(3).toString();

    //location
    if(c == "")
        qsl.append(p+"市");
    else
        qsl.append(p+"省"+c+"市");

    SQLTool::search(sq, "store_pDetail", "id_purchase", purchase_id);
    while(sq.next()){
        QStringList qsl2;
        qsl2.append(sq.value(1).toString());//id_clothes

        QStringList qsl3;
        qsl3.append("store_id");
        qsl3.append(store_id);
        qsl3.append("clothes_id");
        qsl3.append(sq.value(1).toString());
        SQLTool::search(sq3, "quantity", "store_warehouse", qsl3);
        sq3.next();

        if(!sq3.isValid())
            qsl2.append(QString::number(0, 10));
        else
            qsl2.append(sq3.value(0).toString());//exist
        qsl2.append(sq.value(2).toString());//amount
        qv.append(qsl2);
    }
}

void Store::getPurchaseInfo(QString store_id, QVector<QStringList> &qv, QMap<QString, QMap<QString, QString> > &m){
    QSqlQuery sq, sq2;
    SQLTool::search(sq, "store_pRecord", "id_store", store_id);
    while(sq.next()){
        QStringList qsl;
        qsl.append(sq.value(0).toString());//id
        qsl.append(sq.value(2).toString());//date
        qsl.append(sq.value(3).toString());//check
        qv.append(qsl);

        SQLTool::search(sq2, "store_pDetail", "id_purchase", sq.value(0).toString());
        QMap<QString, QString> m2;
        while(sq2.next()){
            m2.insert(sq2.value(1).toString(), sq2.value(2).toString());
        }
        m.insert(sq.value(0).toString(), m2);
    }
}

void Store::getAllPurchaseInfo(QVector<QStringList> &qv){
    QSqlQuery sq;
    SQLTool::search(sq, "store_pRecord", "checked", QString::number(0, 10));
    while(sq.next()){
        QStringList qsl;
        qsl.append(sq.value(0).toString());
        qsl.append(sq.value(1).toString());
        qsl.append(sq.value(2).toString());
        qv.append(qsl);
    }
}

void Store::changePAmount(QString id_p, QString id_c, QString amount){
    QStringList qsl;
    qsl.append("id_purchase");
    qsl.append(id_p);
    qsl.append("id_clothes");
    qsl.append(id_c);
    SQLTool::update("store_pDetail", "amount", amount, qsl);
}

/**
 *
 *
 * @author sissyVI
 * @param store_id the store id of destination
 * @param time_com commit time
 * @param qv from id and details(cloth id and quantity)
 * @param m from id and arrive time
 */
void Store::storeArrive(QString store_id, QString time_com, Order& o){
    QSqlQuery sq;
    QStringList qsl;
    qsl.append("id_store");
    qsl.append(store_id);
    qsl.append("date_check");
    qsl.append(time_com);
    SQLTool::search(sq, "id_purchase", "store_pRecord", qsl);
    sq.next();
    QString purchase_id = sq.value(0).toString();
    qDebug()<<"purchase_id: "<<purchase_id;

    QString from_id = o.getId();
    QString date_arr = o.getDatetime();
    QStringList qsl_c = o.getProductInfo();

    for(int i=0; i<qsl_c.size();){
        QStringList qsl_arr;
        qDebug() << store_id << qsl_c.at(i) << qsl_c.at(i+1) << date_arr << from_id << purchase_id;
        qsl_arr << store_id << qsl_c.at(i++) << qsl_c.at(i++) << date_arr << from_id << purchase_id;
        SQLTool::insert("store_arriving", qsl_arr);
    }

}

