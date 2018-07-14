#include "ftpmanager.h"
#include <QFileInfo>

ftpManager::ftpManager(QObject *parent)
    : QObject(parent)
{


    m_pUrl.setScheme("ftp");
}

void ftpManager::setHostPort(const QString &host, int port)
{
    m_pUrl.setHost(host);

    m_pUrl.setPort(port);
}

void ftpManager::setUserInfo(const QString &username, const QString &password)
{
    m_pUrl.setUserName(username);

    m_pUrl.setPassword(password);
}

void ftpManager::put(const QString &fileName, const QString &path)
{
    QFile file(fileName);
    file.open(QIODevice::ReadWrite);
    QByteArray data = file.readAll();

    qDebug() << file.size();
    qDebug() << data.size();

    m_pUrl.setPath(path);
    qDebug() << m_pUrl;

    QNetworkRequest putRequest;
    putRequest.setUrl(m_pUrl);

    QNetworkReply *putReply = m_manager.post(putRequest, data);
    Q_UNUSED(putReply);


    connect(putReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));




}



