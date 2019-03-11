#include <qstring.h>
#include "UWB_WebSocket.h"


UWB_WebSocketServer::UWB_WebSocketServer(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("UWB WebSocket Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    m_uwb_sql = new UWB_SQL("192.168.10.9", "prison", "root", "root");
	
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "UWB WebSocket Server listening on port" << port;
		
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &UWB_WebSocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &UWB_WebSocketServer::closed);
    }
}

UWB_WebSocketServer::~UWB_WebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
	qDeleteAll(m_cell_ol_clients.begin(), m_clients.end());
	qDeleteAll(m_cell_rt_clients.begin(), m_clients.end());
}

void UWB_WebSocketServer::onNewConnection()
{
    qDebug() << "New WebSocket connection connected";

    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &UWB_WebSocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &UWB_WebSocketServer::socketDisconnected);

    qDebug() << "Add websocket to m_clients" << pSocket;
    m_clients << pSocket;
}

cJSON *UWB_WebSocketServer::__GetJsonRequest(QString req_json)
{
    char *json_str = NULL;

    QByteArray byte_array = req_json.toLatin1();

    json_str = byte_array.data();

    return cJSON_Parse(json_str);
}

void UWB_WebSocketServer::__JsonDelete(cJSON *json)
{
    if (json == NULL)
        return;

    cJSON_Delete(json);
}

UWB_DATA_TYPE UWB_WebSocketServer::__GetRequestDataType(cJSON *json)
{
    UWB_DATA_TYPE type = TYPE_UNKNOW;

    if (json == NULL)
        return type;

    cJSON *data_type = cJSON_GetObjectItem(json, "data_type");
    if (data_type == NULL)
        return type;

    if (0 == strcmp(data_type->valuestring, "cell_ol"))
        type = CELL_OL;
    else if (0 == strcmp(data_type->valuestring, "cell_rt"))
        type = CELL_RT;
	else if (0 == strcmp(data_type->valuestring, "prisoner_ol"))
        type = PRISONER_OL;
    else if (0 == strcmp(data_type->valuestring, "prisoner_hist"))
        type = PRISONER_HIST;

    return type;
}

int32_t UWB_WebSocketServer::__GetRequestCellNumber(cJSON *json)
{
    if (json == NULL)
        return -1;

    cJSON *cell_json = cJSON_GetObjectItem(json, "cell_num");
    if (cell_json == NULL)
        return -2;

    return cell_json->valueint;
}

int32_t UWB_WebSocketServer::__GetRequestTagID(cJSON *json)
{
    if (json == NULL)
        return -1;

    cJSON *tag_id = cJSON_GetObjectItem(json, "tag_id");
    if (tag_id == NULL)
        return -2;

    return tag_id->valueint;
}

char *UWB_WebSocketServer::__GetRequestObjString(cJSON *json, const char *key)
{
    if ((json == NULL) || (key == NULL))
        return NULL;

    cJSON *value = cJSON_GetObjectItem(json, key);
    if (value == NULL)
        return NULL;

    return value->valuestring;
}

int32_t UWB_WebSocketServer::__CheckWebSocketInList(QList<QWebSocket *> *list, QWebSocket *web_socket)
{
    if ((list == NULL) || (web_socket == NULL))
        return -1;

    for (int32_t i = 0; i < list->size(); i++)
        if (list->at(i) == web_socket)
            return i;

    return -1;
}

void UWB_WebSocketServer::__DeleteWebSocketInList(QWebSocket *web_socket)
{
    int32_t ret;
    uint32_t i;

    if (web_socket == NULL)
        return;

    ret = __CheckWebSocketInList(&m_cell_ol_clients, web_socket);
    if (ret >= 0)
    {
        qDebug() << "Delete websocket from m_cell_ol_clients" << web_socket;
        m_cell_ol_clients.removeAll(web_socket);
    }

    ret = __CheckWebSocketInList(&m_cell_rt_clients, web_socket);
    if (ret >= 0)
    {
        qDebug() << "Delete websocket from m_cell_rt_clients" << web_socket;
        m_cell_rt_clients.removeAll(web_socket);
    }

    for (i = 0; i < CELL_PRISONER_NUM; i++)
    {
        ret = __CheckWebSocketInList(&m_prisoner_ol_clients[i], web_socket);
        if (ret >= 0)
        {
            qDebug() << "Delete websocket from m_prisoner_ol_clients" << i << web_socket;
            m_prisoner_ol_clients[i].removeAll(web_socket);
        }
    }

    for (i = 0; i < CELL_PRISONER_NUM; i++)
    {
        ret = __CheckWebSocketInList(&m_prisoner_rt_clients[i], web_socket);
        if (ret >= 0)
        {
            qDebug() << "Delete websocket from m_prisoner_rt_clients" << i << web_socket;
            m_prisoner_rt_clients[i].removeAll(web_socket);
        }
    }

}

