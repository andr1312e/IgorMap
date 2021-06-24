/****************************************************************************
** Meta object code from reading C++ file 'mapdebugger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mapdebugger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapdebugger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapDebugger_t {
    QByteArrayData data[14];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapDebugger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapDebugger_t qt_meta_stringdata_MapDebugger = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MapDebugger"
QT_MOC_LITERAL(1, 12, 16), // "requestForNewMap"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "doc"
QT_MOC_LITERAL(4, 34, 13), // "moveCenterOnX"
QT_MOC_LITERAL(5, 48, 2), // "vx"
QT_MOC_LITERAL(6, 51, 13), // "moveCenterOnY"
QT_MOC_LITERAL(7, 65, 2), // "vy"
QT_MOC_LITERAL(8, 68, 16), // "updateViewCenter"
QT_MOC_LITERAL(9, 85, 6), // "center"
QT_MOC_LITERAL(10, 92, 19), // "acceptButtonClicked"
QT_MOC_LITERAL(11, 112, 18), // "clearButtonClicked"
QT_MOC_LITERAL(12, 131, 19), // "movingButtonClicked"
QT_MOC_LITERAL(13, 151, 19) // "rotateButtonClicked"

    },
    "MapDebugger\0requestForNewMap\0\0doc\0"
    "moveCenterOnX\0vx\0moveCenterOnY\0vy\0"
    "updateViewCenter\0center\0acceptButtonClicked\0"
    "clearButtonClicked\0movingButtonClicked\0"
    "rotateButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapDebugger[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   63,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x08 /* Private */,
      11,    0,   67,    2, 0x08 /* Private */,
      12,    0,   68,    2, 0x08 /* Private */,
      13,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QVector3D,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MapDebugger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapDebugger *_t = static_cast<MapDebugger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestForNewMap((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 1: _t->moveCenterOnX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->moveCenterOnY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->updateViewCenter((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 4: _t->acceptButtonClicked(); break;
        case 5: _t->clearButtonClicked(); break;
        case 6: _t->movingButtonClicked(); break;
        case 7: _t->rotateButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MapDebugger::*)(QJsonDocument );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::requestForNewMap)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MapDebugger::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::moveCenterOnX)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MapDebugger::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::moveCenterOnY)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MapDebugger::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_MapDebugger.data,
      qt_meta_data_MapDebugger,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MapDebugger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapDebugger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapDebugger.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int MapDebugger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MapDebugger::requestForNewMap(QJsonDocument _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapDebugger::moveCenterOnX(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MapDebugger::moveCenterOnY(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
