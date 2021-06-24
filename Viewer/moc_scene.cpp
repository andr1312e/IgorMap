/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "scene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
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
       7,       // revision
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
        GrideGL *_t = static_cast<GrideGL *>(_o);
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

QT_INIT_METAOBJECT const QMetaObject GrideGL::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GrideGL.data,
      qt_meta_data_GrideGL,  qt_static_metacall, nullptr, nullptr}
};


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
    QByteArrayData data[6];
    char stringdata0[42];
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
QT_MOC_LITERAL(5, 28, 13) // "translateSlot"

    },
    "MapGL\0getNewMap\0\0doc\0update\0translateSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapGL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       5,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QJsonDocument,    3,
    QMetaType::Void,

       0        // eod
};

void MapGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MapGL *_t = static_cast<MapGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getNewMap((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 1: _t->update((*reinterpret_cast< QJsonDocument(*)>(_a[1]))); break;
        case 2: _t->translateSlot(); break;
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

QT_INIT_METAOBJECT const QMetaObject MapGL::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MapGL.data,
      qt_meta_data_MapGL,  qt_static_metacall, nullptr, nullptr}
};


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
void MapGL::getNewMap(QJsonDocument _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_NewGrideGL_t {
    QByteArrayData data[1];
    char stringdata0[11];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewGrideGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewGrideGL_t qt_meta_stringdata_NewGrideGL = {
    {
QT_MOC_LITERAL(0, 0, 10) // "NewGrideGL"

    },
    "NewGrideGL"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewGrideGL[] = {

 // content:
       7,       // revision
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

void NewGrideGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject NewGrideGL::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NewGrideGL.data,
      qt_meta_data_NewGrideGL,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NewGrideGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewGrideGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NewGrideGL.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NewGrideGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DSPGLData_t {
    QByteArrayData data[10];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DSPGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DSPGLData_t qt_meta_stringdata_DSPGLData = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DSPGLData"
QT_MOC_LITERAL(1, 10, 8), // "nextData"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 2), // "id"
QT_MOC_LITERAL(4, 23, 33), // "QSharedPointer<QVector<DSPDat..."
QT_MOC_LITERAL(5, 57, 12), // "sharedVector"
QT_MOC_LITERAL(6, 70, 14), // "setColorRanges"
QT_MOC_LITERAL(7, 85, 11), // "ColorRanges"
QT_MOC_LITERAL(8, 97, 11), // "colorRanges"
QT_MOC_LITERAL(9, 109, 12) // "eraseDSPData"

    },
    "DSPGLData\0nextData\0\0id\0"
    "QSharedPointer<QVector<DSPData> >\0"
    "sharedVector\0setColorRanges\0ColorRanges\0"
    "colorRanges\0eraseDSPData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DSPGLData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x0a /* Public */,
       6,    2,   34,    2, 0x0a /* Public */,
       9,    1,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    3,    8,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void DSPGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DSPGLData *_t = static_cast<DSPGLData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nextData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QSharedPointer<QVector<DSPData> >(*)>(_a[2]))); break;
        case 1: _t->setColorRanges((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< ColorRanges(*)>(_a[2]))); break;
        case 2: _t->eraseDSPData((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DSPGLData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DSPGLData.data,
      qt_meta_data_DSPGLData,  qt_static_metacall, nullptr, nullptr}
};


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
struct qt_meta_stringdata_SectorsGLData_t {
    QByteArrayData data[21];
    char stringdata0[271];
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
QT_MOC_LITERAL(20, 264, 6) // "action"

    },
    "SectorsGLData\0setStateSignal\0\0index\0"
    "ItemState\0state\0addSectorViewer\0size\0"
    "presetSectorSlot\0SharedSectorParameters\0"
    "sharedSector\0excludeSectorSlot\0"
    "addSectorSlot\0deleteSectorSlot\0"
    "sectorInFocus\0sectorOutFocus\0setColor\0"
    "color\0setBlinkingActions\0"
    "ActionsWithBlinkingSector\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorsGLData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       6,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   72,    2, 0x0a /* Public */,
      11,    1,   77,    2, 0x0a /* Public */,
      12,    2,   80,    2, 0x0a /* Public */,
      13,    1,   85,    2, 0x0a /* Public */,
      14,    1,   88,    2, 0x0a /* Public */,
      15,    0,   91,    2, 0x0a /* Public */,
      16,    1,   92,    2, 0x0a /* Public */,
      18,    2,   95,    2, 0x0a /* Public */,

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

       0        // eod
};

void SectorsGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SectorsGLData *_t = static_cast<SectorsGLData *>(_o);
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

QT_INIT_METAOBJECT const QMetaObject SectorsGLData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SectorsGLData.data,
      qt_meta_data_SectorsGLData,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SectorsGLData::setStateSignal(const quint8 _t1, const ItemState & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SectorsGLData::addSectorViewer(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_KTAGLData_t {
    QByteArrayData data[19];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KTAGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KTAGLData_t qt_meta_stringdata_KTAGLData = {
    {
QT_MOC_LITERAL(0, 0, 9), // "KTAGLData"
QT_MOC_LITERAL(1, 10, 14), // "addPOIMarkSlot"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "POIKtaMessage"
QT_MOC_LITERAL(4, 40, 3), // "msg"
QT_MOC_LITERAL(5, 44, 14), // "addVOIMarkSlot"
QT_MOC_LITERAL(6, 59, 14), // "VOIMarkMessage"
QT_MOC_LITERAL(7, 74, 11), // "eraseOldKTA"
QT_MOC_LITERAL(8, 86, 18), // "eraseOldSampledKTA"
QT_MOC_LITERAL(9, 105, 11), // "setKTAColor"
QT_MOC_LITERAL(10, 117, 5), // "isPOI"
QT_MOC_LITERAL(11, 123, 5), // "color"
QT_MOC_LITERAL(12, 129, 10), // "setKTASize"
QT_MOC_LITERAL(13, 140, 14), // "TextSizeAction"
QT_MOC_LITERAL(14, 155, 4), // "flag"
QT_MOC_LITERAL(15, 160, 5), // "value"
QT_MOC_LITERAL(16, 166, 19), // "drawSampledMarkSlot"
QT_MOC_LITERAL(17, 186, 31), // "QSharedPointer<QVector<float> >"
QT_MOC_LITERAL(18, 218, 5) // "array"

    },
    "KTAGLData\0addPOIMarkSlot\0\0POIKtaMessage\0"
    "msg\0addVOIMarkSlot\0VOIMarkMessage\0"
    "eraseOldKTA\0eraseOldSampledKTA\0"
    "setKTAColor\0isPOI\0color\0setKTASize\0"
    "TextSizeAction\0flag\0value\0drawSampledMarkSlot\0"
    "QSharedPointer<QVector<float> >\0array"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KTAGLData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    2,   57,    2, 0x0a /* Public */,
      12,    3,   62,    2, 0x0a /* Public */,
      16,    1,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QColor,   10,   11,
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 13, QMetaType::Float,   10,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void KTAGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KTAGLData *_t = static_cast<KTAGLData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addPOIMarkSlot((*reinterpret_cast< POIKtaMessage(*)>(_a[1]))); break;
        case 1: _t->addVOIMarkSlot((*reinterpret_cast< VOIMarkMessage(*)>(_a[1]))); break;
        case 2: _t->eraseOldKTA(); break;
        case 3: _t->eraseOldSampledKTA(); break;
        case 4: _t->setKTAColor((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        case 5: _t->setKTASize((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const TextSizeAction(*)>(_a[2])),(*reinterpret_cast< const float(*)>(_a[3]))); break;
        case 6: _t->drawSampledMarkSlot((*reinterpret_cast< QSharedPointer<QVector<float> >(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< POIKtaMessage >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< VOIMarkMessage >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KTAGLData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KTAGLData.data,
      qt_meta_data_KTAGLData,  qt_static_metacall, nullptr, nullptr}
};


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
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
struct qt_meta_stringdata_TraceGLData_t {
    QByteArrayData data[24];
    char stringdata0[265];
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
QT_MOC_LITERAL(9, 93, 12), // "addTraceMark"
QT_MOC_LITERAL(10, 106, 14), // "RLSOaimMessage"
QT_MOC_LITERAL(11, 121, 13), // "eraseOldTrace"
QT_MOC_LITERAL(12, 135, 7), // "idTrace"
QT_MOC_LITERAL(13, 143, 15), // "setLogBookColor"
QT_MOC_LITERAL(14, 159, 5), // "color"
QT_MOC_LITERAL(15, 165, 13), // "setTraceColor"
QT_MOC_LITERAL(16, 179, 12), // "setTextColor"
QT_MOC_LITERAL(17, 192, 11), // "setTextSize"
QT_MOC_LITERAL(18, 204, 14), // "TextSizeAction"
QT_MOC_LITERAL(19, 219, 4), // "flag"
QT_MOC_LITERAL(20, 224, 5), // "value"
QT_MOC_LITERAL(21, 230, 14), // "reCalcAllTrace"
QT_MOC_LITERAL(22, 245, 9), // "drawTrace"
QT_MOC_LITERAL(23, 255, 9) // "isDrawing"

    },
    "TraceGLData\0traceInfoToExtraWindow\0\0"
    "id\0h\0addExtraWindowSignal\0msgToVOI\0"
    "msg\0trackDrawingReset\0addTraceMark\0"
    "RLSOaimMessage\0eraseOldTrace\0idTrace\0"
    "setLogBookColor\0color\0setTraceColor\0"
    "setTextColor\0setTextSize\0TextSizeAction\0"
    "flag\0value\0reCalcAllTrace\0drawTrace\0"
    "isDrawing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TraceGLData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       5,    1,   79,    2, 0x06 /* Public */,
       6,    1,   82,    2, 0x06 /* Public */,
       8,    0,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   86,    2, 0x0a /* Public */,
      11,    1,   89,    2, 0x0a /* Public */,
      13,    1,   92,    2, 0x0a /* Public */,
      15,    1,   95,    2, 0x0a /* Public */,
      16,    1,   98,    2, 0x0a /* Public */,
      17,    2,  101,    2, 0x0a /* Public */,
      21,    0,  106,    2, 0x0a /* Public */,
      22,    2,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,    3,    4,
    QMetaType::Void, QMetaType::UShort,    3,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,    7,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::QColor,   14,
    QMetaType::Void, QMetaType::QColor,   14,
    QMetaType::Void, QMetaType::QColor,   14,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Float,   19,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::Bool,    3,   23,

       0        // eod
};

void TraceGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TraceGLData *_t = static_cast<TraceGLData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->traceInfoToExtraWindow((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 1: _t->addExtraWindowSignal((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 2: _t->msgToVOI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->trackDrawingReset(); break;
        case 4: _t->addTraceMark((*reinterpret_cast< RLSOaimMessage(*)>(_a[1]))); break;
        case 5: _t->eraseOldTrace((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->setLogBookColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 7: _t->setTraceColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 8: _t->setTextColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 9: _t->setTextSize((*reinterpret_cast< const TextSizeAction(*)>(_a[1])),(*reinterpret_cast< const float(*)>(_a[2]))); break;
        case 10: _t->reCalcAllTrace(); break;
        case 11: _t->drawTrace((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RLSOaimMessage >(); break;
            }
            break;
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
    }
}

QT_INIT_METAOBJECT const QMetaObject TraceGLData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TraceGLData.data,
      qt_meta_data_TraceGLData,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void TraceGLData::traceInfoToExtraWindow(quint16 _t1, quint16 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TraceGLData::addExtraWindowSignal(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TraceGLData::msgToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TraceGLData::trackDrawingReset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
struct qt_meta_stringdata_Test3D_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Test3D_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Test3D_t qt_meta_stringdata_Test3D = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Test3D"
QT_MOC_LITERAL(1, 7, 12), // "addTraceMark"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "RLSOaimMessage"
QT_MOC_LITERAL(4, 36, 3) // "msg"

    },
    "Test3D\0addTraceMark\0\0RLSOaimMessage\0"
    "msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Test3D[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Test3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Test3D *_t = static_cast<Test3D *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addTraceMark((*reinterpret_cast< RLSOaimMessage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RLSOaimMessage >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Test3D::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Test3D.data,
      qt_meta_data_Test3D,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Test3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Test3D::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Test3D.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Test3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_RayGLData_t {
    QByteArrayData data[9];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RayGLData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RayGLData_t qt_meta_stringdata_RayGLData = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RayGLData"
QT_MOC_LITERAL(1, 10, 16), // "updateRaySetSlot"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "RaySet"
QT_MOC_LITERAL(4, 35, 3), // "set"
QT_MOC_LITERAL(5, 39, 8), // "setColor"
QT_MOC_LITERAL(6, 48, 5), // "color"
QT_MOC_LITERAL(7, 54, 10), // "setMaxDist"
QT_MOC_LITERAL(8, 65, 5) // "value"

    },
    "RayGLData\0updateRaySetSlot\0\0RaySet\0"
    "set\0setColor\0color\0setMaxDist\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RayGLData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    1,   32,    2, 0x0a /* Public */,
       7,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QColor,    6,
    QMetaType::Void, QMetaType::Float,    8,

       0        // eod
};

void RayGLData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RayGLData *_t = static_cast<RayGLData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateRaySetSlot((*reinterpret_cast< RaySet(*)>(_a[1]))); break;
        case 1: _t->setColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: _t->setMaxDist((*reinterpret_cast< const float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RaySet >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RayGLData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RayGLData.data,
      qt_meta_data_RayGLData,  qt_static_metacall, nullptr, nullptr}
};


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
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_ExtraWindow_t {
    QByteArrayData data[3];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ExtraWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ExtraWindow_t qt_meta_stringdata_ExtraWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ExtraWindow"
QT_MOC_LITERAL(1, 12, 9), // "updateDSP"
QT_MOC_LITERAL(2, 22, 0) // ""

    },
    "ExtraWindow\0updateDSP\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ExtraWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ExtraWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ExtraWindow *_t = static_cast<ExtraWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateDSP(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ExtraWindow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ExtraWindow.data,
      qt_meta_data_ExtraWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ExtraWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExtraWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ExtraWindow.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ExtraWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_Scene_t {
    QByteArrayData data[27];
    char stringdata0[314];
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
QT_MOC_LITERAL(11, 123, 14), // "addExtraWindow"
QT_MOC_LITERAL(12, 138, 23), // "updateInfoInExtraWindow"
QT_MOC_LITERAL(13, 162, 2), // "id"
QT_MOC_LITERAL(14, 165, 1), // "h"
QT_MOC_LITERAL(15, 167, 20), // "changeProjectionSlot"
QT_MOC_LITERAL(16, 188, 13), // "setBackground"
QT_MOC_LITERAL(17, 202, 5), // "color"
QT_MOC_LITERAL(18, 208, 10), // "setDistMax"
QT_MOC_LITERAL(19, 219, 5), // "value"
QT_MOC_LITERAL(20, 225, 19), // "initSceneProperties"
QT_MOC_LITERAL(21, 245, 19), // "SceneCustomDataInit"
QT_MOC_LITERAL(22, 265, 5), // "cData"
QT_MOC_LITERAL(23, 271, 19), // "setForwardSpeedSlot"
QT_MOC_LITERAL(24, 291, 2), // "vy"
QT_MOC_LITERAL(25, 294, 16), // "setSideSpeedSlot"
QT_MOC_LITERAL(26, 311, 2) // "vx"

    },
    "Scene\0resizeRequest\0\0size\0KTASamplingRequest\0"
    "leftBottom\0rightTop\0targetingAddRequest\0"
    "point\0isQuick\0targetingExcludeRequest\0"
    "addExtraWindow\0updateInfoInExtraWindow\0"
    "id\0h\0changeProjectionSlot\0setBackground\0"
    "color\0setDistMax\0value\0initSceneProperties\0"
    "SceneCustomDataInit\0cData\0setForwardSpeedSlot\0"
    "vy\0setSideSpeedSlot\0vx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Scene[] = {

 // content:
       7,       // revision
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
      12,    2,   93,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,
      18,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,
      23,    1,  110,    2, 0x0a /* Public */,
      25,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QSize,    3,
    QMetaType::Void, QMetaType::QPointF, QMetaType::QPointF,    5,    6,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,    8,    9,
    QMetaType::Void, QMetaType::QPointF,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort,   13,   14,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QColor,   17,
    QMetaType::Void, QMetaType::UShort,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::Float,   24,
    QMetaType::Void, QMetaType::Float,   26,

       0        // eod
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Scene *_t = static_cast<Scene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resizeRequest((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 1: _t->KTASamplingRequest((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 2: _t->targetingAddRequest((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->targetingExcludeRequest((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 4: _t->addExtraWindow((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 5: _t->updateInfoInExtraWindow((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 6: _t->changeProjectionSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setBackground((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 8: _t->setDistMax((*reinterpret_cast< const quint16(*)>(_a[1]))); break;
        case 9: _t->initSceneProperties((*reinterpret_cast< const SceneCustomDataInit(*)>(_a[1]))); break;
        case 10: _t->setForwardSpeedSlot((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->setSideSpeedSlot((*reinterpret_cast< float(*)>(_a[1]))); break;
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

QT_INIT_METAOBJECT const QMetaObject Scene::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Scene.data,
      qt_meta_data_Scene,  qt_static_metacall, nullptr, nullptr}
};


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
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Scene::KTASamplingRequest(const QPointF _t1, const QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Scene::targetingAddRequest(const QPointF _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Scene::targetingExcludeRequest(const QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
