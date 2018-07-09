#include "processor.h"
#include <QDateTime>

Processor::Processor(QTcpSocket* socket)
{
    this->m_socket = socket;
}

void Processor::work ()
{
    QDataStream in(m_socket);
    in.setVersion (QDataStream::Qt_5_7);
    quint16 blocksize = 0;
    if (m_socket->bytesAvailable() < (int)sizeof(quint16)){
        return;

    }
    in >> blocksize;

    if(m_socket->bytesAvailable() < blocksize){
        return;
    }

    QStringList list;
    in >> list;

    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);

    QString function = list.at(0);
    list.removeFirst();

    out << (quint16) 0;

    /*
     * H-ZC
     *
     */

    if(function == "Default"){
        out << "Default";
    }

    if(function == "login"){
        QString username = list.at(0);
        QString password = list.at(1);
        int result = Login::login(username, password);
        out << function;
        out << result;

    }
    if(function == "info"){
        QStringList result = Login::info(list.at(0));
        out << function;
        out << result;

    }

    if(function == "send"){
        QString username = list.at(0);
        QString email = list.at(1);
        QString securityCode = list.at(2);
        int result = ForgetPassword::sendCode(username, email, securityCode);
        out << function;
        out << result;

    }

    if(function == "check"){
        QString username = list.at(0);
        QString pw1 = list.at(1);
        QString pw2 = list.at(2);
        QString code = list.at(3);
        QString securityCode = list.at(4);
        int result = ForgetPassword::checkCode(username, pw1, pw2, code, securityCode);
        out << function;
        out << result;

    }
    if(function == "transfer"){
        Warehouse::transfer();

        QVector<QStringList> stock;
        Warehouse::stock(stock);
        QVector<QStringList> arriving;
        Warehouse::arriving(arriving);
        QVector<QStringList> clothes;
        Warehouse::GInfo(clothes);
        QVector<QStringList> warehouse;
        Warehouse::info(warehouse);
        QMap<QString, QMap<QString, QString>> stock_map;
        Warehouse::stock(stock_map);
        QMap<QString, QMap<QString, QStringList>> arriving_map;
        Warehouse::arriving(arriving_map);
        out << function;
        out << stock;
        out << arriving;
        out << clothes;
        out << warehouse;
        out << stock_map;
        out << arriving_map;
    }

    if(function == "info_whEC"){
        QVector<QStringList> result;
        Warehouse::info(result);

        QStringList wordlist1;
        for (QStringList list : result){
            wordlist1 << list.at(0) << list.at(1) <<
                    list.at(2) << list.at(3) <<
                    list.at(4) << list.at(5);
        }
        Tool::QStringList_removeDuplicates(&wordlist1);

        QStringList wordlist2;
        for (QStringList list : result){
            wordlist2 << list.at(0) << list.at(1);
        }
        Tool::QStringList_removeDuplicates(&wordlist2);

        QVector<QStringList> result2;
        Warehouse::GInfo(result2);

        QStringList wordlist3;

        for (QStringList list : result2){
            wordlist3 << list.at(0) << list.at(1);
        }
        Tool::QStringList_removeDuplicates(&wordlist3);

        QStringList wordlist4 = wordlist2 + wordlist3;
        Tool::QStringList_removeDuplicates(&wordlist4);

        out << function;
        out << wordlist1;
        out << wordlist2;
        out << wordlist3;
        out << wordlist4;
    }
    if(function == "isC"){
        QVector<QStringList> w;
        Warehouse::info(w);

        QString text = list.at(0);
        int id;
        for (QStringList list : w){
            if(list.at(0) == text || list.at(1) == text){
                id = list.at(0).toInt();
                break;
            }
        }

        QStringList warehouse;
        Warehouse::info(id, warehouse);

        QMap<QString, QString> stock;
        Warehouse::stock(id, stock);

        QMap<QString, QStringList> arriving;
        Warehouse::arriving(id, arriving);

        out << function;
        out << warehouse;
        out << stock;
        out << arriving;
    }

    if(function == "pB5"){
        QMap<QString, QString> warehouse;
        Warehouse::info(warehouse);


        out << function;
        out << warehouse;
    }

    if(function == "pB8"){
        QVector<QStringList> g;
        Warehouse::GInfo(g);

        QStringList result;

        for(QStringList l : g){
            result.append("   " + l.at(0) + " - "
                         + l.at(1));
        }

        Tool::QStringList_removeDuplicates(&result);
        out << function;
        out << result;
    }


    if(function == "tWBiC"){
        QMap<QString, QString> warehouse;
        Warehouse::info(warehouse);
        QString s = list.at(0);

        QStringList result;
        Warehouse::GInfo(s.toInt(), result);
        out << function;
        out << warehouse;
        out << result;

    }

    if(function == "sendOrder"){
        QString orderID = list.at(0);
        list.removeFirst();
        QString datetime = list.at(0);
        list.removeFirst();
        QStringList productInfo;
        for(QString s : list){
            productInfo.append(s);
        }

        Order order(orderID, datetime, productInfo);
        Warehouse::sendRequirement(order);
        out << function;
        out << QString("done");
    }

    if(function == "pB10"){
        QVector<QStringList> g;
        Warehouse::GInfo(g);

        QStringList result1;

        for(QStringList l : g){
            result1.append("   " + l.at(0) + " - "
                         + l.at(1));
        }

        Tool::QStringList_removeDuplicates(&result1);

        QVector<QStringList> w;
        Warehouse::info(w);

        QStringList result2;

        for(QStringList l : w){
            result2.append("   " + l.at(0) + " - "
                         + l.at(1));
        }

        Tool::QStringList_removeDuplicates(&result2);


        out << function;
        out << result1;
        out << result2;
    }

    if(function == "tWD1iC"){
        QString s = list.at(0);

        QStringList result;
        Warehouse::GInfo(s.toInt(), result);
        out << function;
        out << result;

    }

    if(function == "tWD2iC"){
        QString s = list.at(0);

        QMap<QString, QString> result;
        Warehouse::stock(s.toInt(), result);

        QVector<QStringList> g;
        Warehouse::GInfo(g);

        QMap<QString, QString> result1;

        for(QStringList l : g){
            result1.insert(l.at(0), l.at(1));
        }
        out << function;
        out << result;
        out << result1;
    }
    if(function == "order_send"){
        QMap<QString, QMap<QString, QString>> orders;
        in >> orders;

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");

        for(QMap<QString, QMap<QString, QString>>::const_iterator i
            = orders.begin(); i != orders.end(); ++i){
            QStringList productInfo;
            for(QMap<QString, QString>::const_iterator j
                = i.value().begin(); j != i.value().end(); ++j){
                productInfo.append(j.key());
                productInfo.append(j.value());
            }
            Order order(i.key(), time, productInfo);
            Warehouse::sendRequirement(order);

        }
        QString msg = "Done";
        out << function;
        out << msg;
    }

    if(function == "wh_history"){
        QString id = list.at(0);
        QVector<QStringList> result;
        QSqlQuery query1;
        SQLTool::search(query1, "wh_history", "from_id", id);
        QSqlQuery query2;
        SQLTool::search(query2, "wh_history", "to_id", id);

        while(query1.next()){
            QStringList l;
            l.append(query1.value(0).toString());
            l.append(query1.value(1).toString());
            l.append(query1.value(2).toString());
            l.append(query1.value(3).toString());
            result.append(l);
        }
        while(query2.next()){
            QStringList l;
            l.append(query2.value(0).toString());
            l.append(query2.value(1).toString());
            l.append(query2.value(2).toString());
            l.append(query2.value(3).toString());
            result.append(l);
        }

        out << function;
        out << result;
    }
    if(function == "wh_history_all"){
        QVector<QStringList> result;
        QSqlQuery query;
        SQLTool::search(query, "wh_history");

        while(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append(query.value(3).toString());
            result.append(l);
        }
        out << function;
        out << result;
    }

    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    qDebug() << function << endl;
    m_socket->write(message);
    m_socket->flush();
}
