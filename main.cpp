#include "mainwindow.h"
#include <iostream>
#include <string>
#include <windows.h>
#include<cstdio>               //gets()函数
#include<cstdlib>              //system()函数
using namespace std;
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
