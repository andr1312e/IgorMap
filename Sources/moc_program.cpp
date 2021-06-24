/****************************************************************************
** Meta object code from reading C++ file 'program.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "program.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'program.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Program_t {
    QByteArrayData data[19];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Program_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Program_t qt_meta_stringdata_Program = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Program"
QT_MOC_LITERAL(1, 8, 13), // "sendToAnalyze"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "QVector<float>&"
QT_MOC_LITERAL(4, 39, 12), // "currentCords"
QT_MOC_LITERAL(5, 52, 4), // "int&"
QT_MOC_LITERAL(6, 57, 3), // "azm"
QT_MOC_LITERAL(7, 61, 5), // "layer"
QT_MOC_LITERAL(8, 67, 5), // "bool&"
QT_MOC_LITERAL(9, 73, 7), // "repaint"
QT_MOC_LITERAL(10, 81, 16), // "sendDataToServer"
QT_MOC_LITERAL(11, 98, 12), // "QStringList&"
QT_MOC_LITERAL(12, 111, 5), // "tiles"
QT_MOC_LITERAL(13, 117, 9), // "clearDone"
QT_MOC_LITERAL(14, 127, 9), // "fastClear"
QT_MOC_LITERAL(15, 137, 7), // "execute"
QT_MOC_LITERAL(16, 145, 5), // "cords"
QT_MOC_LITERAL(17, 151, 7), // "allDone"
QT_MOC_LITERAL(18, 159, 10) // "doingClear"

    },
    "Program\0sendToAnalyze\0\0QVector<float>&\0"
    "currentCords\0int&\0azm\0layer\0bool&\0"
    "repaint\0sendDataToServer\0QStringList&\0"
    "tiles\0clearDone\0fastClear\0execute\0"
    "cords\0allDone\0doingClear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Program[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   49,    2, 0x06 /* Public */,
      10,    1,   58,    2, 0x06 /* Public */,
      13,    0,   61,    2, 0x06 /* Public */,
      14,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    4,   63,    2, 0x0a /* Public */,
      17,    1,   72,    2, 0x0a /* Public */,
      18,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 8,    4,    6,    7,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 8,   16,    6,    7,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void Program::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Program *_t = static_cast<Program *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToAnalyze((*reinterpret_cast< QVector<float>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: _t->sendDataToServer((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 2: _t->clearDone(); break;
        case 3: _t->fastClear(); break;
        case 4: _t->execute((*reinterpret_cast< QVector<float>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 5: _t->allDone((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 6: _t->doingClear(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Program::*)(QVector<float> & , int & , int & , bool & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Program::sendToAnalyze)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Program::*)(QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Program::sendDataToServer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Program::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Program::clearDone)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Program::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Program::fastClear)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Program::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Program.data,
      qt_meta_data_Program,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Program::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Program::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Program.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Program::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Program::sendToAnalyze(QVector<float> & _t1, int & _t2, int & _t3, bool & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Program::sendDataToServer(QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Program::clearDone()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Program::fastClear()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
