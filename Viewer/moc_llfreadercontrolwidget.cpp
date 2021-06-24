/****************************************************************************
** Meta object code from reading C++ file 'llfreadercontrolwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "llfreadercontrolwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'llfreadercontrolwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LLFRSlider_t {
    QByteArrayData data[5];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LLFRSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LLFRSlider_t qt_meta_stringdata_LLFRSlider = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LLFRSlider"
QT_MOC_LITERAL(1, 11, 10), // "PosChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "sliderPressed"
QT_MOC_LITERAL(4, 37, 14) // "sliderReleased"

    },
    "LLFRSlider\0PosChanged\0\0sliderPressed\0"
    "sliderReleased"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LLFRSlider[] = {

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
       3,    0,   32,    2, 0x0a /* Public */,
       4,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LLFRSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LLFRSlider *_t = static_cast<LLFRSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->PosChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sliderPressed(); break;
        case 2: _t->sliderReleased(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LLFRSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LLFRSlider::PosChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LLFRSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_LLFRSlider.data,
      qt_meta_data_LLFRSlider,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LLFRSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LLFRSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LLFRSlider.stringdata0))
        return static_cast<void*>(this);
    return QSlider::qt_metacast(_clname);
}

int LLFRSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
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
void LLFRSlider::PosChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_LLFReaderCWButton_t {
    QByteArrayData data[1];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LLFReaderCWButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LLFReaderCWButton_t qt_meta_stringdata_LLFReaderCWButton = {
    {
QT_MOC_LITERAL(0, 0, 17) // "LLFReaderCWButton"

    },
    "LLFReaderCWButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LLFReaderCWButton[] = {

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

void LLFReaderCWButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LLFReaderCWButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_LLFReaderCWButton.data,
      qt_meta_data_LLFReaderCWButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LLFReaderCWButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LLFReaderCWButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LLFReaderCWButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int LLFReaderCWButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_LLFReaderControlWidget_t {
    QByteArrayData data[11];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LLFReaderControlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LLFReaderControlWidget_t qt_meta_stringdata_LLFReaderControlWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "LLFReaderControlWidget"
QT_MOC_LITERAL(1, 23, 9), // "selectDir"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "selectMsg"
QT_MOC_LITERAL(4, 44, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(5, 61, 4), // "item"
QT_MOC_LITERAL(6, 66, 12), // "selectAllMsg"
QT_MOC_LITERAL(7, 79, 11), // "timeChanged"
QT_MOC_LITERAL(8, 91, 5), // "pause"
QT_MOC_LITERAL(9, 97, 8), // "setSpeed"
QT_MOC_LITERAL(10, 106, 4) // "stop"

    },
    "LLFReaderControlWidget\0selectDir\0\0"
    "selectMsg\0QListWidgetItem*\0item\0"
    "selectAllMsg\0timeChanged\0pause\0setSpeed\0"
    "stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LLFReaderControlWidget[] = {

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
       1,    0,   49,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x08 /* Private */,
       9,    0,   56,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LLFReaderControlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LLFReaderControlWidget *_t = static_cast<LLFReaderControlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectDir(); break;
        case 1: _t->selectMsg((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->selectAllMsg(); break;
        case 3: _t->timeChanged(); break;
        case 4: _t->pause(); break;
        case 5: _t->setSpeed(); break;
        case 6: _t->stop(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LLFReaderControlWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_LLFReaderControlWidget.data,
      qt_meta_data_LLFReaderControlWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LLFReaderControlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LLFReaderControlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LLFReaderControlWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int LLFReaderControlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
