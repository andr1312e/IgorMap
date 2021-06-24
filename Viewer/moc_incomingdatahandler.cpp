/****************************************************************************
** Meta object code from reading C++ file 'incomingdatahandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TcpHandler/incomingdatahandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'incomingdatahandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IncomingDataHandler_t {
    QByteArrayData data[32];
    char stringdata0[383];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IncomingDataHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IncomingDataHandler_t qt_meta_stringdata_IncomingDataHandler = {
    {
QT_MOC_LITERAL(0, 0, 19), // "IncomingDataHandler"
QT_MOC_LITERAL(1, 20, 14), // "addVOIMarkSign"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "VOIMarkMessage"
QT_MOC_LITERAL(4, 51, 3), // "msg"
QT_MOC_LITERAL(5, 55, 14), // "addPOIMarkSign"
QT_MOC_LITERAL(6, 70, 13), // "POIKtaMessage"
QT_MOC_LITERAL(7, 84, 12), // "addTraceMark"
QT_MOC_LITERAL(8, 97, 14), // "RLSOaimMessage"
QT_MOC_LITERAL(9, 112, 14), // "resetTraceMark"
QT_MOC_LITERAL(10, 127, 6), // "trakId"
QT_MOC_LITERAL(11, 134, 12), // "updateRaySet"
QT_MOC_LITERAL(12, 147, 6), // "RaySet"
QT_MOC_LITERAL(13, 154, 3), // "vec"
QT_MOC_LITERAL(14, 158, 20), // "updateInfoAboutTrace"
QT_MOC_LITERAL(15, 179, 7), // "trackId"
QT_MOC_LITERAL(16, 187, 7), // "isReset"
QT_MOC_LITERAL(17, 195, 10), // "dspNewData"
QT_MOC_LITERAL(18, 206, 18), // "RLSODSPDataMessage"
QT_MOC_LITERAL(19, 225, 9), // "mapUpdate"
QT_MOC_LITERAL(20, 235, 3), // "doc"
QT_MOC_LITERAL(21, 239, 6), // "doWork"
QT_MOC_LITERAL(22, 246, 7), // "sendMsg"
QT_MOC_LITERAL(23, 254, 3), // "arr"
QT_MOC_LITERAL(24, 258, 16), // "sendJsonDocument"
QT_MOC_LITERAL(25, 275, 8), // "readData"
QT_MOC_LITERAL(26, 284, 14), // "readDataForMap"
QT_MOC_LITERAL(27, 299, 15), // "connectionError"
QT_MOC_LITERAL(28, 315, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(29, 344, 11), // "socketError"
QT_MOC_LITERAL(30, 356, 12), // "disconnected"
QT_MOC_LITERAL(31, 369, 13) // "slotConnected"

    },
    "IncomingDataHandler\0addVOIMarkSign\0\0"
    "VOIMarkMessage\0msg\0addPOIMarkSign\0"
    "POIKtaMessage\0addTraceMark\0RLSOaimMessage\0"
    "resetTraceMark\0trakId\0updateRaySet\0"
    "RaySet\0vec\0updateInfoAboutTrace\0trackId\0"
    "isReset\0dspNewData\0RLSODSPDataMessage\0"
    "mapUpdate\0doc\0doWork\0sendMsg\0arr\0"
    "sendJsonDocument\0readData\0readDataForMap\0"
    "connectionError\0QAbstractSocket::SocketError\0"
    "socketError\0disconnected\0slotConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IncomingDataHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       5,    1,   97,    2, 0x06 /* Public */,
       7,    1,  100,    2, 0x06 /* Public */,
       9,    1,  103,    2, 0x06 /* Public */,
      11,    1,  106,    2, 0x06 /* Public */,
      14,    2,  109,    2, 0x06 /* Public */,
      17,    1,  114,    2, 0x06 /* Public */,
      19,    1,  117,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    0,  120,    2, 0x0a /* Public */,
      22,    1,  121,    2, 0x0a /* Public */,
      24,    1,  124,    2, 0x0a /* Public */,
      25,    0,  127,    2, 0x08 /* Private */,
      26,    0,  128,    2, 0x08 /* Private */,
      27,    1,  129,    2, 0x08 /* Private */,
      30,    0,  132,    2, 0x08 /* Private */,
      31,    0,  133,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8,    4,
    QMetaType::Void, QMetaType::UInt,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   15,   16,
    QMetaType::Void, 0x80000000 | 18,    4,
    QMetaType::Void, QMetaType::QJsonDocument,   20,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   23,
    QMetaType::Void, QMetaType::QJsonDocument,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void IncomingDataHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        IncomingDataHandler *_t = static_cast<IncomingDataHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addVOIMarkSign((*reinterpret_cast< VOIMarkMessage(*)>(_a[1]))); break;
        case 1: _t->addPOIMarkSign((*reinterpret_cast< POIKtaMessage(*)>(_a[1]))); break;
        case 2: _t->addTraceMark((*reinterpret_cast< RLSOaimMessage(*)>(_a[1]))); break;
        case 3: _t->resetTraceMark((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 4: _t->updateRaySet((*reinterpret_cast< RaySet(*)>(_a[1]))); break;
        case 5: _t->updateInfoAboutTrace((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->dspNewData((*reinterpret_cast< RLSODSPDataMessage(*)>(_a[1]))); break;
        case 7: _t->mapUpdate((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 8: _t->doWork(); break;
        case 9: _t->sendMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->sendJsonDocument((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 11: _t->readData(); break;
        case 12: _t->readDataForMap(); break;
        case 13: _t->connectionError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 14: _t->disconnected(); break;
        case 15: _t->slotConnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
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
            using _t = void (IncomingDataHandler::*)(VOIMarkMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::addVOIMarkSign)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(POIKtaMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::addPOIMarkSign)) {
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
        {
            using _t = void (IncomingDataHandler::*)(qint32 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::updateInfoAboutTrace)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(RLSODSPDataMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::dspNewData)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (IncomingDataHandler::*)(QJsonDocument );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IncomingDataHandler::mapUpdate)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject IncomingDataHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_IncomingDataHandler.data,
      qt_meta_data_IncomingDataHandler,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void IncomingDataHandler::addVOIMarkSign(VOIMarkMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IncomingDataHandler::addPOIMarkSign(POIKtaMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void IncomingDataHandler::addTraceMark(RLSOaimMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void IncomingDataHandler::resetTraceMark(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void IncomingDataHandler::updateRaySet(RaySet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void IncomingDataHandler::updateInfoAboutTrace(qint32 _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void IncomingDataHandler::dspNewData(RLSODSPDataMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void IncomingDataHandler::mapUpdate(QJsonDocument _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
