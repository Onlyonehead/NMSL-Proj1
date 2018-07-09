#include "processor.h"

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
        out << function;
    }

    if(function == "info_pB4"){
        QVector<QStringList> result;
        Warehouse::info(result);
        out << function;
        out << result;
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
        out << function;
        out << wordlist1;
        out << wordlist2;
    }
    if(function == "info_isA"){
        QVector<QStringList> result;
        Warehouse::info(result);
        out << function;
        out << result;
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

        QVector<QStringList> clothes;
        Warehouse::GInfo(clothes);

        out << function;
        out << warehouse;
        out << stock;
        out << arriving;
        out << clothes;
    }

    if(function == "pB5"){
        QMap<QString, QString> warehouse;
        Warehouse::info(warehouse);

        QVector<QMap<QString, QString>> stock;
        Warehouse::stock(stock);

        QVector<QMap<QString, QStringList>> arriving;
        Warehouse::arriving(arriving);

        QVector<QStringList> clothes;
        Warehouse::GInfo(clothes);

        out << function;
        out << warehouse;
        out << stock;
        out << arriving;
        out << clothes;
    }

    if(function == "iwhC"){
        QVector<QStringList> stock;
        Warehouse::stock(stock);
        QVector<QStringList> arriving;
        Warehouse::arriving(arriving);
        QVector<QStringList> clothes;
        Warehouse::GInfo(clothes);
        out << function;
        out << stock;
        out << arriving;
        out << clothes;
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

    if(function == "info_whEC3"){
        QVector<QStringList> result;
        Warehouse::GInfo(result);

        QStringList wordlist;

        for (QStringList list : result){
            wordlist << list.at(0) << list.at(1);
        }
        Tool::QStringList_removeDuplicates(&wordlist);
        out << function;
        out << wordlist;
    }

    if(function == "tWBiC"){
        QMap<QString, QString> warehouse;
        Warehouse::info(warehouse);
        QVector<QStringList> stock;
        Warehouse::stock(stock);
        QString s = list.at(0);

        QStringList result;
        Warehouse::GInfo(s.toInt(), result);
        out << function;
        out << warehouse;
        out << stock;
        out << result;

    }

    if(function == "isB"){
        QVector<QStringList> result;
        Warehouse::GInfo(result);
        out << function;
        out << result;
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




    out.device()->seek(0);
    out << (quint16) (message.size() - sizeof(quint16));
    qDebug() << function << endl;
    m_socket->write(message);
    m_socket->flush();
}
