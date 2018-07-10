#ifndef GARMENT_H
#define GARMENT_H
#include <QString>
#include <QVector>
#include <QStringList>


class Garment
{
public:
    Garment();

    //add garment form to database
    static void addGarmentForm(QString garmentStyle, QString garmentSize,QString garmentPic, QString garmentValue);

    static void Info(int i, QStringList&);//return garment info by ID

    static void Info(QVector<QStringList> &);//return all garment info

    static void Info(QString garmentStyle, QVector<QStringList> &);//return garment info by style

    static void updateGarmentInfo(int ID, QString alterAttribute, QString alterValue);//update garment information to database

private:
    int garmentID;

    QString garmentStyle;

    QString garmentSize;

    QString picPath;

    int value;

};

#endif // GARMENT_H
