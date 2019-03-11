/****************************************************************************
** Meta object code from reading C++ file 'AncManageWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../views/AncManageWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AncManageWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AncManageWidget_t {
    QByteArrayData data[28];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AncManageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AncManageWidget_t qt_meta_stringdata_AncManageWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "AncManageWidget"
QT_MOC_LITERAL(1, 16, 10), // "sendUpResp"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "status"
QT_MOC_LITERAL(4, 35, 4), // "int*"
QT_MOC_LITERAL(5, 40, 7), // "succBuf"
QT_MOC_LITERAL(6, 48, 9), // "succCount"
QT_MOC_LITERAL(7, 58, 7), // "failBuf"
QT_MOC_LITERAL(8, 66, 9), // "failCount"
QT_MOC_LITERAL(9, 76, 11), // "startUpdate"
QT_MOC_LITERAL(10, 88, 3), // "ver"
QT_MOC_LITERAL(11, 92, 13), // "sendUpCmdRsut"
QT_MOC_LITERAL(12, 106, 3), // "aid"
QT_MOC_LITERAL(13, 110, 2), // "ok"
QT_MOC_LITERAL(14, 113, 18), // "sendRecoverCmdRsut"
QT_MOC_LITERAL(15, 132, 14), // "sendGetVerRsut"
QT_MOC_LITERAL(16, 147, 13), // "updateAncAddr"
QT_MOC_LITERAL(17, 161, 4), // "addr"
QT_MOC_LITERAL(18, 166, 4), // "port"
QT_MOC_LITERAL(19, 171, 13), // "periodProcess"
QT_MOC_LITERAL(20, 185, 14), // "startUpTimeout"
QT_MOC_LITERAL(21, 200, 16), // "reportStaTimeout"
QT_MOC_LITERAL(22, 217, 11), // "cellClicked"
QT_MOC_LITERAL(23, 229, 1), // "r"
QT_MOC_LITERAL(24, 231, 1), // "c"
QT_MOC_LITERAL(25, 233, 10), // "showUpSrvW"
QT_MOC_LITERAL(26, 244, 10), // "verChanged"
QT_MOC_LITERAL(27, 255, 14) // "senDataTimeout"

    },
    "AncManageWidget\0sendUpResp\0\0status\0"
    "int*\0succBuf\0succCount\0failBuf\0failCount\0"
    "startUpdate\0ver\0sendUpCmdRsut\0aid\0ok\0"
    "sendRecoverCmdRsut\0sendGetVerRsut\0"
    "updateAncAddr\0addr\0port\0periodProcess\0"
    "startUpTimeout\0reportStaTimeout\0"
    "cellClicked\0r\0c\0showUpSrvW\0verChanged\0"
    "senDataTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AncManageWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   90,    2, 0x0a /* Public */,
      11,    2,   93,    2, 0x0a /* Public */,
      14,    2,   98,    2, 0x0a /* Public */,
      15,    2,  103,    2, 0x0a /* Public */,
      16,    3,  108,    2, 0x0a /* Public */,
      19,    0,  115,    2, 0x0a /* Public */,
      20,    0,  116,    2, 0x0a /* Public */,
      21,    0,  117,    2, 0x0a /* Public */,
      22,    2,  118,    2, 0x0a /* Public */,
      25,    0,  123,    2, 0x0a /* Public */,
      26,    1,  124,    2, 0x08 /* Private */,
      27,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, QMetaType::Int, 0x80000000 | 4, QMetaType::Int,    3,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   12,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int,   12,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   23,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void AncManageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AncManageWidget *_t = static_cast<AncManageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendUpResp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int*(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 1: _t->startUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sendUpCmdRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->sendRecoverCmdRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->sendGetVerRsut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->updateAncAddr((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->periodProcess(); break;
        case 7: _t->startUpTimeout(); break;
        case 8: _t->reportStaTimeout(); break;
        case 9: _t->cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->showUpSrvW(); break;
        case 11: _t->verChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->senDataTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AncManageWidget::*_t)(int , int * , int , int * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AncManageWidget::sendUpResp)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AncManageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AncManageWidget.data,
      qt_meta_data_AncManageWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AncManageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AncManageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AncManageWidget.stringdata0))
        return static_cast<void*>(const_cast< AncManageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AncManageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void AncManageWidget::sendUpResp(int _t1, int * _t2, int _t3, int * _t4, int _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
