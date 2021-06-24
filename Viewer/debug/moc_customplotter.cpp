/****************************************************************************
** Meta object code from reading C++ file 'customplotter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../customplotter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customplotter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SpinBoxDelegate_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpinBoxDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpinBoxDelegate_t qt_meta_stringdata_SpinBoxDelegate = {
    {
QT_MOC_LITERAL(0, 0, 15) // "SpinBoxDelegate"

    },
    "SpinBoxDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpinBoxDelegate[] = {

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

void SpinBoxDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject SpinBoxDelegate::staticMetaObject = { {
    QMetaObject::SuperData::link<QStyledItemDelegate::staticMetaObject>(),
    qt_meta_stringdata_SpinBoxDelegate.data,
    qt_meta_data_SpinBoxDelegate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SpinBoxDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpinBoxDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SpinBoxDelegate.stringdata0))
        return static_cast<void*>(this);
    return QStyledItemDelegate::qt_metacast(_clname);
}

int SpinBoxDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_CustomPlotterWidget_t {
    QByteArrayData data[14];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomPlotterWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomPlotterWidget_t qt_meta_stringdata_CustomPlotterWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CustomPlotterWidget"
QT_MOC_LITERAL(1, 20, 11), // "showContour"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 2), // "on"
QT_MOC_LITERAL(4, 36, 15), // "showSpectrogram"
QT_MOC_LITERAL(5, 52, 11), // "setColorMap"
QT_MOC_LITERAL(6, 64, 8), // "setAlpha"
QT_MOC_LITERAL(7, 73, 14), // "setAntiAlasing"
QT_MOC_LITERAL(8, 88, 14), // "updatePlotSlot"
QT_MOC_LITERAL(9, 103, 13), // "pannerHandler"
QT_MOC_LITERAL(10, 117, 2), // "dx"
QT_MOC_LITERAL(11, 120, 2), // "dy"
QT_MOC_LITERAL(12, 123, 11), // "zoomHandler"
QT_MOC_LITERAL(13, 135, 4) // "rect"

    },
    "CustomPlotterWidget\0showContour\0\0on\0"
    "showSpectrogram\0setColorMap\0setAlpha\0"
    "setAntiAlasing\0updatePlotSlot\0"
    "pannerHandler\0dx\0dy\0zoomHandler\0rect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomPlotterWidget[] = {

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
       6,    1,   63,    2, 0x0a /* Public */,
       7,    1,   66,    2, 0x0a /* Public */,
       8,    0,   69,    2, 0x0a /* Public */,
       9,    2,   70,    2, 0x0a /* Public */,
      12,    1,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QRectF,   13,

       0        // eod
};

void CustomPlotterWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomPlotterWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showContour((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->showSpectrogram((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setColorMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setAlpha((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setAntiAlasing((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updatePlotSlot(); break;
        case 6: _t->pannerHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->zoomHandler((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomPlotterWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_CustomPlotterWidget.data,
    qt_meta_data_CustomPlotterWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomPlotterWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomPlotterWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomPlotterWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int CustomPlotterWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
