#include "UWB_HTTP.h"

UWB_HTTP::UWB_HTTP(QString url)
{
    _url = url;
    _httpRequest.setRawHeader("Accept", _ACCEPT);
    _httpRequest.setRawHeader("Content-Type", _CONTENT_TYPE);
    QObject::connect(&_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

UWB_HTTP::~UWB_HTTP()
{
    _networkAccessManager.disconnect();
}

void UWB_HTTP::serviceRequestFinished(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

     qDebug() << "serviceRequestFinished...statusCode:" << statusCode;

     if(reply->error() == QNetworkReply::NoError)
     {
         requestFinished(reply, reply->readAll(), statusCode);
     }
     else
     {
         requestFinished(reply, "", statusCode);
     }

     reply->deleteLater();
}

void UWB_HTTP::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
{
    QString str = QString(data);
    qDebug()<<"recv http data:"<<str;
}


/* TODO
{
    'name':'zhilu.location.prison.run',
    'message':{'id':'20202','x':1,'y':6,'z':0}
}
*/

/**
 * 创建日期：
 * 修改日期：
 * 修改人：
/**
 * 创建日期：
 * 修改日期：
 * 修改人：
 * <p>@Title: 天河弱电江苏联通微支付系统业务控制中心模块</p>
 * <p>@Description: 内部消息传输类</p>
 * <p>Copyright: Copyright (c) 2009</p>
 * <p>Company: 广州市天河弱电电子系统工程有限公司 </p>
 * <p>@author </p>
 * <p>@version </p>
*/
void UWB_HTTP::SendTagPosition(int32_t tag_id, double x, double y, double z)
{
    char postBuf [256];

    //sprintf(postBuf,"name=zhilu.location.run&message={\"id\":\"%4X\",\"x\":%3.3f,\"y\":%3.3f,\"z\":%3.3f}\r\n",tag_id, x, y, z);
    sprintf(postBuf,"name=zhilu.location.run&message={\"id\":\"A43E\",\"x\":%3.3f,\"y\":%3.3f,\"z\":%3.3f}\r\n", x, y, z);
    QByteArray data = QString(postBuf).toLatin1();
    qDebug()<<"postData:"<<data;

    _httpRequest.setUrl(QUrl(_url));
    _networkAccessManager.post(_httpRequest, data);
}

