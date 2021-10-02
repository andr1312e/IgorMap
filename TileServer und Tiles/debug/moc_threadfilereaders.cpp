/****************************************************************************
** Meta object code from reading C++ file 'threadfilereaders.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../threadfilereaders.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadfilereaders.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadImageRotator_t {
    QByteArrayData data[13];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadImageRotator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadImageRotator_t qt_meta_stringdata_ThreadImageRotator = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ThreadImageRotator"
QT_MOC_LITERAL(1, 19, 21), // "gettingTilesToConvert"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 12), // "QStringList&"
QT_MOC_LITERAL(4, 55, 5), // "tiles"
QT_MOC_LITERAL(5, 61, 4), // "int&"
QT_MOC_LITERAL(6, 66, 19), // "numOfTilesToConvert"
QT_MOC_LITERAL(7, 86, 8), // "QString&"
QT_MOC_LITERAL(8, 95, 3), // "azm"
QT_MOC_LITERAL(9, 99, 5), // "layer"
QT_MOC_LITERAL(10, 105, 20), // "seekAvailableThreads"
QT_MOC_LITERAL(11, 126, 16), // "addThreadToQueue"
QT_MOC_LITERAL(12, 143, 18) // "readFilesFromQueue"

    },
    "ThreadImageRotator\0gettingTilesToConvert\0"
    "\0QStringList&\0tiles\0int&\0numOfTilesToConvert\0"
    "QString&\0azm\0layer\0seekAvailableThreads\0"
    "addThreadToQueue\0readFilesFromQueue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadImageRotator[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   34,    2, 0x0a /* Public */,
      10,    0,   43,    2, 0x0a /* Public */,
      11,    0,   44,    2, 0x0a /* Public */,
      12,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 7,    4,    6,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ThreadImageRotator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadImageRotator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gettingTilesToConvert((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->seekAvailableThreads(); break;
        case 2: _t->addThreadToQueue(); break;
        case 3: _t->readFilesFromQueue(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadImageRotator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ThreadImageRotator.data,
    qt_meta_data_ThreadImageRotator,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadImageRotator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadImageRotator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadImageRotator.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThreadImageRotator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
