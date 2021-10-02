/****************************************************************************
** Meta object code from reading C++ file 'mapdebugger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Widgets/Map/mapdebugger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mapdebugger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapDebugger_t {
    QByteArrayData data[23];
    char stringdata0[294];
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
QT_MOC_LITERAL(8, 68, 17), // "userCenterViewGeo"
QT_MOC_LITERAL(9, 86, 9), // "centerGeo"
QT_MOC_LITERAL(10, 96, 18), // "clearAllTilesOfMap"
QT_MOC_LITERAL(11, 115, 13), // "getViewCenter"
QT_MOC_LITERAL(12, 129, 13), // "infoForRender"
QT_MOC_LITERAL(13, 143, 5), // "paths"
QT_MOC_LITERAL(14, 149, 16), // "QVector<GLfloat>"
QT_MOC_LITERAL(15, 166, 6), // "points"
QT_MOC_LITERAL(16, 173, 16), // "updateViewCenter"
QT_MOC_LITERAL(17, 190, 6), // "center"
QT_MOC_LITERAL(18, 197, 17), // "parseJSONDocument"
QT_MOC_LITERAL(19, 215, 19), // "acceptButtonClicked"
QT_MOC_LITERAL(20, 235, 18), // "clearButtonClicked"
QT_MOC_LITERAL(21, 254, 19), // "movingButtonClicked"
QT_MOC_LITERAL(22, 274, 19) // "rotateButtonClicked"

    },
    "MapDebugger\0requestForNewMap\0\0doc\0"
    "moveCenterOnX\0vx\0moveCenterOnY\0vy\0"
    "userCenterViewGeo\0centerGeo\0"
    "clearAllTilesOfMap\0getViewCenter\0"
    "infoForRender\0paths\0QVector<GLfloat>\0"
    "points\0updateViewCenter\0center\0"
    "parseJSONDocument\0acceptButtonClicked\0"
    "clearButtonClicked\0movingButtonClicked\0"
    "rotateButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapDebugger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       8,    1,   88,    2, 0x06 /* Public */,
      10,    0,   91,    2, 0x06 /* Public */,
      11,    0,   92,    2, 0x06 /* Public */,
      12,    2,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   98,    2, 0x0a /* Public */,
      18,    1,  101,    2, 0x0a /* Public */,
      19,    0,  104,    2, 0x08 /* Private */,
      20,    0,  105,    2, 0x08 /* Private */,
      21,    0,  106,    2, 0x08 /* Private */,
      22,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::QPointF,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, 0x80000000 | 14,   13,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::QVector3D,   17,
    QMetaType::Void, QMetaType::QJsonDocument,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MapDebugger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MapDebugger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestForNewMap((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 1: _t->moveCenterOnX((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->moveCenterOnY((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->userCenterViewGeo((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 4: _t->clearAllTilesOfMap(); break;
        case 5: _t->getViewCenter(); break;
        case 6: _t->infoForRender((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QVector<GLfloat>(*)>(_a[2]))); break;
        case 7: _t->updateViewCenter((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 8: _t->parseJSONDocument((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 9: _t->acceptButtonClicked(); break;
        case 10: _t->clearButtonClicked(); break;
        case 11: _t->movingButtonClicked(); break;
        case 12: _t->rotateButtonClicked(); break;
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
        {
            using _t = void (MapDebugger::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::userCenterViewGeo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MapDebugger::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::clearAllTilesOfMap)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MapDebugger::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::getViewCenter)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MapDebugger::*)(QStringList , QVector<GLfloat> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapDebugger::infoForRender)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MapDebugger::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_MapDebugger.data,
    qt_meta_data_MapDebugger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
void MapDebugger::requestForNewMap(QJsonDocument _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MapDebugger::moveCenterOnX(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MapDebugger::moveCenterOnY(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MapDebugger::userCenterViewGeo(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MapDebugger::clearAllTilesOfMap()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MapDebugger::getViewCenter()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MapDebugger::infoForRender(QStringList _t1, QVector<GLfloat> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
