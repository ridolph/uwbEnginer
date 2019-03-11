#ifndef UWB_HTTP_H
#define UWB_HTTP_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#define _ACCEPT      "*/*"
//#define _CONTENT_TYPE  "application/json;charset=UTF-8"
//#define HTTP_3D_URL "http://www.teoform.com/com.obim.mq.service/message/send/json"
#define HTTP_3D_URL   "http://39.108.125.93:8080/com.obim.mq.service/message/send"
#define _CONTENT_TYPE "application/x-www-form-urlencoded;charset:utf-8"

class UWB_HTTP : public QObject
{
    Q_OBJECT
public:
    explicit UWB_HTTP(QString url);
    ~UWB_HTTP();

    void SendTagPosition(int32_t tag_id, double x, double y, double z);

public slots:
    void serviceRequestFinished(QNetworkReply *reply);

protected:
   void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode);

private:
    QString _url;
    QNetworkRequest _httpRequest;
    QNetworkAccessManager _networkAccessManager;
public slots:
};

#endif // UWB_HTTP_H
