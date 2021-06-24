/****************************************************************************
** Meta object code from reading C++ file 'signalnoiseratiowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "signalnoiseratiowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signalnoiseratiowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SignalNoiseRatioWidget_t {
    QByteArrayData data[12];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SignalNoiseRatioWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SignalNoiseRatioWidget_t qt_meta_stringdata_SignalNoiseRatioWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "SignalNoiseRatioWidget"
QT_MOC_LITERAL(1, 23, 7), // "setData"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 16), // "QVector<QPointF>"
QT_MOC_LITERAL(4, 49, 4), // "data"
QT_MOC_LITERAL(5, 54, 4), // "isAz"
QT_MOC_LITERAL(6, 59, 13), // "pannerHandler"
QT_MOC_LITERAL(7, 73, 2), // "dx"
QT_MOC_LITERAL(8, 76, 2), // "dy"
QT_MOC_LITERAL(9, 79, 11), // "zoomHandler"
QT_MOC_LITERAL(10, 91, 4), // "rect"
QT_MOC_LITERAL(11, 96, 6) // "replot"

    },
    "SignalNoiseRatioWidget\0setData\0\0"
    "QVector<QPointF>\0data\0isAz\0pannerHandler\0"
    "dx\0dy\0zoomHandler\0rect\0replot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SignalNoiseRatioWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       6,    2,   39,    2, 0x0a /* Public */,
       9,    1,   44,    2, 0x0a /* Public */,
      11,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, QMetaType::QRectF,   10,
    QMetaType::Void,

       0        // eod
};

void SignalNoiseRatioWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SignalNoiseRatioWidget *_t = static_cast<SignalNoiseRatioWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< const QVector<QPointF>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->pannerHandler((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->zoomHandler((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 3: _t->replot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QPointF> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SignalNoiseRatioWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_SignalNoiseRatioWidget.data,
      qt_meta_data_SignalNoiseRatioWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SignalNoiseRatioWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignalNoiseRatioWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SignalNoiseRatioWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int SignalNoiseRatioWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
