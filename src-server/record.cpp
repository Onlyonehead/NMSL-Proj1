#include "record.h"

Record::Record()
{

}



//inline QDataStream& operator>>(QDataStream& in,Record& record)
//{
//    QMap<QString, QString> m;
//    QString id_trans;
//    QString id_store;
//    QString date;
//    QString prices;
//    in>>m>>id_trans>>id_store>>date>>prices;
//    record.loadDetails(m);
//    record.setIdTrans(id_trans);
//    record.setIdStore(id_store);
//    record.setDate(date);
//    record.setPrices(prices);

//    return in;
//}

void Record::loadDetails(QMap<QString, QString> &details){
    map = details;
}

QString Record::getIdTrans() const{
    return id_trans;
}

QString Record::getIdStore() const{
    return id_store;
}

QString Record::getDate() const{
    return date;
}

QString Record::getPrices() const{
    return prices;
}

QMap<QString, QString> Record::getDetails() const{
    return map;
}

void Record::setIdTrans(QString& trans){
    id_trans = trans;
}

void Record::setIdStore(QString& store){
    id_store = store;
}

void Record::setDate(QString& d){
    date = d;
}

void Record::setPrices(QString& p){
    prices = p;
}
