/****************************************************************************
** Meta object code from reading C++ file 'UpdateClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uwb_comm/UpdateClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UpdateClient_t {
    QByteArrayData data[17];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpdateClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpdateClient_t qt_meta_stringdata_UpdateClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UpdateClient"
QT_MOC_LITERAL(1, 13, 13), // "sendUpCmdRsut"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 3), // "aid"
QT_MOC_LITERAL(4, 32, 2), // "ok"
QT_MOC_LITERAL(5, 35, 18), // "sendRecoverCmdRsut"
QT_MOC_LITERAL(6, 54, 14), // "sendGetVerRsut"
QT_MOC_LITERAL(7, 69, 3), // "ver"
QT_MOC_LITERAL(8, 73, 9), // "connectOk"
QT_MOC_LITERAL(9, 83, 11), // "readMessage"
QT_MOC_LITERAL(10, 95, 9), // "handleMsg"
QT_MOC_LITERAL(11, 105, 3), // "msg"
QT_MOC_LITERAL(12, 109, 12), // "disconnected"
QT_MOC_LITERAL(13, 122, 10), // "printError"
QT_MOC_LITERAL(14, 133, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(15, 162, 11), // "connTimeout"
QT_MOC_LITERAL(16, 174, 10) // "rspTimeout"

    },
    "UpdateClient\0sendUpCmdRsut\0\0aid\0ok\0"
    "sendRecoverCmdRsut\0sendGetVerRsut\0ver\0"
    "connectOk\0readMessage\0handleMsg\0msg\0"
    "disconnected\0printError\0"
    "QAbstractSocket::SocketError\0connTimeout\0"
    "rspTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpdateClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       5,    2,   69,    2, 0x06 /* Public */,
       6,    2,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   79,    2, 0x08 /* Private */,
       9,    0,   80,    2, 0x08 /* Private */,
      10,    1,   81,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UpdateClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UpdateClient *_t = static_cast<UpdateClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendUpCmdRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->sendRecoverCmdRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->sendGetVerRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->connectOk(); break;
        case 4: _t->readMessage(); break;
        case 5: _t->handleMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->disconnected(); break;
        case 7: _t->printError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: _t->connTimeout(); break;
        case 9: _t->rspTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
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
            typedef void (UpdateClient::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateClient::sendUpCmdRsut)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (UpdateClient::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateClient::sendRecoverCmdRsut)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (UpdateClient::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UpdateClient::sendGetVerRsut)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject UpdateClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UpdateClient.data,
      qt_meta_data_UpdateClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UpdateClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpdateClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateClient.stringdata0))
        return static_cast<void*>(const_cast< UpdateClient*>(this));
    return QObject::qt_metacast(_clname);
}

int UpdateClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void UpdateClient::sendUpCmdRsut(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UpdateClient::sendRecoverCmdRsut(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UpdateClient::sendGetVerRsut(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