int32_t UWB_WebSocketServer::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

	qDebug() << "Message received:" << message;

    cJSON *json_req = __GetJsonRequest(message);
    if (json_req == NULL)
        return -1;

    UWB_DATA_TYPE type = __GetRequestDataType(json_req);
    if (type == CELL_OL)
    {
        if (__CheckWebSocketInList(&m_cell_ol_clients, pClient) < 0)
        {
            qDebug() << "Add websocket to m_cell_ol_clients" << pClient;
            m_cell_ol_clients << pClient;
        }
    }
    else if (type == CELL_RT)
    {
        if (__CheckWebSocketInList(&m_cell_rt_clients, pClient) < 0)
        {
            qDebug() << "Add websocket to m_cell_rt_clients" << pClient;
            m_cell_rt_clients << pClient;
        }
    }
	else if (type == PRISONER_OL)
    {
    	int32_t tag_id = __GetRequestTagID(json_req);
        if (tag_id < 0)
            return -1;

        if (__CheckWebSocketInList(&m_prisoner_ol_clients[tag_id], pClient) < 0)
        {
            qDebug() << "Add websocket to m_prisoner_ol_clients" << tag_id << pClient;
            m_prisoner_ol_clients[tag_id] << pClient;
        }
    }
    else if (type == PRISONER_HIST)
    {
        int32_t tag_id = __GetRequestTagID(json_req);
        if (tag_id < 0)
            return -2;

        char *start_time = __GetRequestObjString(json_req, "start_time");
        if (start_time == NULL)
            return -3;

        char *end_time = __GetRequestObjString(json_req, "end_time");
        if (end_time == NULL)
            return -4;

        char *send_data = m_uwb_sql->GetPrisonerHistoryData(tag_id, start_time, end_time);
        if (send_data == NULL)
            return -5;

        qDebug() << send_data;

        pClient->sendTextMessage(send_data);
		
		free(send_data);
		
        if (__CheckWebSocketInList(&m_prisoner_rt_clients[tag_id], pClient) < 0)
        {
            qDebug() << "Add websocket to m_prisoner_rt_clients" << tag_id << pClient;
            m_prisoner_rt_clients[tag_id] << pClient;
        }
    }
    else
    {
        return -1;
    }

    if (__CheckWebSocketInList(&m_clients, pClient) >= 0)
    {
        qDebug() << "Delete websocket from m_clients" << pClient;
        m_clients.removeAll(pClient);
    }

    __JsonDelete(json_req);

    return 0;
} 

int32_t UWB_WebSocketServer::SendCellOnlineStatus(int32_t tag_id, uint8_t status)
{

    cJSON *cell_ol_array = cJSON_CreateArray();
    if (cell_ol_array == NULL)
        return -1;

    cJSON *ol_status = cJSON_CreateObject();
    if (ol_status == NULL)
    {
        cJSON_Delete(cell_ol_array);
        return -2;
    }

    cJSON_AddNumberToObject(ol_status, "tag_id", tag_id);
    cJSON_AddNumberToObject(ol_status, "status", status);
    cJSON_AddItemToArray(cell_ol_array, ol_status);

    char *strPosData = cJSON_Print(cell_ol_array);

	
    qDebug() << strPosData;
    QString s(strPosData);
	

#if 1
    for (int i = 0; i != m_cell_ol_clients.size(); i++)
    {
        if (m_cell_ol_clients.at(i) != NULL)
            m_cell_ol_clients.at(i)->sendTextMessage(s);
    }

    for (int i = 0; i != m_prisoner_ol_clients[tag_id].size(); i++)
    {
        if (m_prisoner_ol_clients[tag_id].at(i) != NULL)
            m_prisoner_ol_clients[tag_id].at(i)->sendTextMessage(s);
    }
#endif

    //cJSON_Delete(ol_status);
    cJSON_Delete(cell_ol_array);
    free(strPosData);
}

int32_t UWB_WebSocketServer::SendTagPosition(int32_t tag_id, double x, double y, double z)
{
    cJSON *cell_rt_array = cJSON_CreateArray();
    if (cell_rt_array == NULL)
        return -1;

    cJSON *cell_rt_data = cJSON_CreateObject();
    if (cell_rt_data == NULL)
    {
        cJSON_Delete(cell_rt_data);
        return -2;
    }

    cJSON_AddNumberToObject(cell_rt_data, "tag_id", tag_id);
    cJSON_AddNumberToObject(cell_rt_data, "pos_x", x);
    cJSON_AddNumberToObject(cell_rt_data, "pos_y", y);
    cJSON_AddNumberToObject(cell_rt_data, "pos_z", z);
    cJSON_AddItemToArray(cell_rt_array, cell_rt_data);

    char *strPosData = cJSON_Print(cell_rt_array);

   // qDebug() << strPosData;
    QString s(strPosData);

#if 1
	//发送每个犯人的位置给已经连接上的客户端
    for (int i = 0; i != m_cell_rt_clients.size(); i++)
    {
    	if (m_cell_rt_clients.at(i) != NULL)
        	m_cell_rt_clients.at(i)->sendTextMessage(s);
    }

	for (int i = 0; i != m_prisoner_rt_clients[tag_id].size(); i++)
    {
    	if (m_prisoner_rt_clients[tag_id].at(i) != NULL)
        	m_prisoner_rt_clients[tag_id].at(i)->sendTextMessage(s);
    }
#endif
	
    cJSON_Delete(cell_rt_array);
    free(strPosData);
}

void UWB_WebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (pClient == NULL)
        return;

	qDebug() << "socketDisconnected:" << pClient;

    __DeleteWebSocketInList(pClient);

    pClient->deleteLater();
}
