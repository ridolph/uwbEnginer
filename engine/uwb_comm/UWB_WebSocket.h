#ifndef __UWB_WebSocket_H__
#define __UWB_WebSocket_H__

#include <QObject>
#include <QStringList>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include "cJSON.h"
#include "UWB_SQL.h"


#define CELL_PRISONER_NUM		16

typedef enum _UWB_DATA_TYPE
{
    TYPE_UNKNOW = 0,
    CELL_OL,
    CELL_RT,
    PRISONER_OL,
    PRISONER_RT,
    PRISONER_HIST
}UWB_DATA_TYPE;

class UWB_WebSocket : public QWebSocket
{
public:
    uint8_t connect_flag;
    UWB_DATA_TYPE data_type;
	uint32_t cell_num;
    uint32_t tag_id;
};

class UWB_WebSocketServer : public QObject
{
    Q_OBJECT
public:
	
    explicit UWB_WebSocketServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~UWB_WebSocketServer();
    int32_t SendTagPosition(int32_t tag_id, double x, double y, double z);
    int32_t SendCellOnlineStatus(int32_t tag_id, uint8_t status);
	UWB_SQL *m_uwb_sql;

Q_SIGNALS:
    void closed(); 

private Q_SLOTS:
    void onNewConnection();
    int32_t processTextMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    QList<QWebSocket *> m_cell_ol_clients;
    QList<QWebSocket *> m_cell_rt_clients;
	QList<QWebSocket *> m_prisoner_ol_clients[CELL_PRISONER_NUM];
	QList<QWebSocket *> m_prisoner_rt_clients[CELL_PRISONER_NUM];
	
    bool m_debug;

    cJSON *__GetJsonRequest(QString req_json);
    void __JsonDelete(cJSON *json);
    int32_t __GetRequestCellNumber(cJSON *json);
    int32_t __GetRequestTagID(cJSON *json);
    char *__GetRequestObjString(cJSON *json, const char *key);
    UWB_DATA_TYPE __GetRequestDataType(cJSON *json);
    int32_t __CheckWebSocketInList(QList<QWebSocket *> *list, QWebSocket *web_socket);
    void __DeleteWebSocketInList(QWebSocket *web_socket);
};

#endif
