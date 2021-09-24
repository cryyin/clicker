#ifndef IPADDRESSMANAGER_H
#define IPADDRESSMANAGER_H


#include <iostream>
#include <string>
#include <QDebug>
#include <windows.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QNetworkInterface>
#include <QEventLoop>
#include <QTimer>

#include<cstdio>               //gets()函数
#include<cstdlib>              //system()函数
using namespace std;

class IpAddressManager
{
public:
    IpAddressManager();
    QString getHostIpAddress();
    QString getOutIpAddress();
};

#endif // IPADDRESSMANAGER_H
