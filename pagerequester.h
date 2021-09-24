#ifndef PAGEREQUESTER_H
#define PAGEREQUESTER_H

#include <QThread>
#include <iostream>
#include <string>
#include <QDebug>
#include <windows.h>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QObject>
#include <QEventLoop>
#include <QTimer>
#include <ipaddressmanager.h>
#include <QHash>
#include <QMessageBox>

#include<cstdio>               //gets()函数
#include<cstdlib>              //system()函数
using namespace std;


class pagerequester:public QThread
{
    Q_OBJECT
public:
    void begin();
    void stop();
    void setURL(char URLs[32767]);
    void setEpoch(int Epoch);
    bool getFlag();
    void setCycleflag(bool);
    void setClickGap(int);

protected:
    virtual void run();

private:
    bool startFlag=false;
    char siteURL[32767];
    int cycleNum=10;
    bool cycleflag=false;
    int clickGap=1000;
    QString lastip;
    QString nowip;
    IpAddressManager *ipMa;
    bool IPchanged=false;
    QList<QString> allIP;

signals:
    //void finished(QNetworkReply*);
    void SendMsgToWindow(QString Item,QString Msg);
    void TestSignal(int);

public slots:
    void replyFinished(QNetworkReply *reply);
};

#endif // PAGEREQUESTER_H
