#include "ipaddressmanager.h"

IpAddressManager::IpAddressManager()
{

}

QString IpAddressManager::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
               break;
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}


QString IpAddressManager::getOutIpAddress()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("http://www.net.cn/static/customercare/yourip.asp")));
    QEventLoop eventLoop;
    QTimer m_timer;
    QString data1;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    QObject::connect(&m_timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    eventLoop.exec();
    m_timer.start(5000);
    if(m_timer.isActive())
    {
        m_timer.stop();
        QString data = reply->readAll();
        int len1 = data.indexOf("<h2>");
        int len2 = data.indexOf("</h2>");
        data1 = data.mid(len1+4,len2-len1-4);
    }
    eventLoop.deleteLater();
    m_timer.deleteLater();
    delete manager;
    return data1;//公网IP

}
