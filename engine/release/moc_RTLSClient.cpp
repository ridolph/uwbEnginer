/****************************************************************************
** Meta object code from reading C++ file 'RTLSClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../network/RTLSClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RTLSClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RTLSClient_t {
    QByteArrayData data[70];
    char stringdata0[694];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RTLSClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RTLSClient_t qt_meta_stringdata_RTLSClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RTLSClient"
QT_MOC_LITERAL(1, 11, 12), // "tagHeartRate"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 5), // "tagId"
QT_MOC_LITERAL(4, 31, 4), // "rate"
QT_MOC_LITERAL(5, 36, 5), // "power"
QT_MOC_LITERAL(6, 42, 9), // "plossRate"
QT_MOC_LITERAL(7, 52, 7), // "anchPos"
QT_MOC_LITERAL(8, 60, 8), // "anchorId"
QT_MOC_LITERAL(9, 69, 1), // "x"
QT_MOC_LITERAL(10, 71, 1), // "y"
QT_MOC_LITERAL(11, 73, 1), // "z"
QT_MOC_LITERAL(12, 75, 6), // "tagPos"
QT_MOC_LITERAL(13, 82, 8), // "tagStats"
QT_MOC_LITERAL(14, 91, 3), // "r95"
QT_MOC_LITERAL(15, 95, 8), // "tagRange"
QT_MOC_LITERAL(16, 104, 3), // "aId"
QT_MOC_LITERAL(17, 108, 16), // "statusBarMessage"
QT_MOC_LITERAL(18, 125, 6), // "status"
QT_MOC_LITERAL(19, 132, 15), // "centerOnAnchors"
QT_MOC_LITERAL(20, 148, 15), // "enableFiltering"
QT_MOC_LITERAL(21, 164, 9), // "ancRanges"
QT_MOC_LITERAL(22, 174, 3), // "a01"
QT_MOC_LITERAL(23, 178, 3), // "a02"
QT_MOC_LITERAL(24, 182, 3), // "a12"
QT_MOC_LITERAL(25, 186, 9), // "dsptcpLog"
QT_MOC_LITERAL(26, 196, 3), // "str"
QT_MOC_LITERAL(27, 200, 13), // "updateAncAddr"
QT_MOC_LITERAL(28, 214, 3), // "aid"
QT_MOC_LITERAL(29, 218, 4), // "addr"
QT_MOC_LITERAL(30, 223, 4), // "port"
QT_MOC_LITERAL(31, 228, 8), // "closeApp"
QT_MOC_LITERAL(32, 237, 13), // "sendUpCmdRsut"
QT_MOC_LITERAL(33, 251, 2), // "ok"
QT_MOC_LITERAL(34, 254, 18), // "sendRecoverCmdRsut"
QT_MOC_LITERAL(35, 273, 14), // "sendGetVerRsut"
QT_MOC_LITERAL(36, 288, 3), // "ver"
QT_MOC_LITERAL(37, 292, 8), // "anchInfo"
QT_MOC_LITERAL(38, 301, 10), // "newUdpData"
QT_MOC_LITERAL(39, 312, 18), // "newTcpOrSerialData"
QT_MOC_LITERAL(40, 331, 7), // "newData"
QT_MOC_LITERAL(41, 339, 11), // "QByteArray&"
QT_MOC_LITERAL(42, 351, 4), // "data"
QT_MOC_LITERAL(43, 356, 20), // "SendCellOnlineStatus"
QT_MOC_LITERAL(44, 377, 7), // "uint8_t"
QT_MOC_LITERAL(45, 385, 9), // "SendAlarm"
QT_MOC_LITERAL(46, 395, 10), // "ALARM_TYPE"
QT_MOC_LITERAL(47, 406, 9), // "alarmType"
QT_MOC_LITERAL(48, 416, 2), // "op"
QT_MOC_LITERAL(49, 419, 9), // "setServer"
QT_MOC_LITERAL(50, 429, 12), // "setOutServer"
QT_MOC_LITERAL(51, 442, 13), // "sendAncStatus"
QT_MOC_LITERAL(52, 456, 17), // "sendAncStatusDown"
QT_MOC_LITERAL(53, 474, 15), // "addNewAncTagSum"
QT_MOC_LITERAL(54, 490, 5), // "ancID"
QT_MOC_LITERAL(55, 496, 5), // "tagID"
QT_MOC_LITERAL(56, 502, 7), // "onReady"
QT_MOC_LITERAL(57, 510, 11), // "onConnected"
QT_MOC_LITERAL(58, 522, 4), // "conf"
QT_MOC_LITERAL(59, 527, 15), // "updateAnchorXYZ"
QT_MOC_LITERAL(60, 543, 2), // "id"
QT_MOC_LITERAL(61, 546, 5), // "value"
QT_MOC_LITERAL(62, 552, 19), // "updateTagCorrection"
QT_MOC_LITERAL(63, 572, 3), // "tid"
QT_MOC_LITERAL(64, 576, 16), // "updateAnchorShow"
QT_MOC_LITERAL(65, 593, 4), // "show"
QT_MOC_LITERAL(66, 598, 20), // "sendAncStatusTimeOut"
QT_MOC_LITERAL(67, 619, 22), // "connectionStateChanged"
QT_MOC_LITERAL(68, 642, 33), // "SerialConnection::ConnectionS..."
QT_MOC_LITERAL(69, 676, 17) // "periodCalcProcess"

    },
    "RTLSClient\0tagHeartRate\0\0tagId\0rate\0"
    "power\0plossRate\0anchPos\0anchorId\0x\0y\0"
    "z\0tagPos\0tagStats\0r95\0tagRange\0aId\0"
    "statusBarMessage\0status\0centerOnAnchors\0"
    "enableFiltering\0ancRanges\0a01\0a02\0a12\0"
    "dsptcpLog\0str\0updateAncAddr\0aid\0addr\0"
    "port\0closeApp\0sendUpCmdRsut\0ok\0"
    "sendRecoverCmdRsut\0sendGetVerRsut\0ver\0"
    "anchInfo\0newUdpData\0newTcpOrSerialData\0"
    "newData\0QByteArray&\0data\0SendCellOnlineStatus\0"
    "uint8_t\0SendAlarm\0ALARM_TYPE\0alarmType\0"
    "op\0setServer\0setOutServer\0sendAncStatus\0"
    "sendAncStatusDown\0addNewAncTagSum\0"
    "ancID\0tagID\0onReady\0onConnected\0conf\0"
    "updateAnchorXYZ\0id\0value\0updateTagCorrection\0"
    "tid\0updateAnchorShow\0show\0"
    "sendAncStatusTimeOut\0connectionStateChanged\0"
    "SerialConnection::ConnectionState\0"
    "periodCalcProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RTLSClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  184,    2, 0x06 /* Public */,
       7,    6,  193,    2, 0x06 /* Public */,
      12,    4,  206,    2, 0x06 /* Public */,
      13,    5,  215,    2, 0x06 /* Public */,
      15,    3,  226,    2, 0x06 /* Public */,
      17,    1,  233,    2, 0x06 /* Public */,
      19,    0,  236,    2, 0x06 /* Public */,
      20,    0,  237,    2, 0x06 /* Public */,
      21,    3,  238,    2, 0x06 /* Public */,
      25,    1,  245,    2, 0x06 /* Public */,
      27,    3,  248,    2, 0x06 /* Public */,
      31,    0,  255,    2, 0x06 /* Public */,
      32,    2,  256,    2, 0x06 /* Public */,
      34,    2,  261,    2, 0x06 /* Public */,
      35,    2,  266,    2, 0x06 /* Public */,
      37,    5,  271,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      38,    0,  282,    2, 0x0a /* Public */,
      39,    0,  283,    2, 0x0a /* Public */,
      40,    3,  284,    2, 0x0a /* Public */,
      43,    2,  291,    2, 0x0a /* Public */,
      45,    3,  296,    2, 0x0a /* Public */,
      49,    2,  303,    2, 0x0a /* Public */,
      50,    2,  308,    2, 0x0a /* Public */,
      51,    3,  313,    2, 0x0a /* Public */,
      52,    1,  320,    2, 0x0a /* Public */,
      53,    2,  323,    2, 0x0a /* Public */,
      56,    0,  328,    2, 0x09 /* Protected */,
      57,    2,  329,    2, 0x09 /* Protected */,
      59,    3,  334,    2, 0x09 /* Protected */,
      62,    3,  341,    2, 0x09 /* Protected */,
      64,    2,  348,    2, 0x09 /* Protected */,
      66,    0,  353,    2, 0x09 /* Protected */,
      67,    1,  354,    2, 0x08 /* Private */,
      69,    0,  357,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong, QMetaType::ULongLong, QMetaType::ULongLong,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Bool, QMetaType::Bool,    8,    9,   10,   11,    2,    2,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    9,   10,   11,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::Double,    3,    9,   10,   11,   14,
    QMetaType::Void, QMetaType::ULongLong, QMetaType::ULongLong, QMetaType::Double,    3,   16,    9,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   23,   24,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,   28,   29,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   28,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   28,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   28,   36,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 41, QMetaType::QString, QMetaType::LongLong,   42,   29,   30,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 44,    3,   18,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 46, 0x80000000 | 44,    3,   47,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   29,   30,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,   28,   29,   30,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   54,   55,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   36,   58,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Double,   60,    9,   61,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   28,   63,   61,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   60,   65,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 68,    2,
    QMetaType::Void,

       0        // eod
};

void RTLSClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RTLSClient *_t = static_cast<RTLSClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tagHeartRate((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2])),(*reinterpret_cast< quint64(*)>(_a[3])),(*reinterpret_cast< quint64(*)>(_a[4]))); break;
        case 1: _t->anchPos((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 2: _t->tagPos((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 3: _t->tagStats((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 4: _t->tagRange((*reinterpret_cast< quint64(*)>(_a[1])),(*reinterpret_cast< quint64(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 5: _t->statusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->centerOnAnchors(); break;
        case 7: _t->enableFiltering(); break;
        case 8: _t->ancRanges((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->dsptcpLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->updateAncAddr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->closeApp(); break;
        case 12: _t->sendUpCmdRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->sendRecoverCmdRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->sendGetVerRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 15: _t->anchInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 16: _t->newUdpData(); break;
        case 17: _t->newTcpOrSerialData(); break;
        case 18: _t->newData((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 19: _t->SendCellOnlineStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 20: _t->SendAlarm((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ALARM_TYPE(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        case 21: _t->setServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: _t->setOutServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: _t->sendAncStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 24: _t->sendAncStatusDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->addNewAncTagSum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 26: _t->onReady(); break;
        case 27: _t->onConnected((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 28: _t->updateAnchorXYZ((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 29: _t->updateTagCorrection((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 30: _t->updateAnchorShow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 31: _t->sendAncStatusTimeOut(); break;
        case 32: _t->connectionStateChanged((*reinterpret_cast< SerialConnection::ConnectionState(*)>(_a[1]))); break;
        case 33: _t->periodCalcProcess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RTLSClient::*_t)(quint64 , quint64 , quint64 , quint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::tagHeartRate)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(quint64 , double , double , double , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::anchPos)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(quint64 , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::tagPos)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(quint64 , double , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::tagStats)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(quint64 , quint64 , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::tagRange)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::statusBarMessage)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::centerOnAnchors)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::enableFiltering)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::ancRanges)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::dsptcpLog)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(int , QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::updateAncAddr)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::closeApp)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::sendUpCmdRsut)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::sendRecoverCmdRsut)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::sendGetVerRsut)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (RTLSClient::*_t)(int , int , double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RTLSClient::anchInfo)) {
                *result = 15;
                return;
            }
        }
    }
}

const QMetaObject RTLSClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RTLSClient.data,
      qt_meta_data_RTLSClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RTLSClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RTLSClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RTLSClient.stringdata0))
        return static_cast<void*>(const_cast< RTLSClient*>(this));
    return QObject::qt_metacast(_clname);
}

int RTLSClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 34;
    }
    return _id;
}

// SIGNAL 0
void RTLSClient::tagHeartRate(quint64 _t1, quint64 _t2, quint64 _t3, quint64 _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RTLSClient::anchPos(quint64 _t1, double _t2, double _t3, double _t4, bool _t5, bool _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RTLSClient::tagPos(quint64 _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RTLSClient::tagStats(quint64 _t1, double _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RTLSClient::tagRange(quint64 _t1, quint64 _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RTLSClient::statusBarMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void RTLSClient::centerOnAnchors()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void RTLSClient::enableFiltering()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}

// SIGNAL 8
void RTLSClient::ancRanges(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void RTLSClient::dsptcpLog(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void RTLSClient::updateAncAddr(int _t1, QString _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void RTLSClient::closeApp()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void RTLSClient::sendUpCmdRsut(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void RTLSClient::sendRecoverCmdRsut(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void RTLSClient::sendGetVerRsut(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void RTLSClient::anchInfo(int _t1, int _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_END_MOC_NAMESPACE
