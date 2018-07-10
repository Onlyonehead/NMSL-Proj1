#ifndef RECORD_H
#define RECORD_H

#include <QMap>

class Record
{
public:
    Record();
    Record(QString id_trans, QString id_store, QString date, QString prices):
        id_trans(id_trans), id_store(id_store), date(date), prices(prices){}

    QString getIdTrans() const;
    QString getIdStore() const;
    QString getDate() const;
    QString getPrices()const;
    QMap<QString, QString> getDetails() const;

    void setIdTrans(QString&);
    void setIdStore(QString&);
    void setDate(QString&);
    void setPrices(QString&);
    void loadDetails(QMap<QString, QString> &);

private:
    QString id_trans;
    QString id_store;
    QString date;
    QString prices;
    QMap<QString, QString> map;
};


//QDataStream& operator<<(QDataStream& out, const Record& record)
//{
//    QMap<QString, QString> m = record.getDetails();
//    QString id_trans = record.getIdTrans();
//    QString id_store = record.getIdStore();
//    QString date = record.getDate();
//    QString prices =  record.getPrices();

////    out<<m.size();

////    QStringList qsl;
////    QMap<QString, QString>::iterator it;
////    for(it=m.begin(); it!=m.end(); ++it){
////        qsl<<it.key()<<it.value();
////    }

//    out<<m<<id_trans<<id_store<<date<<prices;

//    return out;
//}

#endif // RECORD_H
