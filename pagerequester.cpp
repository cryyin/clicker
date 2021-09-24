#include "pagerequester.h"

void pagerequester::run()
{
    QNetworkRequest request;
    QNetworkAccessManager* naManager = new QNetworkAccessManager(this);
    QObject::connect(naManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    /* 组装协议头 */
    qDebug() <<"char * before!!!!!!!!!!!!!"<< siteURL << "\n";
    request.setRawHeader("Accept", "application/json, text/plain, */*");
    request.setRawHeader("Accept-Language", "zh-CN,en-US;q=0.8");
    QString boolText = QSslSocket::supportsSsl() ? "true" : "false";
    ipMa =new IpAddressManager();
    nowip=ipMa->getOutIpAddress();
    emit SendMsgToWindow("textEdit","OpenSSL支持情况:" + boolText);
    emit SendMsgToWindow("textEdit","QSslSocket=" + QSslSocket::sslLibraryBuildVersionString());
    while(1){
        //qDebug() <<"char %%%%%%%%%%%%%%%%%%%"<< siteURL << "\n";
        if(startFlag&&cycleflag){
            emit SendMsgToWindow("textEdit","开始访问");
            qDebug() <<"char * before"<< siteURL << "\n";
            QString qs_URL =  QString(QLatin1String(siteURL));
            if(qs_URL.toLower().startsWith("https"))
            {
                QSslConfiguration sslConfig;
                sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);
                sslConfig.setProtocol(QSsl::TlsV1_0);   //具体以OpenSSL版本为准
                request.setSslConfiguration(sslConfig);
            }
            request.setUrl(QUrl(siteURL));
            for(int i=0;i<cycleNum;i++)
            {
                //qDebug() <<"qstr"<< qs_URL << "\n";
                //qDebug() <<"char *"<< siteURL << "\n";
                //qDebug() << "OpenSSL支持情况:" << QSslSocket::supportsSsl();
                //qDebug()<<"QSslSocket="<<QSslSocket::sslLibraryBuildVersionString();

                /* 如果是https请求，则需支持SSL验证 */
                emit SendMsgToWindow("textEdit","第"+QString::number(i+1)+"次");
                QNetworkReply* reply = naManager->get(request);
                //emit finished(reply);
                QEventLoop loop;
                connect(naManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
                loop.exec(QEventLoop::ExcludeUserInputEvents);
                QTimer::singleShot(clickGap, &loop, SLOT(quit()));
                loop.exec();
            }
            lastip=nowip;
            setCycleflag(false);
            IPchanged=true;
            allIP.append(lastip);
            emit SendMsgToWindow("textEdit","当前IP："+lastip+"；循环以完成，等待更新IP");
            emit SendMsgToWindow("label_7",lastip);


        }else{
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, SLOT(quit()));
            loop.exec();
            nowip=ipMa->getOutIpAddress();
            emit SendMsgToWindow("textEdit_2","nowip:"+nowip);
            emit SendMsgToWindow("textEdit_2","lastip:"+lastip);
            if((QString::compare(nowip,lastip)!=0)&&!lastip.isEmpty()&&IPchanged)
            {

                emit SendMsgToWindow("textEdit","IP已更新为："+nowip+"，继续");
                emit SendMsgToWindow("label_6",nowip);
                if(allIP.contains(nowip)){
                    emit SendMsgToWindow("textEdit","IP本次运行已使用过");
                    emit SendMsgToWindow("ipwarning","IP本次运行已使用过");
                    lastip=nowip;
                    continue;
                }
                setCycleflag(true);
                IPchanged=false;
            }
        }
    }
}


void pagerequester::replyFinished(QNetworkReply *reply)
{
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        emit SendMsgToWindow("textEdit_2","statusCode");
        // 获取http状态码
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if(statusCode.isValid())
            qDebug() << "status code=" << statusCode.toInt();
            //emit TestSignal(statusCode.toInt());
            emit SendMsgToWindow("textEdit_2",statusCode.toString());

        QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        if(reason.isValid())
            qDebug() << "reason=" << reason.toString();
            emit SendMsgToWindow("textEdit_2",reason.toString());
            emit SendMsgToWindow("textEdit",reason.toString());

        QNetworkReply::NetworkError err = reply->error();
        if(err != QNetworkReply::NoError) {
            qDebug() << "Failed: " << reply->errorString();
            emit SendMsgToWindow("textEdit_2",reply->errorString());
            emit SendMsgToWindow("textEdit",reply->errorString());
        }
        else {
            // 获取返回内容
            qDebug() << reply->readAll();
            emit SendMsgToWindow("textEdit_2",reply->readAll());
        }
}

void pagerequester::begin()
{
    startFlag=1;
}

void pagerequester::stop()
{
    startFlag=0;
}

void pagerequester::setURL(char URLs[32767])
{
    strcpy_s(siteURL,URLs);
    emit SendMsgToWindow("textEdit","设置地址:" + QString(QLatin1String(siteURL)));
    qDebug()<<"seturl:"<<siteURL;
}

void pagerequester::setEpoch(int Epoch)
{
    cycleNum=Epoch;
    emit SendMsgToWindow("textEdit","设置次数:" + QString::number(cycleNum));
}

bool pagerequester::getFlag()
{
    return startFlag;
}

void pagerequester::setCycleflag(bool flag)
{
    cycleflag=flag;
}

void pagerequester::setClickGap(int gap)
{
    clickGap=gap;
    emit SendMsgToWindow("textEdit","设置间隔时间（ms）:" + QString::number(clickGap));
}
