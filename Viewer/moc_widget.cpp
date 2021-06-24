/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[15];
    char stringdata0[169];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 19), // "openSectorAddWidget"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "point"
QT_MOC_LITERAL(4, 34, 10), // "KTASampled"
QT_MOC_LITERAL(5, 45, 24), // "activatedActionWithTrack"
QT_MOC_LITERAL(6, 70, 2), // "id"
QT_MOC_LITERAL(7, 73, 16), // "ActionsWithTrack"
QT_MOC_LITERAL(8, 90, 6), // "action"
QT_MOC_LITERAL(9, 97, 12), // "resizeMainGL"
QT_MOC_LITERAL(10, 110, 4), // "size"
QT_MOC_LITERAL(11, 115, 9), // "renderNow"
QT_MOC_LITERAL(12, 125, 8), // "resizeGL"
QT_MOC_LITERAL(13, 134, 15), // "forceKeyRelease"
QT_MOC_LITERAL(14, 150, 18) // "addSectorTriggered"

    },
    "Widget\0openSectorAddWidget\0\0point\0"
    "KTASampled\0activatedActionWithTrack\0"
    "id\0ActionsWithTrack\0action\0resizeMainGL\0"
    "size\0renderNow\0resizeGL\0forceKeyRelease\0"
    "addSectorTriggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

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
       4,    0,   57,    2, 0x06 /* Public */,
       5,    2,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   63,    2, 0x0a /* Public */,
      11,    0,   66,    2, 0x09 /* Protected */,
      12,    0,   67,    2, 0x09 /* Protected */,
      13,    0,   68,    2, 0x09 /* Protected */,
      14,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 7,    6,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QSize,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openSectorAddWidget((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->KTASampled(); break;
        case 2: _t->activatedActionWithTrack((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< ActionsWithTrack(*)>(_a[2]))); break;
        case 3: _t->resizeMainGL((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 4: _t->renderNow(); break;
        case 5: _t->resizeGL(); break;
        case 6: _t->forceKeyRelease(); break;
        case 7: _t->addSectorTriggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Widget::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::openSectorAddWidget)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Widget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::KTASampled)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Widget::*)(quint32 , ActionsWithTrack );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Widget::activatedActionWithTrack)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = {
    { &QWindow::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWindow::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWindow::qt_metacall(_c, _id, _a);
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
void Widget::openSectorAddWidget(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Widget::KTASampled()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Widget::activatedActionWithTrack(quint32 _t1, ActionsWithTrack _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
