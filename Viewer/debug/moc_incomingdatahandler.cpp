/****************************************************************************
** Meta object code from reading C++ file 'incomingdatahandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../TcpHandler/incomingdatahandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'incomingdatahandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IncomingDataHandler_t {
    QByteArrayData data[13];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IncomingDataHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IncomingDataHandler_t qt_meta_stringdata_IncomingDataHandler = {
    {
QT_MOC_LITERAL(0, 0, 19), // "IncomingDataHandler"
QT_MOC_LITERAL(1, 20, 9), // "mapUpdate"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "doc"
QT_MOC_LITERAL(4, 35, 6), // "doWork"
QT_MOC_LITERAL(5, 42, 16), // "sendJsonDocument"
QT_MOC_LITERAL(6, 59, 14), // "readDataForMap"
QT_MOC_LITERAL(7, 74, 15), // "connectionError"
QT_MOC_LITERAL(8, 90, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 119, 11), // "socketError"
QT_MOC_LITERAL(10, 131, 12), // "disconnected"
QT_MOC_LITERAL(11, 144, 13), // "slotConnected"
QT_MOC_LITERAL(12, 158, 22) // "connectToHostOnTimeout"

    },
    "IncomingDataHandler\0mapUpdate\0\0doc\0"
    "doWork\0sendJsonDocument\0readDataForMap\0"
    "connectionError\0QAbstractSocket::SocketError\0"
    "socketError\0disconnected\0slotConnected\0"
    "connectToHostOnTimeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IncomingDataHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   57,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       6,    0,   61,    2, 0x08 /* Private */,
       7,    1,   62,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,
      11,    0,   66,    2, 0x08 /* Private */,
      12,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonDocument,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IncomingDataHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IncomingDataHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mapUpdate((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 1: _t->doWork(); break;
        case 2: _t->sendJsonDocument((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 3: _t->readDataForMap(); break;
        case 4: _t->connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->disconnected(); break;
        case 6: _t->slotConnected(); break;
        case 7: _t->connectToHostOnTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IncomingDataHandler::*)(QJsonDocument );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::mapUpdate)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IncomingDataHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IncomingDataHandler.data,
    qt_meta_data_IncomingDataHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IncomingDataHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IncomingDataHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IncomingDataHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IncomingDataHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void IncomingDataHandler::mapUpdate(QJsonDocument _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
