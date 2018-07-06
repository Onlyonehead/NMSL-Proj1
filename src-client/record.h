#ifndef RECORD_H
#define RECORD_H


#include <QMap>

class Record
{
public:
    Record();
    Record(QString id_trans, QString id_store, QString date, QString prices):
        id_trans(id_trans), id_store(id_store), date(date), prices(prices){}
    void loadDetails(QMap<QString, QString>&);
    QString getIdTrans();
    QString getIdStore();
    QString getDate();
    QString getPrices();
    QMap<QString, QString> getDetails();
private:
    QString id_trans;
    QString id_store;
    QString date;
    QString prices;
    QMap<QString, QString> map;
};

#endif // RECORD_H
