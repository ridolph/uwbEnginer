/****************************************************************************
** Meta object code from reading C++ file 'UWB_WebSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uwb_comm/UWB_WebSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UWB_WebSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UWB_WebSocketServer_t {
    QByteArrayData data[8];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UWB_WebSocketServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UWB_WebSocketServer_t qt_meta_stringdata_UWB_WebSocketServer = {
    {
QT_MOC_LITERAL(0, 0, 19), // "UWB_WebSocketServer"
QT_MOC_LITERAL(1, 20, 6), // "closed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "onNewConnection"
QT_MOC_LITERAL(4, 44, 18), // "processTextMessage"
QT_MOC_LITERAL(5, 63, 7), // "int32_t"
QT_MOC_LITERAL(6, 71, 7), // "message"
QT_MOC_LITERAL(7, 79, 18) // "socketDisconnected"

    },
    "UWB_WebSocketServer\0closed\0\0onNewConnection\0"
    "processTextMessage\0int32_t\0message\0"
    "socketDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UWB_WebSocketServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x08 /* Private */,
       4,    1,   36,    2, 0x08 /* Private */,
       7,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    0x80000000 | 5, QMetaType::QString,    6,
    QMetaType::Void,

       0        // eod
};

void UWB_WebSocketServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UWB_WebSocketServer *_t = static_cast<UWB_WebSocketServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closed(); break;
        case 1: _t->onNewConnection(); break;
        case 2: { int32_t _r = _t->processTextMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int32_t*>(_a[0]) = _r; }  break;
        case 3: _t->socketDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UWB_WebSocketServer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UWB_WebSocketServer::closed)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject UWB_WebSocketServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UWB_WebSocketServer.data,
      qt_meta_data_UWB_WebSocketServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UWB_WebSocketServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UWB_WebSocketServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UWB_WebSocketServer.stringdata0))
        return static_cast<void*>(const_cast< UWB_WebSocketServer*>(this));
    return QObject::qt_metacast(_clname);
}

int UWB_WebSocketServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void UWB_WebSocketServer::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
