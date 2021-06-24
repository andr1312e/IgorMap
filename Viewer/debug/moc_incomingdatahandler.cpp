/****************************************************************************
** Meta object code from reading C++ file 'incomingdatahandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
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
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IncomingDataHandler_t {
    QByteArrayData data[24];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IncomingDataHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IncomingDataHandler_t qt_meta_stringdata_IncomingDataHandler = {
    {
QT_MOC_LITERAL(0, 0, 19), // "IncomingDataHandler"
QT_MOC_LITERAL(1, 20, 10), // "addKTAMark"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "RLSOPlotMessage"
QT_MOC_LITERAL(4, 48, 3), // "msg"
QT_MOC_LITERAL(5, 52, 5), // "isPOI"
QT_MOC_LITERAL(6, 58, 11), // "addKTAMark2"
QT_MOC_LITERAL(7, 70, 13), // "POIKtaMessage"
QT_MOC_LITERAL(8, 84, 12), // "addTraceMark"
QT_MOC_LITERAL(9, 97, 14), // "RLSOaimMessage"
QT_MOC_LITERAL(10, 112, 14), // "resetTraceMark"
QT_MOC_LITERAL(11, 127, 6), // "trakId"
QT_MOC_LITERAL(12, 134, 12), // "updateRaySet"
QT_MOC_LITERAL(13, 147, 6), // "RaySet"
QT_MOC_LITERAL(14, 154, 3), // "vec"
QT_MOC_LITERAL(15, 158, 6), // "doWork"
QT_MOC_LITERAL(16, 165, 7), // "sendMsg"
QT_MOC_LITERAL(17, 173, 3), // "arr"
QT_MOC_LITERAL(18, 177, 8), // "readData"
QT_MOC_LITERAL(19, 186, 15), // "connectionError"
QT_MOC_LITERAL(20, 202, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(21, 231, 11), // "socketError"
QT_MOC_LITERAL(22, 243, 12), // "disconnected"
QT_MOC_LITERAL(23, 256, 13) // "slotConnected"

    },
    "IncomingDataHandler\0addKTAMark\0\0"
    "RLSOPlotMessage\0msg\0isPOI\0addKTAMark2\0"
    "POIKtaMessage\0addTraceMark\0RLSOaimMessage\0"
    "resetTraceMark\0trakId\0updateRaySet\0"
    "RaySet\0vec\0doWork\0sendMsg\0arr\0readData\0"
    "connectionError\0QAbstractSocket::SocketError\0"
    "socketError\0disconnected\0slotConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IncomingDataHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,
       8,    1,   77,    2, 0x06 /* Public */,
      10,    1,   80,    2, 0x06 /* Public */,
      12,    1,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   86,    2, 0x0a /* Public */,
      16,    1,   87,    2, 0x0a /* Public */,
      18,    0,   90,    2, 0x08 /* Private */,
      19,    1,   91,    2, 0x08 /* Private */,
      22,    0,   94,    2, 0x08 /* Private */,
      23,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, QMetaType::UInt,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   17,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
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
        case 0: _t->addKTAMark((*reinterpret_cast< RLSOPlotMessage(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->addKTAMark2((*reinterpret_cast< POIKtaMessage(*)>(_a[1]))); break;
        case 2: _t->addTraceMark((*reinterpret_cast< RLSOaimMessage(*)>(_a[1]))); break;
        case 3: _t->resetTraceMark((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 4: _t->updateRaySet((*reinterpret_cast< RaySet(*)>(_a[1]))); break;
        case 5: _t->doWork(); break;
        case 6: _t->sendMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->readData(); break;
        case 8: _t->connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 9: _t->disconnected(); break;
        case 10: _t->slotConnected(); break;
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
        {
            using _t = void (IncomingDataHandler::*)(RLSOPlotMessage , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::addKTAMark)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(POIKtaMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::addKTAMark2)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(RLSOaimMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::addTraceMark)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::resetTraceMark)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(RaySet );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::updateRaySet)) {
                *result = 4;
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
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void IncomingDataHandler::addKTAMark(RLSOPlotMessage _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IncomingDataHandler::addKTAMark2(POIKtaMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IncomingDataHandler::addTraceMark(RLSOaimMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IncomingDataHandler::resetTraceMark(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IncomingDataHandler::updateRaySet(RaySet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
