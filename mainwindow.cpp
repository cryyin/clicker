#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegularExpression regx("[1-9][0-9]+$");                                             //输入容错
    QValidator *validator = new QRegularExpressionValidator(regx, ui->lineEdit_2 );
    QValidator *validator2 = new QRegularExpressionValidator(regx, ui->lineEdit_3 );
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator2);
    requester = new pagerequester();//连接消息信号槽
    //connect(requester, SIGNAL(TestSignal(int)), this, SLOT(DisplayMsg(int)));
    connect(requester, SIGNAL(SendMsgToWindow(QString,QString)), this, SLOT(showMsg(QString,QString)));
    requester->start();
    ipMa =new IpAddressManager();
    ui->label_6->setText(ipMa->getOutIpAddress());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showMsg(QString Item,QString Msg)
{
    if(Item=="textEdit"){
        ui->textEdit->append(Msg);
    }else if(Item=="textEdit_2"){
        ui->textEdit_2->append(Msg);
    }else if(Item=="label_7"){
        ui->label_7->setText(Msg);
    }else if(Item=="label_6"){
        ui->label_6->setText(Msg);
    }else if(Item=="ipwarning"){
        int ret = QMessageBox::warning(this, tr("注意"),tr("新IP本次运行已使用过"),QMessageBox::Ok |QMessageBox::Cancel,QMessageBox::Cancel);
        //ui->textEdit->append(QString::number(ret));
        //requester->setCycleflag(true);
        switch (ret) {
          case QMessageBox::Ok:
              requester->setCycleflag(true);
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
              break;
          default:
              // should never be reached
              break;
        }

    }

}

void MainWindow::DisplayMsg(int a)
{
    ui->textEdit_2->append(QString::number(a));
}



void MainWindow::on_pushButton_clicked()
{
    if(requester->getFlag()){
        requester->stop();
        ui->pushButton->setText("start");
    }else{
        if(ui->lineEdit->text().isEmpty()){
            ui->textEdit->append("网址不能为空");
        }else if(ui->lineEdit_2->text().toInt()>32767){
            ui->textEdit->append("次数过多");
            qDebug("num:%d",ui->lineEdit_2->text().toInt());
            ui->textEdit->append(ui->lineEdit_2->text());
        }else{
            QByteArray temp = ui->lineEdit->text().toLatin1(); // must
            requester->setURL(temp.data());
            requester->setEpoch(ui->lineEdit_2->text().toInt());
            requester->begin();
            requester->setCycleflag(true);
            requester->setClickGap(ui->lineEdit_3->text().toInt());
            ui->pushButton->setText("stop");


        }

    }
}

