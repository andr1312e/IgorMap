/****************************************************************************
** Meta object code from reading C++ file 'tilesanalyzer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tilesanalyzer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tilesanalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TilesAnalyzer_t {
    QByteArrayData data[23];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TilesAnalyzer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TilesAnalyzer_t qt_meta_stringdata_TilesAnalyzer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TilesAnalyzer"
QT_MOC_LITERAL(1, 14, 13), // "sendToProgram"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 12), // "QStringList&"
QT_MOC_LITERAL(4, 42, 5), // "tiles"
QT_MOC_LITERAL(5, 48, 6), // "float&"
QT_MOC_LITERAL(6, 55, 2), // "w1"
QT_MOC_LITERAL(7, 58, 2), // "h1"
QT_MOC_LITERAL(8, 61, 2), // "w2"
QT_MOC_LITERAL(9, 64, 2), // "h2"
QT_MOC_LITERAL(10, 67, 2), // "w3"
QT_MOC_LITERAL(11, 70, 2), // "h3"
QT_MOC_LITERAL(12, 73, 2), // "w4"
QT_MOC_LITERAL(13, 76, 6), // "p1_lat"
QT_MOC_LITERAL(14, 83, 7), // "p1_long"
QT_MOC_LITERAL(15, 91, 6), // "p2_lat"
QT_MOC_LITERAL(16, 98, 7), // "p2_long"
QT_MOC_LITERAL(17, 106, 12), // "sendToRotate"
QT_MOC_LITERAL(18, 119, 10), // "numOfTiles"
QT_MOC_LITERAL(19, 130, 8), // "QString&"
QT_MOC_LITERAL(20, 139, 5), // "layer"
QT_MOC_LITERAL(21, 145, 3), // "azm"
QT_MOC_LITERAL(22, 149, 16) // "sendToLoadNoText"

    },
    "TilesAnalyzer\0sendToProgram\0\0QStringList&\0"
    "tiles\0float&\0w1\0h1\0w2\0h2\0w3\0h3\0w4\0"
    "p1_lat\0p1_long\0p2_lat\0p2_long\0"
    "sendToRotate\0numOfTiles\0QString&\0layer\0"
    "azm\0sendToLoadNoText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TilesAnalyzer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,   12,   29,    2, 0x06 /* Public */,
      17,    4,   54,    2, 0x06 /* Public */,
      22,    3,   63,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 5,    4,    6,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 19, 0x80000000 | 19,    4,   18,   20,   21,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 19,    4,   18,   20,

       0        // eod
};

void TilesAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TilesAnalyzer *_t = static_cast<TilesAnalyzer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToProgram((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6])),(*reinterpret_cast< float(*)>(_a[7])),(*reinterpret_cast< float(*)>(_a[8])),(*reinterpret_cast< float(*)>(_a[9])),(*reinterpret_cast< float(*)>(_a[10])),(*reinterpret_cast< float(*)>(_a[11])),(*reinterpret_cast< float(*)>(_a[12]))); break;
        case 1: _t->sendToRotate((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->sendToLoadNoText((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TilesAnalyzer::*)(QStringList & , float & , float & , float & , float & , float & , float & , float & , float & , float & , float & , float & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TilesAnalyzer::sendToProgram)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TilesAnalyzer::*)(QStringList & , int , QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TilesAnalyzer::sendToRotate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TilesAnalyzer::*)(QStringList & , int , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TilesAnalyzer::sendToLoadNoText)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TilesAnalyzer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TilesAnalyzer.data,
      qt_meta_data_TilesAnalyzer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TilesAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TilesAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TilesAnalyzer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TilesAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TilesAnalyzer::sendToProgram(QStringList & _t1, float & _t2, float & _t3, float & _t4, float & _t5, float & _t6, float & _t7, float & _t8, float & _t9, float & _t10, float & _t11, float & _t12)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)), const_cast<void*>(reinterpret_cast<const void*>(&_t9)), const_cast<void*>(reinterpret_cast<const void*>(&_t10)), const_cast<void*>(reinterpret_cast<const void*>(&_t11)), const_cast<void*>(reinterpret_cast<const void*>(&_t12)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TilesAnalyzer::sendToRotate(QStringList & _t1, int _t2, QString & _t3, QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TilesAnalyzer::sendToLoadNoText(QStringList & _t1, int _t2, QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
