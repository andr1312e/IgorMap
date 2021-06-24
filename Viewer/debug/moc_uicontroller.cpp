/****************************************************************************
** Meta object code from reading C++ file 'uicontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../uicontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uicontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UIController_t {
    QByteArrayData data[23];
    char stringdata0[237];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UIController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UIController_t qt_meta_stringdata_UIController = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UIController"
QT_MOC_LITERAL(1, 13, 12), // "openCloseQML"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "changeProjection"
QT_MOC_LITERAL(4, 44, 11), // "windowState"
QT_MOC_LITERAL(5, 56, 11), // "WidgetTypes"
QT_MOC_LITERAL(6, 68, 4), // "type"
QT_MOC_LITERAL(7, 73, 4), // "open"
QT_MOC_LITERAL(8, 78, 7), // "addMark"
QT_MOC_LITERAL(9, 86, 15), // "RLSOPlotMessage"
QT_MOC_LITERAL(10, 102, 3), // "msg"
QT_MOC_LITERAL(11, 106, 5), // "isPOI"
QT_MOC_LITERAL(12, 112, 9), // "addRaySet"
QT_MOC_LITERAL(13, 122, 6), // "RaySet"
QT_MOC_LITERAL(14, 129, 6), // "raySet"
QT_MOC_LITERAL(15, 136, 8), // "addTrace"
QT_MOC_LITERAL(16, 145, 14), // "RLSOaimMessage"
QT_MOC_LITERAL(17, 160, 10), // "testKTAMsg"
QT_MOC_LITERAL(18, 171, 12), // "testTraceMsg"
QT_MOC_LITERAL(19, 184, 13), // "testTraceMsg2"
QT_MOC_LITERAL(20, 198, 13), // "testTraceMsg3"
QT_MOC_LITERAL(21, 212, 13), // "testTraceMsg4"
QT_MOC_LITERAL(22, 226, 10) // "testRayMsg"

    },
    "UIController\0openCloseQML\0\0changeProjection\0"
    "windowState\0WidgetTypes\0type\0open\0"
    "addMark\0RLSOPlotMessage\0msg\0isPOI\0"
    "addRaySet\0RaySet\0raySet\0addTrace\0"
    "RLSOaimMessage\0testKTAMsg\0testTraceMsg\0"
    "testTraceMsg2\0testTraceMsg3\0testTraceMsg4\0"
    "testRayMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UIController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,
       4,    2,   80,    2, 0x06 /* Public */,
       8,    2,   85,    2, 0x06 /* Public */,
      12,    1,   90,    2, 0x06 /* Public */,
      15,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,   96,    2, 0x08 /* Private */,
      18,    0,   97,    2, 0x08 /* Private */,
      19,    0,   98,    2, 0x08 /* Private */,
      20,    0,   99,    2, 0x08 /* Private */,
      21,    0,  100,    2, 0x08 /* Private */,
      22,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Bool,    6,    7,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Bool,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UIController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UIController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openCloseQML((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeProjection((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->windowState((*reinterpret_cast< WidgetTypes(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->addMark((*reinterpret_cast< RLSOPlotMessage(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->addRaySet((*reinterpret_cast< RaySet(*)>(_a[1]))); break;
        case 5: _t->addTrace((*reinterpret_cast< RLSOaimMessage(*)>(_a[1]))); break;
        case 6: _t->testKTAMsg(); break;
        case 7: _t->testTraceMsg(); break;
        case 8: _t->testTraceMsg2(); break;
        case 9: _t->testTraceMsg3(); break;
        case 10: _t->testTraceMsg4(); break;
        case 11: _t->testRayMsg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RLSOPlotMessage >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RaySet >(); break;
            }
            break;
        case 5:
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
            using _t = void (UIController::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UIController::openCloseQML)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UIController::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UIController::changeProjection)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UIController::*)(WidgetTypes , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UIController::windowState)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UIController::*)(RLSOPlotMessage , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UIController::addMark)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UIController::*)(RaySet );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UIController::addRaySet)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UIController::*)(RLSOaimMessage );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UIController::addTrace)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UIController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_UIController.data,
    qt_meta_data_UIController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UIController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UIController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UIController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UIController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void UIController::openCloseQML(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UIController::changeProjection(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UIController::windowState(WidgetTypes _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UIController::addMark(RLSOPlotMessage _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void UIController::addRaySet(RaySet _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void UIController::addTrace(RLSOaimMessage _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
