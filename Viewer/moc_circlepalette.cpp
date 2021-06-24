/****************************************************************************
** Meta object code from reading C++ file 'circlepalette.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "circlepalette.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'circlepalette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GradientLabel_t {
    QByteArrayData data[8];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GradientLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GradientLabel_t qt_meta_stringdata_GradientLabel = {
    {
QT_MOC_LITERAL(0, 0, 13), // "GradientLabel"
QT_MOC_LITERAL(1, 14, 9), // "setColors"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "QVector<QColor>"
QT_MOC_LITERAL(4, 41, 6), // "colors"
QT_MOC_LITERAL(5, 48, 11), // "setPersents"
QT_MOC_LITERAL(6, 60, 12), // "QVector<int>"
QT_MOC_LITERAL(7, 73, 8) // "persents"

    },
    "GradientLabel\0setColors\0\0QVector<QColor>\0"
    "colors\0setPersents\0QVector<int>\0"
    "persents"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GradientLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       5,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void GradientLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GradientLabel *_t = static_cast<GradientLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setColors((*reinterpret_cast< QVector<QColor>(*)>(_a[1]))); break;
        case 1: _t->setPersents((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QColor> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GradientLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_GradientLabel.data,
      qt_meta_data_GradientLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GradientLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GradientLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GradientLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int GradientLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_RangeSlider_t {
    QByteArrayData data[13];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RangeSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RangeSlider_t qt_meta_stringdata_RangeSlider = {
    {
QT_MOC_LITERAL(0, 0, 11), // "RangeSlider"
QT_MOC_LITERAL(1, 12, 17), // "lowerValueChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "aLowerValue"
QT_MOC_LITERAL(4, 43, 17), // "upperValueChanged"
QT_MOC_LITERAL(5, 61, 11), // "aUpperValue"
QT_MOC_LITERAL(6, 73, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 86, 12), // "QVector<int>"
QT_MOC_LITERAL(8, 99, 5), // "range"
QT_MOC_LITERAL(9, 105, 12), // "setRangeType"
QT_MOC_LITERAL(10, 118, 6), // "Option"
QT_MOC_LITERAL(11, 125, 1), // "t"
QT_MOC_LITERAL(12, 127, 6) // "vector"

    },
    "RangeSlider\0lowerValueChanged\0\0"
    "aLowerValue\0upperValueChanged\0aUpperValue\0"
    "rangeChanged\0QVector<int>\0range\0"
    "setRangeType\0Option\0t\0vector"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RangeSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   48,    2, 0x0a /* Public */,
       9,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 7,   11,   12,

       0        // eod
};

void RangeSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RangeSlider *_t = static_cast<RangeSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lowerValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->upperValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->rangeChanged((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        case 3: _t->setRangeType((*reinterpret_cast< Option(*)>(_a[1]))); break;
        case 4: _t->setRangeType((*reinterpret_cast< Option(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RangeSlider::lowerValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RangeSlider::upperValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RangeSlider::*)(QVector<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RangeSlider::rangeChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RangeSlider::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RangeSlider.data,
      qt_meta_data_RangeSlider,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *RangeSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RangeSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RangeSlider.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int RangeSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void RangeSlider::lowerValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RangeSlider::upperValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RangeSlider::rangeChanged(QVector<int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_CirclePalette_t {
    QByteArrayData data[9];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CirclePalette_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CirclePalette_t qt_meta_stringdata_CirclePalette = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CirclePalette"
QT_MOC_LITERAL(1, 14, 21), // "selectedColorsChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "hoverColor"
QT_MOC_LITERAL(4, 48, 5), // "color"
QT_MOC_LITERAL(5, 54, 20), // "lightingColorChanged"
QT_MOC_LITERAL(6, 75, 9), // "newColors"
QT_MOC_LITERAL(7, 85, 15), // "QVector<QColor>"
QT_MOC_LITERAL(8, 101, 6) // "colors"

    },
    "CirclePalette\0selectedColorsChanged\0"
    "\0hoverColor\0color\0lightingColorChanged\0"
    "newColors\0QVector<QColor>\0colors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CirclePalette[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,
       5,    1,   38,    2, 0x06 /* Public */,
       6,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    4,
    QMetaType::Void, QMetaType::QColor,    4,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void CirclePalette::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CirclePalette *_t = static_cast<CirclePalette *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectedColorsChanged(); break;
        case 1: _t->hoverColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 2: _t->lightingColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 3: _t->newColors((*reinterpret_cast< QVector<QColor>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QColor> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CirclePalette::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CirclePalette::selectedColorsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CirclePalette::*)(const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CirclePalette::hoverColor)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CirclePalette::*)(const QColor & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CirclePalette::lightingColorChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CirclePalette::*)(QVector<QColor> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CirclePalette::newColors)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CirclePalette::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CirclePalette.data,
      qt_meta_data_CirclePalette,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CirclePalette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CirclePalette::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CirclePalette.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CirclePalette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CirclePalette::selectedColorsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CirclePalette::hoverColor(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CirclePalette::lightingColorChanged(const QColor & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CirclePalette::newColors(QVector<QColor> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_ColorSchemeWidget_t {
    QByteArrayData data[18];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ColorSchemeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ColorSchemeWidget_t qt_meta_stringdata_ColorSchemeWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ColorSchemeWidget"
QT_MOC_LITERAL(1, 18, 12), // "sendColorMap"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "ColorsMap"
QT_MOC_LITERAL(4, 42, 8), // "colorMap"
QT_MOC_LITERAL(5, 51, 13), // "schemeChanged"
QT_MOC_LITERAL(6, 65, 10), // "nameScheme"
QT_MOC_LITERAL(7, 76, 13), // "newNameScheme"
QT_MOC_LITERAL(8, 90, 15), // "QVector<QColor>"
QT_MOC_LITERAL(9, 106, 6), // "colors"
QT_MOC_LITERAL(10, 113, 12), // "QVector<int>"
QT_MOC_LITERAL(11, 126, 6), // "ranges"
QT_MOC_LITERAL(12, 133, 13), // "schemeDeleted"
QT_MOC_LITERAL(13, 147, 17), // "setNumberOfPoints"
QT_MOC_LITERAL(14, 165, 12), // "acceptColors"
QT_MOC_LITERAL(15, 178, 12), // "insertScheme"
QT_MOC_LITERAL(16, 191, 12), // "deleteScheme"
QT_MOC_LITERAL(17, 204, 20) // "currentSchemeChanged"

    },
    "ColorSchemeWidget\0sendColorMap\0\0"
    "ColorsMap\0colorMap\0schemeChanged\0"
    "nameScheme\0newNameScheme\0QVector<QColor>\0"
    "colors\0QVector<int>\0ranges\0schemeDeleted\0"
    "setNumberOfPoints\0acceptColors\0"
    "insertScheme\0deleteScheme\0"
    "currentSchemeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ColorSchemeWidget[] = {

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
       5,    4,   57,    2, 0x06 /* Public */,
      12,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   69,    2, 0x0a /* Public */,
      14,    0,   70,    2, 0x0a /* Public */,
      15,    0,   71,    2, 0x08 /* Private */,
      16,    0,   72,    2, 0x08 /* Private */,
      17,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 8, 0x80000000 | 10,    6,    7,    9,   11,
    QMetaType::Void, QMetaType::QString,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ColorSchemeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ColorSchemeWidget *_t = static_cast<ColorSchemeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendColorMap((*reinterpret_cast< ColorsMap(*)>(_a[1]))); break;
        case 1: _t->schemeChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QVector<QColor>(*)>(_a[3])),(*reinterpret_cast< QVector<int>(*)>(_a[4]))); break;
        case 2: _t->schemeDeleted((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setNumberOfPoints(); break;
        case 4: _t->acceptColors(); break;
        case 5: _t->insertScheme(); break;
        case 6: _t->deleteScheme(); break;
        case 7: _t->currentSchemeChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QColor> >(); break;
            case 3:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ColorSchemeWidget::*)(ColorsMap );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorSchemeWidget::sendColorMap)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ColorSchemeWidget::*)(QString , QString , QVector<QColor> , QVector<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorSchemeWidget::schemeChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ColorSchemeWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorSchemeWidget::schemeDeleted)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ColorSchemeWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_ColorSchemeWidget.data,
      qt_meta_data_ColorSchemeWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ColorSchemeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColorSchemeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ColorSchemeWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int ColorSchemeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ColorSchemeWidget::sendColorMap(ColorsMap _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ColorSchemeWidget::schemeChanged(QString _t1, QString _t2, QVector<QColor> _t3, QVector<int> _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ColorSchemeWidget::schemeDeleted(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
