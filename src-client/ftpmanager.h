#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QUrl>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class ftpManager : public QObject
{
    Q_OBJECT
public:
    explicit ftpManager(QObject *parent = 0);

    void setHostPort(const QString &host, int port = 21);

    void setUserInfo(const QString &username, const QString password);

    void put(const QString &fileName, const QString &path);


signals:
    void error(QNetworkReply::NetworkError);

private:
    QUrl m_pUrl;

    QFile m_file;

    QNetworkAccessManager m_manager;

};

#endif // FTPMANAGER_H
