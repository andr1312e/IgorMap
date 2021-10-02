/****************************************************************************
** Meta object code from reading C++ file 'threadfilereaders.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "threadfilereaders.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadfilereaders.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadFileReader_t {
    QByteArrayData data[16];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadFileReader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadFileReader_t qt_meta_stringdata_ThreadFileReader = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ThreadFileReader"
QT_MOC_LITERAL(1, 17, 10), // "sendToLoad"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "QString&"
QT_MOC_LITERAL(4, 38, 4), // "tile"
QT_MOC_LITERAL(5, 43, 7), // "m_layer"
QT_MOC_LITERAL(6, 51, 3), // "azm"
QT_MOC_LITERAL(7, 55, 7), // "getting"
QT_MOC_LITERAL(8, 63, 12), // "QStringList&"
QT_MOC_LITERAL(9, 76, 5), // "tiles"
QT_MOC_LITERAL(10, 82, 12), // "numOfThreads"
QT_MOC_LITERAL(11, 95, 5), // "layer"
QT_MOC_LITERAL(12, 101, 7), // "sending"
QT_MOC_LITERAL(13, 109, 20), // "seekAvailableThreads"
QT_MOC_LITERAL(14, 130, 16), // "addThreadToQueue"
QT_MOC_LITERAL(15, 147, 19) // "loadImagesFromQueue"

    },
    "ThreadFileReader\0sendToLoad\0\0QString&\0"
    "tile\0m_layer\0azm\0getting\0QStringList&\0"
    "tiles\0numOfThreads\0layer\0sending\0"
    "seekAvailableThreads\0addThreadToQueue\0"
    "loadImagesFromQueue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadFileReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    4,   51,    2, 0x0a /* Public */,
      12,    0,   60,    2, 0x0a /* Public */,
      13,    0,   61,    2, 0x0a /* Public */,
      14,    0,   62,    2, 0x0a /* Public */,
      15,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 3,    9,   10,    6,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ThreadFileReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ThreadFileReader *_t = static_cast<ThreadFileReader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToLoad((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->getting((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->sending(); break;
        case 3: _t->seekAvailableThreads(); break;
        case 4: _t->addThreadToQueue(); break;
        case 5: _t->loadImagesFromQueue(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadFileReader::*)(QString & , QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadFileReader::sendToLoad)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadFileReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ThreadFileReader.data,
      qt_meta_data_ThreadFileReader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ThreadFileReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadFileReader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadFileReader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThreadFileReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ThreadFileReader::sendToLoad(QString & _t1, QString & _t2, QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
