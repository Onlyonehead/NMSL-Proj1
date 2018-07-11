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
            result.append("Clothes id:  " + l.at(0) + "\n- Style: "
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
            result1.append("Clothes id:  " + l.at(0) + "\n- Style: "
                           + l.at(1));
        }

        Tool::QStringList_removeDuplicates(&result1);

        QVector<QStringList> w;
        Warehouse::info(w);

        QStringList result2;

        for(QStringList l : w){
            result2.append("Warehouse id:  " + l.at(0) + "\n- Name: "
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

    if(function == "orderinfo"){
        QSqlQuery query;
        SQLTool::search(query, "orderInfo");
        QVector<QStringList> vlist;

        while(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append(query.value(3).toString());
            vlist.append(l);
        }

        QVector<QStringList> w;
        Warehouse::info(w);
        QStringList result2;

        for(QStringList l : w){
            result2.append("Warehouse id:  " + l.at(0) + "\n- Name: "
                         + l.at(1));
        }

        Tool::QStringList_removeDuplicates(&result2);
        out << function;
        out << vlist;
        out << result2;
    }

    if(function == "tWlAiC"){
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


    //system page show garment
    if(function == "sp_sg"){
        QVector<QStringList> result;
        Garment::Info(result);
        out << function;
        out << result;

    }
    //providerpage show provider info
    if(function == "pp_sp"){
        QVector<QStringList> result;
        Provider::Info(result);
        out << function;
        out << result;
    }
    //providerpage change provider info
    if(function == "pp_cpi"){
        QString tempID = list.at(0);
        int providerID = tempID.toInt();
        QString alterAttribute, alterValue;
        alterAttribute = "address";
        alterValue = list.at(1);
        Provider::updateProviderInfo(providerID, alterAttribute, alterValue);
        alterAttribute = "name";
        alterValue = list.at(2);
        Provider::updateProviderInfo(providerID, alterAttribute, alterValue);
        alterAttribute = "productInfo";
        alterValue = list.at(3);
        Provider::updateProviderInfo(providerID, alterAttribute, alterValue);
        out << function;
    }
    //personnel page 1 show staff info
    if(function == "pp1_ss"){
        QVector<QStringList> result;
        Staff::Info(result);
        out << function;
        out << result;
    }
    // personnel page 1 search staff info multi results
    if(function == "pp1_ssi"){
        QVector<QStringList> result;
        QString searchAttribute, searchValue;
        searchAttribute = list.at(0);
        searchValue = list.at(1);
        Staff::Info(searchAttribute, searchValue, result);
        out << function;
        out << result;
    }
    //personnel page 1 delete staff info
    if(function == "pp1_dsi"){
        QString username = list.at(0);
        Staff::deleteStaffInfo(username);
        out << function;
    }
    //personnel page 2 add new staff username
    if(function == "pp2_anu"){
        QString username = list.at(0);
        bool isExisted;
        if(Staff::isUsernameExisted(username)){
            isExisted = true;
        }else {
            isExisted = false;
        }
        out << function;
        out << isExisted;
    }
    //personnel page 2 check password
    if(function == "pp2_rp"){
        QString password, repeatPassword;
        password = list.at(0);
        repeatPassword = list.at(1);
        bool isSame;
        if(password == repeatPassword){
            isSame = true;
        }else {
            isSame = false;
        }
        out << function;
        out << isSame;
    }
    //personnel page 2 add new email
    if(function == "pp2_ane"){
        QString email = list.at(0);
        bool isExisted;
        if(Staff::isEmailExisted(email)){
            isExisted = true;
        }else {
            isExisted = false;
        }
        out << function;
        out << isExisted;
    }
    // purchase page show garment info
    if(function == "pcp_sg"){
        QVector<QStringList> result;
        Garment::Info(result);
        out << function;
        out << result;
    }
    //purchase page show garment detailed information
    if(function == "pcp_sgdi"){
        QStringList result;
        QString ID = list.at(0);
        Garment::Info(ID.toInt(), result);
        out << function;
        out << result;
    }


    //sissyVI--Start

    //系统
    if(function == "showStores"){
        out << function;
        QVector<QStringList> qv;
        Store::getStores(qv);

        out << qv;
    }

    if(function == "storesClicked"){
        out << function;
        QString store_id = list.at(0);
        int size;

        QVector<Record> qv_record;
        Store::getRecord(store_id.toInt(), size, qv_record);

        out<< size;//条目总数
        out << qv_record.size();//记录总数
        QVector<Record>::iterator it;
        for(it=qv_record.begin(); it!=qv_record.end(); ++it){
            out<<it->getIdTrans()<<it->getIdStore()<<it->getDate()<<it->getPrices();
            out<<it->getDetails();
        }
    }

    if(function == "getAllRequests"){
        out << function;
        QVector<QStringList> qv;
        Store::getAllPurchaseInfo(qv);
        out << qv;

    }

    if(function == "getCheckDetail"){
        out << function;
        QStringList qsl;
        QVector<QStringList> qv;
        Store::getPurchaseInfo(list.at(0), list.at(1), qsl, qv);
        out << qsl << qv;
    }

    if(function == "changeAmount"){
        out << function;

        Store::changePAmount(list.at(0), list.at(1), list.at(2));

        out << list.at(2);

    }

    if(function == "commitRequest"){
        out << function;

        QString purchase_id, store_id, time;
        purchase_id = list.at(0);
        store_id = "S"+list.at(1);
        time = list.at(2);
        list.removeFirst();
        list.removeFirst();
        list.removeFirst();

        SQLTool::update("store_pRecord", "checked", "1", "id_purchase", purchase_id);
        SQLTool::update("store_pRecord", "date_check", time, "id_purchase", purchase_id);

        Order order(store_id, time, list);
        Warehouse::sendRequirement(order);

        out << "success";
    }

    //门店
    if(function == "getRecord"){
        out << function;
        QString store_id = list.at(0);
        int size;

        QVector<Record> qv_record;
        Store::getRecord(store_id.toInt(), size, qv_record);

        out << qv_record.size();
        QVector<Record>::iterator it;
        for(it=qv_record.begin(); it!=qv_record.end(); ++it){
            out<<it->getIdTrans()<<it->getIdStore()<<it->getDate()<<it->getPrices();
            out<<it->getDetails();
        }

        out<< size;

    }

    if(function == "getStoreInfo"){
        out << function;
        QString username, size;
        username = list.at(0);
        size = list.at(1);
        QVector<QString> qv;
        Store::getStoreInfo(username, size, qv);
        out << qv;
    }

    if(function == "getStock"){
        out << function;
        QVector<QVector<QString> > qv;
        Store::getStock(list.at(0), qv);
        out << qv;
    }

    if(function == "sellGoods"){
        out << function;
        int i=2;
        QVector<int> qv;
        while(list.at(i) != "#"){
            QString s1, s2;
            s1 = list.at(i++);
            s2 = list.at(i++);
            qv.append(s1.toInt());qv.append(s2.toInt());
        }
        if(Store::sellGoods(list.at(0), list.at(1), qv))
            out << QString("交易成功");
        else
            out << QString("交易失败");
        QString store_id = list.at(0);

        //getStock
        QVector<QVector<QString> > qv1;
        Store::getStock(store_id, qv1);
        out << qv1;

        //getRecord
        int size;

        qDebug()<<"店铺ID为："<<store_id;
        QVector<Record> qv_record;
        Store::getRecord(store_id.toInt(), size, qv_record);
        qDebug()<<"记录大小为："<<qv_record.size();

        out << qv_record.size();
        QVector<Record>::iterator it;
        for(it=qv_record.begin(); it!=qv_record.end(); ++it){
            out<<it->getIdTrans()<<it->getIdStore()<<it->getDate()<<it->getPrices();
            out<<it->getDetails();
        }

        out<< size;

    }

    if(function == "MainWindowInit"){
        out << function;

        //getAllClothes
        QVector<QStringList> qv;
        Store::getAllClothes(qv);
        out << qv;

        //getStock
        QVector<QVector<QString> > qv1;
        Store::getStock(list.at(0), qv1);
        out << qv1;

        //getRecord
        QString store_id = list.at(0);
        int size;

        qDebug()<<"店铺ID为："<<store_id;
        QVector<Record> qv_record;
        Store::getRecord(store_id.toInt(), size, qv_record);
        qDebug()<<"记录大小为："<<qv_record.size();

        out << qv_record.size();
        QVector<Record>::iterator it;
        for(it=qv_record.begin(); it!=qv_record.end(); ++it){
            out<<it->getIdTrans()<<it->getIdStore()<<it->getDate()<<it->getPrices();
            out<<it->getDetails();
        }

        out<< size;
    }

    if(function == "sendRequest"){
        out << function;

        QMap<QString, QString> m;
        in >> m;
        Store::purchase(list.at(0), m);

        QString message = "request complete";
        out << message;
    }

    if(function == "getRequests"){
        QVector<QStringList> qv;
        QMap<QString, QMap<QString, QString>> m;
        Store::getPurchaseInfo(list.at(0), qv, m);

        out << function << qv << m;
    }

    if(function == "test_sell"){

//        QStringList qsl;
//        qsl.append("test_sell");

//        QString store_id = "1";
//        QString time_com = "2018-07-11 14:38:47";

//        QVector<QMap<QString, QStringList>> qv;
//        QMap<QString, QStringList> qm;
//        QStringList qsl_m;
//        qsl_m << QString("1") << QString("200");
//        qm.insert(QString("10"), qsl_m);
//        qv.append(qm);

//        QMap<QString, QString> m;
//        m.insert(QString("10"), QString("2018-07-11 18:27:50"));



//        QByteArray message;
//        QDataStream out(&message,QIODevice::WriteOnly);
//        out.setVersion(QDataStream::Qt_5_7);
//        out << (quint16) 0;

//        out << qsl;
//        out << store_id << time_com << qv << m;

//        out.device()->seek(0);
//        out << (quint16) (message.size() - sizeof(quint16));
//        m_tcpsocket->write(message);


        out << function;
        QString store_id;
        QString time_com;
        QVector<QMap<QString, QStringList>> qv;
        QMap<QString, QString> m;
        in >> store_id >> time_com >> qv >> m;
        Store::storeArrive(store_id, time_com, qv, m);

        out << "success";
    }

    if(function == "requestReject"){
        out << function;

        //将chencked的值设为2，代表请求被拒
        SQLTool::update("store_pRecord", "checked", "2", "id_purchase", list.at(0));

        out << "rejected";
    }

    //sissyVI--Finish

    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    qDebug() << function << endl;
    m_socket->write(message);
    m_socket->flush();
}
