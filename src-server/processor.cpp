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

    qDebug() << function << endl;

    out << (quint16) 0;

    /*
     * hzc
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
        QMap<QString, QString> warehouse_map;
        Warehouse::info(warehouse_map);
        QVector<QStringList> stores;
        Store::getStores(stores);

        QSqlQuery query;
        SQLTool::search(query, "orderInfo");
        int count_ongoing = query.size();
        SQLTool::search(query, "orderChecked");
        int count_dealt = 0;
        int count_rejected = 0;

        while(query.next()){
            if(query.value(3).toString() == "REJECTED"){
                count_rejected++;
            }else{
                count_dealt++;
            }
        }

        out << function;
        out << stock;
        out << arriving;
        out << clothes;
        out << warehouse;
        out << stock_map;
        out << arriving_map;
        out << warehouse_map;
        out << stores;
        out << count_dealt;
        out << count_ongoing;
        out << count_rejected;
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
            if(list.at(0).contains(text, Qt::CaseInsensitive) ||
                    list.at(1).contains(text, Qt::CaseInsensitive)){
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


        out << function;
        out << vlist;

    }
    if(function == "tWlAiC"){
        QVector<QStringList> w;
        Warehouse::info(w);
        QStringList result2;

        for(QStringList l : w){
            result2.append("Warehouse id:  " + l.at(0) + "\n- Name: "
                           + l.at(1));
        }

        Tool::QStringList_removeDuplicates(&result2);

        out << function;
        out << result2;
    }

    if(function == "send_replenishment"){
        QString warehouse_id;
        QString order_id;
        QMap<QString, QMap<QString, QString>> replenishment;

        QString order_time;

        in >> order_id;
        in >> warehouse_id;
        in >> replenishment;
        in >> order_time;

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString time = current_date_time.addDays(2).addSecs(10000).
                addMSecs(warehouse_id.toInt() * 1000000).toString("yyyy-MM-dd hh:mm:ss");



        QStringList s_for_infochecked;

        for(QMap<QString, QMap<QString, QString>>::const_iterator i
            = replenishment.begin(); i != replenishment.end(); ++i){
            QStringList l;
            for(QMap<QString, QString>::const_iterator j
                = i.value().begin(); j != i.value().end(); ++j){
                l.append(j.key());
                l.append(j.value());
                s_for_infochecked.append(i.key());
                s_for_infochecked.append(j.key());
                s_for_infochecked.append(j.value());
            }
            Order order(i.key(), time, l);
            QByteArray ba = warehouse_id.split("-")[0].trimmed().toLatin1();
            const char *s = ba.data();

            if(*s == 'S'){
                Store::storeArrive(warehouse_id.split("-")[0].trimmed().split(QRegExp("[A-Z]"))[1], order_time, order);
            }else{
                Warehouse::replenish(warehouse_id.split("-")[0].trimmed(), order);
            }
            QString id = order.getId();
            order.editInfo(warehouse_id.split("-")[0].trimmed(), order.getDatetime(), order.getProductInfo());
            Warehouse::deliverGoods(id, order);
        }
        QSqlQuery query;
        SQLTool::search(query, "orderInfo", "order_id", order_id);
        if(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append(s_for_infochecked.join("#"));
            SQLTool::insert("orderChecked", l);
            SQLTool::del("orderInfo", "order_id", order_id);
        }
        out << function;
        out << QString("Done");
    }

    if(function == "orderCheckedInfo"){
        QSqlQuery query;
        SQLTool::search(query, "orderChecked");
        QVector<QStringList> vlist;

        while(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append(query.value(3).toString());
            vlist.append(l);
        }


        out << function;
        out << vlist;
    }

    if(function == "del_orderChecked"){
        QString id = list.at(0);

        QSqlQuery query;
        SQLTool::search(query, "orderChecked", "order_id", id);

        SQLTool::del("orderChecked", "order_id", id);
        out << function;
        if(query.next()){
            if(query.value(3).toString() == "REJECTED"){
                out << QString("REJECTED");
            }else{
                out << QString("Done");
            }
        }
    }

    if(function == "reject_order"){
        QString order_id = list.at(0);
        QSqlQuery query;
        SQLTool::search(query, "orderInfo", "order_id", order_id);
        if(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append("REJECTED");
            SQLTool::insert("orderChecked", l);
            SQLTool::del("orderInfo", "order_id", order_id);
        }
        out << function;
        out << QString("Done");
    }

    if(function == "reject_order_D"){
        QString order_id = list.at(0);
        QSqlQuery query;
        SQLTool::search(query, "orderInfo", "order_id", order_id);
        if(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append("REJECTED");
            SQLTool::insert("orderChecked", l);
            SQLTool::del("orderInfo", "order_id", order_id);
        }
        out << function;
        out << QString("Done");
    }

    if(function == "add_warehouse"){
        QString name = list.at(0);
        QString province = list.at(1);
        QString city = list.at(2);
        QString address = list.at(3);
        QString position_x = list.at(4);
        QString position_y = list.at(5);
        QStringList l;
        l.append("0");
        l.append(name);
        l.append(province);
        l.append(city);
        l.append(address);
        l.append("分仓库");
        l.append(position_x);
        l.append(position_y);
        SQLTool::insert("warehouse", l);
        out << function;
        out << QString("Done");
        out << l;

    }

    if(function == "edit_warehouse"){
        QString id = list.at(0);
        QString name = list.at(1);
        QString province = list.at(2);
        QString city = list.at(3);
        QString address = list.at(4);
        QString position_x = list.at(5);
        QString position_y = list.at(6);
        QStringList l;
        l.append("id");
        l.append(id);
        SQLTool::update("warehouse","name", name, l);
        SQLTool::update("warehouse","province", province, l);
        SQLTool::update("warehouse","city", city, l);
        SQLTool::update("warehouse","address", address, l);
        SQLTool::update("warehouse","position_x", position_x, l);
        SQLTool::update("warehouse","position_y", position_y, l);

        QStringList msg;
        msg.append(id);
        msg.append(name);
        msg.append(province);
        msg.append(city);
        msg.append(address);
        msg.append("分仓库");
        msg.append(position_x);
        msg.append(position_y);
        out << function;
        out << QString("Done");
        out << msg;
    }

    if(function == "del_warehouse"){
        QString id = list.at(0);
        SQLTool::del("warehouse", "id", id);
        out << function;
        out << QString("Done");
        out << id;
    }

    if(function == "orderinfo_D"){
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


        out << function;
        out << vlist;
    }

    if(function == "auto_replenish"){
        QString warehouse_id;
        QString order_id;
        QMap<QString, QMap<QString, QString>> replenishment;

        QString order_time;


        in >> order_id;
        in >> warehouse_id;
        in >> replenishment;
        in >> order_time;

        QDateTime current_date_time = QDateTime::currentDateTime();

        QStringList s_for_infochecked;

        for(QMap<QString, QMap<QString, QString>>::const_iterator i
            = replenishment.begin(); i != replenishment.end(); ++i){
            QStringList l;
            QString time;
            for(QMap<QString, QString>::const_iterator j
                = i.value().begin(); j != i.value().end(); ++j){
                if(j.key() == "duration"){
                    time = current_date_time.addSecs(j.value().toInt()).toString("yyyy-MM-dd hh:mm:ss");
                }else{
                    l.append(j.key());
                    l.append(j.value());
                    s_for_infochecked.append(i.key());
                    s_for_infochecked.append(j.key());
                    s_for_infochecked.append(j.value());
                }
            }
            Order order(i.key(), time, l);
            QByteArray ba = warehouse_id.split("-")[0].trimmed().toLatin1();
            const char *s = ba.data();

            if(*s == 'S'){
                Store::storeArrive(warehouse_id.split("-")[0].trimmed().split(QRegExp("[A-Z]"))[1], order_time, order);
            }else{
                Warehouse::replenish(warehouse_id.split("-")[0].trimmed(), order);
            }
            QString id = order.getId();
            order.editInfo(warehouse_id.split("-")[0].trimmed(), order.getDatetime(), order.getProductInfo());
            Warehouse::deliverGoods(id, order);
        }
        QSqlQuery query;
        SQLTool::search(query, "orderInfo", "order_id", order_id);
        if(query.next()){
            QStringList l;
            l.append(query.value(0).toString());
            l.append(query.value(1).toString());
            l.append(query.value(2).toString());
            l.append(s_for_infochecked.join("#"));
            SQLTool::insert("orderChecked", l);
            SQLTool::del("orderInfo", "order_id", order_id);
        }
        out << function;
        out << QString("Done");
    }




    //system page add new garment
    if(function == "sp_confirmAddG"){
        QString garmentSytle = list.at(0);
        list.removeFirst();
        QString garmentPic = list.at(0);
        list.removeFirst();
        QString garmentPrice = list.at(0);
        list.removeFirst();
        for(int i = 0; i < list.size(); i++){
            QString garmentSize = list.at(i);
            Garment::addGarmentForm(garmentSytle, garmentSize, garmentPic, garmentPrice);
        }

        QVector<QStringList> garmentInfo;

        Garment::Info(garmentSytle, garmentInfo);

        out << function;
        out << garmentInfo;
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
    //provider page add new provider
    if(function == "pp_api"){
        QString providerAds = list.at(0);
        QString providerName = list.at(1);
        QString providerProduct = list.at(2);
        Provider::addNewPrvider(providerName, providerAds, providerProduct);
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
        QString searchValue;
        searchValue = list.at(0);
        QVector<QStringList> staffInfo;
        QSqlQuery query;
        QStringList list;
        QStringList l = {"username", "name", "gender", "position", "email"};
        for(QString s : l){
            SQLTool::fuzzySearch(query, "userdata", s, searchValue);
            while (query.next()) {
                list.clear();
                list.append(query.value(0).toString());
                list.append(query.value(1).toString());
                list.append(query.value(2).toString());
                list.append(query.value(3).toString());
                list.append(query.value(4).toString());
                list.append(query.value(5).toString());
                list.append(query.value(6).toString());
                staffInfo.append(list);
            }
        }

        out << function;
        out << staffInfo;
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
    //personnel page 2 confirm add new staff
    if(function == "pp2_cns"){
        QString username = list.at(0);
        QString password = list.at(1);
        QString name = list.at(2);
        QString gender = list.at(3);
        QString position = list.at(4);
        QString email = list.at(5);
        QString userPic = list.at(6);
        qDebug() << position <<endl;
        qDebug() << email << endl;
        Staff::addNewStaff(username, password, name, gender,
                           position, email, userPic);
        out << function;
    }
    // personnel page 3 show staff
    if(function == "pp3_upss"){
        QVector<QStringList> result;
        Staff::Info(result);
        out << function;
        out << result;
    }
    // personnel page 3 update staff information
    if(function == "pp3_csi"){
        QString username = list.at(0);
        QString name = list.at(1);
        QString gender = list.at(2);
        QString position = list.at(3);
        QString email = list.at(4);
        Staff::updateStaffInfo(username, "name", name);
        Staff::updateStaffInfo(username, "gender", gender);
        Staff::updateStaffInfo(username, "position", position);
        Staff::updateStaffInfo(username, "email", email);
        out << function;
    }
    // personnel page 4 check if email exists
    if(function == "pp4_ise"){
        QString email = list.at(0);
        bool isEmailExisted = Staff::isEmailExisted(email);
        out << function;
        out << isEmailExisted;
    }
    // personnel page 4 check if old password right
    if(function == "pp4_cop"){
        QString email = list.at(0);
        QString oldPassword = list.at(1);
        QVector<QStringList> result;
        Staff::Info("email", email, result);
        if(result.isEmpty()){
            return ;
        }
        bool isPasswordRight;
        if(oldPassword == result.at(0).at(1)){
            isPasswordRight = true;
        }else {
            isPasswordRight = false;
        }
        out << function;
        out << isPasswordRight;

    }
    //personnel page 4 update staff information
    if(function == "pp4_csp"){
        QString email = list.at(0);
        QString newPassword = list.at(1);
        QString newUsername = list.at(2);
        Staff::alterStaffUsername(email, newUsername);
        Staff::updateStaffInfo(newUsername, "password", newPassword);
        QSqlQuery query;
        SQLTool::search(query, "userdata", "email", email);
        query.next();
        out << function;
        out << newUsername;
        out << query.value(0).toString();
    }
    // purchase page show garment info
    if(function == "pcp_sg"){
        QVector<QStringList> result;
        Garment::Info(result);
        out << function;
        out << result;
    }
    //deliver page show all providers IDs
    if(function == "dp_sp"){
        QVector<QStringList> result;
        Provider::Info(result);
        out << function;
        out << result;

    }
    //deliver page show provider detailde information
    if(function == "dp_spdi"){
        QStringList result;
        QString ID = list.at(0);
        Provider::Info(ID.toInt(), result);
        out << function;
        out << result;
    }
    //deliver page deliver order & save order in table providerOrder
    if(function == "dp_do"){
        QSqlQuery query;
        int tempID;
        QString providerID = list.at(0);
        QString datetime = list.at(1);
        QString productTectmpInfo = list.at(2);
        QString isFirstOrder = list.at(3);
        QStringList productInfo = productTectmpInfo.split("#");
        Order providerOrder(providerID, datetime, productInfo);
        QString providerOrderID;

        if(isFirstOrder == "Y"){
            SQLTool::search(query, "orderID", "providerOrder");
            query.last();
            tempID = query.value(0).toInt();
            tempID ++;
            providerOrderID = QString::number(tempID);
        }else {
            SQLTool::search(query, "orderID", "providerOrder");
            query.last();
            providerOrderID = query.value(0).toString();
        }
        Order::saveProviderOrder(providerOrderID, providerOrder);
        QDateTime changeDatetime = QDateTime::fromString(datetime, "yyyy-MM-dd hh:mm:ss");
        QString arriveDatetime = changeDatetime.addDays(3).toString("yyyy-MM-dd hh:mm:ss");
        providerOrder.editInfo(providerID, arriveDatetime, productInfo);
        QString warehouseID = "1";
        Warehouse::replenish(warehouseID, providerOrder);
        out << function;
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

        QVector<QStringList> qv_record;
        QMap<QString, QMap<QString, QString> > qm_detail;
        Store::getRecord(store_id, size, qv_record, qm_detail);

        out<< size;//条目总数
        out << qv_record.size();//记录总数
        QVector<QStringList>::const_iterator it;
        for(it=qv_record.constBegin(); it!=qv_record.constEnd(); ++it){
            out << it->at(0) << it->at(1) << it->at(2) << it->at(3);
            out << qm_detail.value(it->at(0));
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
        QVector<QStringList> qv;
        Store::getPurchaseInfo(list.at(0), list.at(1), qv);
        out << list.at(1) <<  qv;
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

        QVector<QStringList> qv_record;
        QMap<QString, QMap<QString, QString> > qm_detail;
        Store::getRecord(store_id, size, qv_record, qm_detail);

        out << qv_record.size();//记录总数
        QVector<QStringList>::const_iterator it;
        for(it=qv_record.constBegin(); it!=qv_record.constEnd(); ++it){
            out << it->at(0) << it->at(1) << it->at(2) << it->at(3);
            out << qm_detail.value(it->at(0));
        }

        out<< size;

    }

    if(function == "MainWindowInit"){
        out << function;

        //readStoreArrive
        Store::readStoreArrive(list.at(0));

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

        QVector<QStringList> qv_record;
        QMap<QString, QMap<QString, QString> > qm_detail;
        Store::getRecord(store_id, size, qv_record, qm_detail);

        out << qv_record.size();//记录总数
        QVector<QStringList>::const_iterator it;
        for(it=qv_record.constBegin(); it!=qv_record.constEnd(); ++it){
            out << it->at(0) << it->at(1) << it->at(2) << it->at(3);
            out << qm_detail.value(it->at(0));
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

    if(function == "test_cc"){

        QStringList list1;
        list1.append("1");
        list1.append("100");
        list1.append("3");
        list1.append("300");

        Order order1("5", "2020-03-03 12:22:21", list1);


        out << function;
        QString store_id = "1";
        QString time_com = "2018-07-11 14:38:47";
        Store::storeArrive(store_id, time_com, order1);

        out << "success";
    }

    if(function == "requestReject"){
        out << function;

        //将chencked的值设为2，代表请求被拒
        SQLTool::update("store_pRecord", "checked", "2", "id_purchase", list.at(0));

        out << "rejected";
    }

    if(function == "getArriveRecord"){
        out << function;

        QString store_id = list.at(0);
        QVector<QStringList> qv;
        QSqlQuery sq;
        QStringList qsl;
        qsl.append("id_purchase");
        qsl.append("checked");
        qsl.append("date_check");
        SQLTool::search(sq, qsl, "store_pRecord", "id_store", store_id);
        while(sq.next()){
            if(sq.value(1).toString()!="0"){
                QStringList qsla;
                qsla.append(sq.value(0).toString());
                qsla.append(sq.value(1).toString());
                qsla.append(sq.value(2).toString());
                qv.append(qsla);
            }
        }

        out << qv;
    }

    if(function == "getArriveDetail"){
        out << function;

        QString purchase_id = list.at(0);
        QMap<QString, QVector<QStringList> > qm;
        QMap<QString, QString> qmt;
        int size;
        QStringList qsl;
        qsl.append("id_from");
        qsl.append("date_arrive");
        qsl.append("id_clothes");
        qsl.append("quantity");
        QSqlQuery sq;
        SQLTool::search(sq, qsl, "store_arriving", "id_purchase", purchase_id);
        size = sq.size();
        while(sq.next()){
            QStringList qsld;
            qsld.append(sq.value(2).toString());
            qsld.append(sq.value(3).toString());
            if(qm.contains(sq.value(0).toString())){
                QVector<QStringList> qv = qm.value(sq.value(0).toString());
                qv.append(qsld);
                qm.insert(sq.value(0).toString(), qv);
            }else{
                QVector<QStringList> qv;
                qv.append(qsld);
                qm.insert(sq.value(0).toString(), qv);

                qmt.insert(sq.value(0).toString(), sq.value(1).toString());
            }
        }

        out << size << qm << qmt;
    }

    if(function == "changeUserName"){
        out << function;
        QSqlQuery sq;
        QStringList users;
        sq.exec("SELECT username FROM userdata WHERE username NOT IN (SELECT username FROM store)");
        while (sq.next())
            users.append(sq.value(0).toString());

        out << users;
    }

    if(function == "changeUserName2"){
        out << function;
        QSqlQuery sq;
        QStringList users;
        sq.exec("SELECT username FROM userdata WHERE username NOT IN (SELECT username FROM store)");
        while (sq.next())
            users.append(sq.value(0).toString());

        out << users;
    }

    if(function == "storeInfoChange"){
        out << function;

        QSqlQuery sq;
        SQLTool::search(sq, "position", "userdata", "username", list.at(5));
        sq.next();
        SQLTool::update("userdata", "position", sq.value(0).toString(), "username", list.at(6));
        SQLTool::update("userdata", "position", "门店人员", "username", list.at(5));

        QString sql = "update store set name='"+list.at(1)+"',province='"+list.at(2)+"',city='"+list.at(3)+"',address='"+list.at(4)+"',username='"+list.at(5)+"' where id_store='"+list.at(0)+"'";
        sq.exec(sql);
    }

    if(function == "reloadStores"){
        out << function;
        QVector<QStringList> qv;
        Store::getStores(qv);

        out << qv;
    }

    if(function == "createStore"){

        QString name, province, city, address, username;
        name = list.at(0);list.removeFirst();
        province = list.at(0);list.removeFirst();
        city = list.at(0);list.removeFirst();
        address = list.at(0);list.removeFirst();
        username = list.at(0);list.removeFirst();

        QStringList qsl;
        qsl<<"0"<<name<<province<<city<<address<<username<<"121.6216"<<"29.859515";
        SQLTool::insert("store", qsl);

        QSqlQuery sq;
        SQLTool::search(sq,"id_store", "store", "username", username);
        sq.next();
        QString store_id = sq.value(0).toString();

        QStringList qsl2;
        for(int i=0; i<list.size();){
            qsl2.clear();
            qsl2.append(store_id);
            qsl2.append(list.at(i++));
            qsl2.append(list.at(i++));
            SQLTool::insert("store_warehouse", qsl2);
        }

        QDateTime current_date_time = QDateTime::currentDateTime();
        QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
        QStringList qsl3;
        qsl3 << store_id << time;
        SQLTool::insert("store_check", qsl3);

        SQLTool::update("userdata", "position", "门店人员", "username", username);

        out << function;
        out << QString("Done");
    }

    //sissyVI--Finish

    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    m_socket->write(message);
    m_socket->flush();
}
