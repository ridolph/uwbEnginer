/****************************************************************************
** Meta object code from reading C++ file 'UWB_TcpClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uwb_comm/UWB_TcpClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UWB_TcpClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UWB_TcpClient_t {
    QByteArrayData data[27];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UWB_TcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UWB_TcpClient_t qt_meta_stringdata_UWB_TcpClient = {
    {
QT_MOC_LITERAL(0, 0, 13), // "UWB_TcpClient"
QT_MOC_LITERAL(1, 14, 11), // "startUpdate"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "ver"
QT_MOC_LITERAL(4, 31, 10), // "sendUpResp"
QT_MOC_LITERAL(5, 42, 6), // "status"
QT_MOC_LITERAL(6, 49, 4), // "int*"
QT_MOC_LITERAL(7, 54, 7), // "failBuf"
QT_MOC_LITERAL(8, 62, 9), // "failCount"
QT_MOC_LITERAL(9, 72, 7), // "succBuf"
QT_MOC_LITERAL(10, 80, 9), // "succCount"
QT_MOC_LITERAL(11, 90, 13), // "sendTagStatus"
QT_MOC_LITERAL(12, 104, 6), // "tag_id"
QT_MOC_LITERAL(13, 111, 10), // "tag_status"
QT_MOC_LITERAL(14, 122, 8), // "tag_area"
QT_MOC_LITERAL(15, 131, 13), // "sendAncStatus"
QT_MOC_LITERAL(16, 145, 7), // "tag_num"
QT_MOC_LITERAL(17, 153, 9), // "connectOk"
QT_MOC_LITERAL(18, 163, 11), // "readMessage"
QT_MOC_LITERAL(19, 175, 9), // "msgHandle"
QT_MOC_LITERAL(20, 185, 3), // "msg"
QT_MOC_LITERAL(21, 189, 12), // "disconnected"
QT_MOC_LITERAL(22, 202, 10), // "printError"
QT_MOC_LITERAL(23, 213, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(24, 242, 11), // "pingTimeout"
QT_MOC_LITERAL(25, 254, 11), // "connTimeout"
QT_MOC_LITERAL(26, 266, 14) // "pingRspTimeout"

    },
    "UWB_TcpClient\0startUpdate\0\0ver\0"
    "sendUpResp\0status\0int*\0failBuf\0failCount\0"
    "succBuf\0succCount\0sendTagStatus\0tag_id\0"
    "tag_status\0tag_area\0sendAncStatus\0"
    "tag_num\0connectOk\0readMessage\0msgHandle\0"
    "msg\0disconnected\0printError\0"
    "QAbstractSocket::SocketError\0pingTimeout\0"
    "connTimeout\0pingRspTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UWB_TcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    5,   77,    2, 0x0a /* Public */,
      11,    3,   88,    2, 0x0a /* Public */,
      15,    3,   95,    2, 0x0a /* Public */,
      17,    0,  102,    2, 0x08 /* Private */,
      18,    0,  103,    2, 0x08 /* Private */,
      19,    1,  104,    2, 0x08 /* Private */,
      21,    0,  107,    2, 0x08 /* Private */,
      22,    1,  108,    2, 0x08 /* Private */,
      24,    0,  111,    2, 0x08 /* Private */,
      25,    0,  112,    2, 0x08 /* Private */,
      26,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6, QMetaType::Int, 0x80000000 | 6, QMetaType::Int,    5,    7,    8,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UWB_TcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UWB_TcpClient *_t = static_cast<UWB_TcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendUpResp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int*(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->sendTagStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->sendAncStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->connectOk(); break;
        case 5: _t->readMessage(); break;
        case 6: _t->msgHandle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->disconnected(); break;
        case 8: _t->printError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 9: _t->pingTimeout(); break;
        case 10: _t->connTimeout(); break;
        case 11: _t->pingRspTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UWB_TcpClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UWB_TcpClient::startUpdate)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UWB_TcpClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UWB_TcpClient.data,
      qt_meta_data_UWB_TcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UWB_TcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UWB_TcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UWB_TcpClient.stringdata0))
        return static_cast<void*>(const_cast< UWB_TcpClient*>(this));
    return QObject::qt_metacast(_clname);
}

int UWB_TcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void UWB_TcpClient::startUpdate(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
