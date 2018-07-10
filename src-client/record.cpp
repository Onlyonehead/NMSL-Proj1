#include "record.h"

Record::Record()
{

}


void Record::loadDetails(QMap<QString, QString> &details){
//    QMap<QString, QString>::iterator i;
//    for (i=details.begin(); i!=details.end(); ++i) {
//        map.insert(i.key(), i.value());
//    }
    map = details;
}

QString Record::getIdTrans(){
    return id_trans;
}

QString Record::getIdStore(){
    return id_store;
}

QString Record::getDate(){
    return date;
}

QString Record::getPrices(){
    return prices;
}

QMap<QString, QString> Record::getDetails(){
    return map;
}
