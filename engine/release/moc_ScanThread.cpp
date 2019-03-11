/****************************************************************************
** Meta object code from reading C++ file 'ScanThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uwb_comm/ScanThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScanThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScanThread_t {
    QByteArrayData data[10];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanThread_t qt_meta_stringdata_ScanThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ScanThread"
QT_MOC_LITERAL(1, 11, 20), // "SendCellOnlineStatus"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "tagId"
QT_MOC_LITERAL(4, 39, 7), // "uint8_t"
QT_MOC_LITERAL(5, 47, 6), // "status"
QT_MOC_LITERAL(6, 54, 9), // "SendAlarm"
QT_MOC_LITERAL(7, 64, 10), // "ALARM_TYPE"
QT_MOC_LITERAL(8, 75, 9), // "alarmType"
QT_MOC_LITERAL(9, 85, 2) // "op"

    },
    "ScanThread\0SendCellOnlineStatus\0\0tagId\0"
    "uint8_t\0status\0SendAlarm\0ALARM_TYPE\0"
    "alarmType\0op"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       6,    3,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 4,    3,    8,    9,

       0        // eod
};

void ScanThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScanThread *_t = static_cast<ScanThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendCellOnlineStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2]))); break;
        case 1: _t->SendAlarm((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ALARM_TYPE(*)>(_a[2])),(*reinterpret_cast< uint8_t(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScanThread::*_t)(int , uint8_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScanThread::SendCellOnlineStatus)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ScanThread::*_t)(int , ALARM_TYPE , uint8_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScanThread::SendAlarm)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ScanThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ScanThread.data,
      qt_meta_data_ScanThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScanThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScanThread.stringdata0))
        return static_cast<void*>(const_cast< ScanThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ScanThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ScanThread::SendCellOnlineStatus(int _t1, uint8_t _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScanThread::SendAlarm(int _t1, ALARM_TYPE _t2, uint8_t _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
