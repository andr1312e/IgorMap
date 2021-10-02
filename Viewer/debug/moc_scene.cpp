/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Scene/scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GrideGL_t {
    QByteArrayData data[14];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GrideGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GrideGL_t qt_meta_stringdata_GrideGL = {
    {
QT_MOC_LITERAL(0, 0, 7), // "GrideGL"
QT_MOC_LITERAL(1, 8, 13), // "setGrideColor"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "color"
QT_MOC_LITERAL(4, 29, 12), // "setTextColor"
QT_MOC_LITERAL(5, 42, 14), // "setDistDiscret"
QT_MOC_LITERAL(6, 57, 5), // "value"
QT_MOC_LITERAL(7, 63, 12), // "setAzDiscret"
QT_MOC_LITERAL(8, 76, 11), // "setTextSize"
QT_MOC_LITERAL(9, 88, 14), // "TextSizeAction"
QT_MOC_LITERAL(10, 103, 4), // "flag"
QT_MOC_LITERAL(11, 108, 14), // "setAzMarkOnOff"
QT_MOC_LITERAL(12, 123, 16), // "setDistMarkOnOff"
QT_MOC_LITERAL(13, 140, 15) // "resetCameraSlot"

    },
    "GrideGL\0setGrideColor\0\0color\0setTextColor\0"
    "setDistDiscret\0value\0setAzDiscret\0"
    "setTextSize\0TextSizeAction\0flag\0"
    "setAzMarkOnOff\0setDistMarkOnOff\0"
    "resetCameraSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GrideGL[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    1,   57,    2, 0x0a /* Public */,
       5,    1,   60,    2, 0x0a /* Public */,
       7,    1,   63,    2, 0x0a /* Public */,
       8,    2,   66,    2, 0x0a /* Public */,
      11,    1,   71,    2, 0x0a /* Public */,
      12,    1,   74,    2, 0x0a /* Public */,
      13,    0,   77,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::UShort,    6,
    QMetaType::Void, QMetaType::UShort,    6,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Float,   10,    6,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,

       0        // eod
};

void GrideGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GrideGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setGrideColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->setTextColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->setDistDiscret((*reinterpret_cast< const quint16(*)>(_a[1]))); break;
        case 3: _t->setAzDiscret((*reinterpret_cast< const quint16(*)>(_a[1]))); break;
        case 4: _t->setTextSize((*reinterpret_cast< const TextSizeAction(*)>(_a[1])),(*reinterpret_cast< const float(*)>(_a[2]))); break;
        case 5: _t->setAzMarkOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setDistMarkOnOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->resetCameraSlot(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GrideGL::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GrideGL.data,
    qt_meta_data_GrideGL,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GrideGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GrideGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GrideGL.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GrideGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
struct qt_meta_stringdata_MapGL_t {
    QByteArrayData data[13];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapGL_t qt_meta_stringdata_MapGL = {
    {
QT_MOC_LITERAL(0, 0, 5), // "MapGL"
QT_MOC_LITERAL(1, 6, 9), // "getNewMap"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 3), // "doc"
QT_MOC_LITERAL(4, 21, 6), // "update"
QT_MOC_LITERAL(5, 28, 19), // "updateViewCenterGeo"
QT_MOC_LITERAL(6, 48, 10), // "_centerGeo"
QT_MOC_LITERAL(7, 59, 13), // "translateSlot"
QT_MOC_LITERAL(8, 73, 13), // "clearAllTiles"
QT_MOC_LITERAL(9, 87, 9), // "updateMap"
QT_MOC_LITERAL(10, 97, 5), // "paths"
QT_MOC_LITERAL(11, 103, 16), // "QVector<GLfloat>"
QT_MOC_LITERAL(12, 120, 6) // "points"

    },
    "MapGL\0getNewMap\0\0doc\0update\0"
    "updateViewCenterGeo\0_centerGeo\0"
    "translateSlot\0clearAllTiles\0updateMap\0"
    "paths\0QVector<GLfloat>\0points"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapGL[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       5,    1,   50,    2, 0x0a /* Public */,
       7,    0,   53,    2, 0x0a /* Public */,
       8,    0,   54,    2, 0x0a /* Public */,
       9,    2,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,
    QMetaType::Void, QMetaType::QPointF,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList, 0x80000000 | 11,   10,   12,

       0        // eod
};

void MapGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MapGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getNewMap((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 1: _t->update((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 2: _t->updateViewCenterGeo((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 3: _t->translateSlot(); break;
        case 4: _t->clearAllTiles(); break;
        case 5: _t->updateMap((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QVector<GLfloat>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MapGL::*)(QJsonDocument );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MapGL::getNewMap)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MapGL::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MapGL.data,
    qt_meta_data_MapGL,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MapGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapGL.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MapGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MapGL::getNewMap(QJsonDocument _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_DSPGLData_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DSPGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DSPGLData_t qt_meta_stringdata_DSPGLData = {
    {
QT_MOC_LITERAL(0, 0, 9) // "DSPGLData"

    },
    "DSPGLData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DSPGLData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DSPGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DSPGLData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DSPGLData.data,
    qt_meta_data_DSPGLData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DSPGLData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DSPGLData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DSPGLData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DSPGLData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_SectorsGLData_t {
    QByteArrayData data[22];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SectorsGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SectorsGLData_t qt_meta_stringdata_SectorsGLData = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SectorsGLData"
QT_MOC_LITERAL(1, 14, 14), // "setStateSignal"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "index"
QT_MOC_LITERAL(4, 36, 9), // "ItemState"
QT_MOC_LITERAL(5, 46, 5), // "state"
QT_MOC_LITERAL(6, 52, 15), // "addSectorViewer"
QT_MOC_LITERAL(7, 68, 4), // "size"
QT_MOC_LITERAL(8, 73, 16), // "presetSectorSlot"
QT_MOC_LITERAL(9, 90, 22), // "SharedSectorParameters"
QT_MOC_LITERAL(10, 113, 12), // "sharedSector"
QT_MOC_LITERAL(11, 126, 17), // "excludeSectorSlot"
QT_MOC_LITERAL(12, 144, 13), // "addSectorSlot"
QT_MOC_LITERAL(13, 158, 16), // "deleteSectorSlot"
QT_MOC_LITERAL(14, 175, 13), // "sectorInFocus"
QT_MOC_LITERAL(15, 189, 14), // "sectorOutFocus"
QT_MOC_LITERAL(16, 204, 8), // "setColor"
QT_MOC_LITERAL(17, 213, 5), // "color"
QT_MOC_LITERAL(18, 219, 18), // "setBlinkingActions"
QT_MOC_LITERAL(19, 238, 25), // "ActionsWithBlinkingSector"
QT_MOC_LITERAL(20, 264, 6), // "action"
QT_MOC_LITERAL(21, 271, 22) // "maxDistanceChangedSlot"

    },
    "SectorsGLData\0setStateSignal\0\0index\0"
    "ItemState\0state\0addSectorViewer\0size\0"
    "presetSectorSlot\0SharedSectorParameters\0"
    "sharedSector\0excludeSectorSlot\0"
    "addSectorSlot\0deleteSectorSlot\0"
    "sectorInFocus\0sectorOutFocus\0setColor\0"
    "color\0setBlinkingActions\0"
    "ActionsWithBlinkingSector\0action\0"
    "maxDistanceChangedSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorsGLData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   77,    2, 0x0a /* Public */,
      11,    1,   82,    2, 0x0a /* Public */,
      12,    2,   85,    2, 0x0a /* Public */,
      13,    1,   90,    2, 0x0a /* Public */,
      14,    1,   93,    2, 0x0a /* Public */,
      15,    0,   96,    2, 0x0a /* Public */,
      16,    1,   97,    2, 0x0a /* Public */,
      18,    2,  100,    2, 0x0a /* Public */,
      21,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::UChar,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 9,    3,   10,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 9,    3,   10,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 19,    3,   20,
    QMetaType::Void,

       0        // eod
};

void SectorsGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SectorsGLData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStateSignal((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< const ItemState(*)>(_a[2]))); break;
        case 1: _t->addSectorViewer((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 2: _t->presetSectorSlot((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< SharedSectorParameters(*)>(_a[2]))); break;
        case 3: _t->excludeSectorSlot((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 4: _t->addSectorSlot((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< SharedSectorParameters(*)>(_a[2]))); break;
        case 5: _t->deleteSectorSlot((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 6: _t->sectorInFocus((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 7: _t->sectorOutFocus(); break;
        case 8: _t->setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 9: _t->setBlinkingActions((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< ActionsWithBlinkingSector(*)>(_a[2]))); break;
        case 10: _t->maxDistanceChangedSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SectorsGLData::*)(const quint8 , const ItemState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsGLData::setStateSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SectorsGLData::*)(const quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsGLData::addSectorViewer)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SectorsGLData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SectorsGLData.data,
    qt_meta_data_SectorsGLData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SectorsGLData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SectorsGLData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SectorsGLData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SectorsGLData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SectorsGLData::setStateSignal(const quint8 _t1, const ItemState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SectorsGLData::addSectorViewer(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_KTAGLData_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KTAGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KTAGLData_t qt_meta_stringdata_KTAGLData = {
    {
QT_MOC_LITERAL(0, 0, 9) // "KTAGLData"

    },
    "KTAGLData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KTAGLData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void KTAGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject KTAGLData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_KTAGLData.data,
    qt_meta_data_KTAGLData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KTAGLData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KTAGLData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KTAGLData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int KTAGLData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_TraceGLData_t {
    QByteArrayData data[26];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TraceGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TraceGLData_t qt_meta_stringdata_TraceGLData = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TraceGLData"
QT_MOC_LITERAL(1, 12, 22), // "traceInfoToExtraWindow"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 2), // "id"
QT_MOC_LITERAL(4, 39, 1), // "h"
QT_MOC_LITERAL(5, 41, 20), // "addExtraWindowSignal"
QT_MOC_LITERAL(6, 62, 8), // "msgToVOI"
QT_MOC_LITERAL(7, 71, 3), // "msg"
QT_MOC_LITERAL(8, 75, 17), // "trackDrawingReset"
QT_MOC_LITERAL(9, 93, 13), // "traceDistance"
QT_MOC_LITERAL(10, 107, 8), // "idObject"
QT_MOC_LITERAL(11, 116, 4), // "dist"
QT_MOC_LITERAL(12, 121, 16), // "clearTraceOnGrid"
QT_MOC_LITERAL(13, 138, 13), // "eraseOldTrace"
QT_MOC_LITERAL(14, 152, 7), // "idTrace"
QT_MOC_LITERAL(15, 160, 15), // "setLogBookColor"
QT_MOC_LITERAL(16, 176, 5), // "color"
QT_MOC_LITERAL(17, 182, 13), // "setTraceColor"
QT_MOC_LITERAL(18, 196, 12), // "setTextColor"
QT_MOC_LITERAL(19, 209, 11), // "setTextSize"
QT_MOC_LITERAL(20, 221, 14), // "TextSizeAction"
QT_MOC_LITERAL(21, 236, 4), // "flag"
QT_MOC_LITERAL(22, 241, 5), // "value"
QT_MOC_LITERAL(23, 247, 14), // "reCalcAllTrace"
QT_MOC_LITERAL(24, 262, 9), // "drawTrace"
QT_MOC_LITERAL(25, 272, 9) // "isDrawing"

    },
    "TraceGLData\0traceInfoToExtraWindow\0\0"
    "id\0h\0addExtraWindowSignal\0msgToVOI\0"
    "msg\0trackDrawingReset\0traceDistance\0"
    "idObject\0dist\0clearTraceOnGrid\0"
    "eraseOldTrace\0idTrace\0setLogBookColor\0"
    "color\0setTraceColor\0setTextColor\0"
    "setTextSize\0TextSizeAction\0flag\0value\0"
    "reCalcAllTrace\0drawTrace\0isDrawing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TraceGLData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       5,    1,   84,    2, 0x06 /* Public */,
       6,    1,   87,    2, 0x06 /* Public */,
       8,    0,   90,    2, 0x06 /* Public */,
       9,    2,   91,    2, 0x06 /* Public */,
      12,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   99,    2, 0x0a /* Public */,
      15,    1,  102,    2, 0x0a /* Public */,
      17,    1,  105,    2, 0x0a /* Public */,
      18,    1,  108,    2, 0x0a /* Public */,
      19,    2,  111,    2, 0x0a /* Public */,
      23,    0,  116,    2, 0x0a /* Public */,
      24,    2,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,    3,    4,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   10,   11,
    QMetaType::Void, QMetaType::Int,   10,

 // slots: parameters
    QMetaType::Void, QMetaType::UInt,   14,
    QMetaType::Void, QMetaType::QColor,   16,
    QMetaType::Void, QMetaType::QColor,   16,
    QMetaType::Void, QMetaType::QColor,   16,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Float,   21,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::Bool,    3,   25,

       0        // eod
};

void TraceGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TraceGLData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->traceInfoToExtraWindow((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 1: _t->addExtraWindowSignal((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->msgToVOI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->trackDrawingReset(); break;
        case 4: _t->traceDistance((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 5: _t->clearTraceOnGrid((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 6: _t->eraseOldTrace((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 7: _t->setLogBookColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 8: _t->setTraceColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 9: _t->setTextColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 10: _t->setTextSize((*reinterpret_cast< const TextSizeAction(*)>(_a[1])),(*reinterpret_cast< const float(*)>(_a[2]))); break;
        case 11: _t->reCalcAllTrace(); break;
        case 12: _t->drawTrace((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TraceGLData::*)(quint16 , quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TraceGLData::traceInfoToExtraWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TraceGLData::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TraceGLData::addExtraWindowSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TraceGLData::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TraceGLData::msgToVOI)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TraceGLData::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TraceGLData::trackDrawingReset)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TraceGLData::*)(qint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TraceGLData::traceDistance)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TraceGLData::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TraceGLData::clearTraceOnGrid)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TraceGLData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TraceGLData.data,
    qt_meta_data_TraceGLData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TraceGLData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TraceGLData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TraceGLData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TraceGLData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void TraceGLData::traceInfoToExtraWindow(quint16 _t1, quint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TraceGLData::addExtraWindowSignal(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TraceGLData::msgToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TraceGLData::trackDrawingReset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TraceGLData::traceDistance(qint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TraceGLData::clearTraceOnGrid(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_RayGLData_t {
    QByteArrayData data[1];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RayGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RayGLData_t qt_meta_stringdata_RayGLData = {
    {
QT_MOC_LITERAL(0, 0, 9) // "RayGLData"

    },
    "RayGLData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RayGLData[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void RayGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject RayGLData::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_RayGLData.data,
    qt_meta_data_RayGLData,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RayGLData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RayGLData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RayGLData.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RayGLData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Scene_t {
    QByteArrayData data[25];
    char stringdata0[310];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Scene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Scene_t qt_meta_stringdata_Scene = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Scene"
QT_MOC_LITERAL(1, 6, 13), // "resizeRequest"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "size"
QT_MOC_LITERAL(4, 26, 18), // "KTASamplingRequest"
QT_MOC_LITERAL(5, 45, 10), // "leftBottom"
QT_MOC_LITERAL(6, 56, 8), // "rightTop"
QT_MOC_LITERAL(7, 65, 19), // "targetingAddRequest"
QT_MOC_LITERAL(8, 85, 5), // "point"
QT_MOC_LITERAL(9, 91, 7), // "isQuick"
QT_MOC_LITERAL(10, 99, 23), // "targetingExcludeRequest"
QT_MOC_LITERAL(11, 123, 20), // "changeProjectionSlot"
QT_MOC_LITERAL(12, 144, 13), // "setBackground"
QT_MOC_LITERAL(13, 158, 5), // "color"
QT_MOC_LITERAL(14, 164, 10), // "setDistMax"
QT_MOC_LITERAL(15, 175, 5), // "value"
QT_MOC_LITERAL(16, 181, 19), // "initSceneProperties"
QT_MOC_LITERAL(17, 201, 19), // "SceneCustomDataInit"
QT_MOC_LITERAL(18, 221, 5), // "cData"
QT_MOC_LITERAL(19, 227, 19), // "setForwardSpeedSlot"
QT_MOC_LITERAL(20, 247, 2), // "vy"
QT_MOC_LITERAL(21, 250, 16), // "setSideSpeedSlot"
QT_MOC_LITERAL(22, 267, 2), // "vx"
QT_MOC_LITERAL(23, 270, 17), // "viewCenterRequest"
QT_MOC_LITERAL(24, 288, 21) // "programmUpdateScaling"

    },
    "Scene\0resizeRequest\0\0size\0KTASamplingRequest\0"
    "leftBottom\0rightTop\0targetingAddRequest\0"
    "point\0isQuick\0targetingExcludeRequest\0"
    "changeProjectionSlot\0setBackground\0"
    "color\0setDistMax\0value\0initSceneProperties\0"
    "SceneCustomDataInit\0cData\0setForwardSpeedSlot\0"
    "vy\0setSideSpeedSlot\0vx\0viewCenterRequest\0"
    "programmUpdateScaling"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    2,   77,    2, 0x06 /* Public */,
       7,    2,   82,    2, 0x06 /* Public */,
      10,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   90,    2, 0x0a /* Public */,
      12,    1,   93,    2, 0x0a /* Public */,
      14,    1,   96,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,
      19,    1,  102,    2, 0x0a /* Public */,
      21,    1,  105,    2, 0x0a /* Public */,
      23,    0,  108,    2, 0x0a /* Public */,
      24,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QSize,    3,
    QMetaType::Void, QMetaType::QPointF, QMetaType::QPointF,    5,    6,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,    8,    9,
    QMetaType::Void, QMetaType::QPointF,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QColor,   13,
    QMetaType::Void, QMetaType::UShort,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Float,   20,
    QMetaType::Void, QMetaType::Float,   22,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Scene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeRequest((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 1: _t->KTASamplingRequest((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 2: _t->targetingAddRequest((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->targetingExcludeRequest((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 4: _t->changeProjectionSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setBackground((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 6: _t->setDistMax((*reinterpret_cast< const quint16(*)>(_a[1]))); break;
        case 7: _t->initSceneProperties((*reinterpret_cast< const SceneCustomDataInit(*)>(_a[1]))); break;
        case 8: _t->setForwardSpeedSlot((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setSideSpeedSlot((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 10: _t->viewCenterRequest(); break;
        case 11: _t->programmUpdateScaling(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Scene::*)(const QSize );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scene::resizeRequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Scene::*)(const QPointF , const QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scene::KTASamplingRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Scene::*)(const QPointF , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scene::targetingAddRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Scene::*)(const QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Scene::targetingExcludeRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Scene::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Scene.data,
    qt_meta_data_Scene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Scene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Scene.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions_3_3_Core"))
        return static_cast< QOpenGLFunctions_3_3_Core*>(this);
    return QObject::qt_metacast(_clname);
}

int Scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Scene::resizeRequest(const QSize _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Scene::KTASamplingRequest(const QPointF _t1, const QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Scene::targetingAddRequest(const QPointF _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Scene::targetingExcludeRequest(const QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
