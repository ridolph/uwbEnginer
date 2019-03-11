/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../views/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[346];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "connectionStateChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 33), // "SerialConnection::ConnectionS..."
QT_MOC_LITERAL(4, 69, 22), // "saveViewConfigSettings"
QT_MOC_LITERAL(5, 92, 14), // "udpPortChanged"
QT_MOC_LITERAL(6, 107, 7), // "onReady"
QT_MOC_LITERAL(7, 115, 16), // "tcpNewConnection"
QT_MOC_LITERAL(8, 132, 16), // "socket_Read_Data"
QT_MOC_LITERAL(9, 149, 19), // "socket_Disconnected"
QT_MOC_LITERAL(10, 169, 12), // "loadSettings"
QT_MOC_LITERAL(11, 182, 12), // "saveSettings"
QT_MOC_LITERAL(12, 195, 9), // "setServer"
QT_MOC_LITERAL(13, 205, 4), // "addr"
QT_MOC_LITERAL(14, 210, 4), // "port"
QT_MOC_LITERAL(15, 215, 20), // "onConfigServerAction"
QT_MOC_LITERAL(16, 236, 18), // "onScanConfigAction"
QT_MOC_LITERAL(17, 255, 13), // "onAboutAction"
QT_MOC_LITERAL(18, 269, 13), // "onMiniMapView"
QT_MOC_LITERAL(19, 283, 17), // "onTagManageAction"
QT_MOC_LITERAL(20, 301, 20), // "onAnchorConfigAction"
QT_MOC_LITERAL(21, 322, 16), // "statusBarMessage"
QT_MOC_LITERAL(22, 339, 6) // "status"

    },
    "MainWindow\0connectionStateChanged\0\0"
    "SerialConnection::ConnectionState\0"
    "saveViewConfigSettings\0udpPortChanged\0"
    "onReady\0tcpNewConnection\0socket_Read_Data\0"
    "socket_Disconnected\0loadSettings\0"
    "saveSettings\0setServer\0addr\0port\0"
    "onConfigServerAction\0onScanConfigAction\0"
    "onAboutAction\0onMiniMapView\0"
    "onTagManageAction\0onAnchorConfigAction\0"
    "statusBarMessage\0status"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x0a /* Public */,
       4,    0,  102,    2, 0x0a /* Public */,
       5,    0,  103,    2, 0x0a /* Public */,
       6,    0,  104,    2, 0x09 /* Protected */,
       7,    0,  105,    2, 0x09 /* Protected */,
       8,    0,  106,    2, 0x09 /* Protected */,
       9,    0,  107,    2, 0x09 /* Protected */,
      10,    0,  108,    2, 0x09 /* Protected */,
      11,    0,  109,    2, 0x09 /* Protected */,
      12,    2,  110,    2, 0x09 /* Protected */,
      15,    0,  115,    2, 0x09 /* Protected */,
      16,    0,  116,    2, 0x09 /* Protected */,
      17,    0,  117,    2, 0x09 /* Protected */,
      18,    0,  118,    2, 0x09 /* Protected */,
      19,    0,  119,    2, 0x09 /* Protected */,
      20,    0,  120,    2, 0x09 /* Protected */,
      21,    1,  121,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionStateChanged((*reinterpret_cast< SerialConnection::ConnectionState(*)>(_a[1]))); break;
        case 1: _t->saveViewConfigSettings(); break;
        case 2: _t->udpPortChanged(); break;
        case 3: _t->onReady(); break;
        case 4: _t->tcpNewConnection(); break;
        case 5: _t->socket_Read_Data(); break;
        case 6: _t->socket_Disconnected(); break;
        case 7: _t->loadSettings(); break;
        case 8: _t->saveSettings(); break;
        case 9: _t->setServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->onConfigServerAction(); break;
        case 11: _t->onScanConfigAction(); break;
        case 12: _t->onAboutAction(); break;
        case 13: _t->onMiniMapView(); break;
        case 14: _t->onTagManageAction(); break;
        case 15: _t->onAnchorConfigAction(); break;
        case 16: _t->statusBarMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
