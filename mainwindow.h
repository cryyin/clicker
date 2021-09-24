#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <QDebug>
#include <windows.h>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "pagerequester.h"
#include <ipaddressmanager.h>
#include <QList>

#include<cstdio>               //gets()函数
#include<cstdlib>              //system()函数
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void showMsg(QString Item,QString Msg);
    void DisplayMsg(int);


private:
    Ui::MainWindow *ui;
    pagerequester *requester;
    IpAddressManager *ipMa;

};
#endif // MAINWINDOW_H
