/****************************************************************************
** Meta object code from reading C++ file 'ktamarkmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "TrackingManager/DataModel/ktamarkmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ktamarkmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KTAMarkModel_t {
    QByteArrayData data[11];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KTAMarkModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KTAMarkModel_t qt_meta_stringdata_KTAMarkModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "KTAMarkModel"
QT_MOC_LITERAL(1, 13, 20), // "returnDataToTableKTA"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "KTAMarksForTable*"
QT_MOC_LITERAL(4, 53, 4), // "list"
QT_MOC_LITERAL(5, 58, 22), // "selectKTARequestAnswer"
QT_MOC_LITERAL(6, 81, 18), // "WeakPointerKTAMark"
QT_MOC_LITERAL(7, 100, 13), // "selectedIndex"
QT_MOC_LITERAL(8, 114, 23), // "selectKTARequestHandler"
QT_MOC_LITERAL(9, 138, 16), // "indexOnKTAVector"
QT_MOC_LITERAL(10, 155, 11) // "eraseAllKTA"

    },
    "KTAMarkModel\0returnDataToTableKTA\0\0"
    "KTAMarksForTable*\0list\0selectKTARequestAnswer\0"
    "WeakPointerKTAMark\0selectedIndex\0"
    "selectKTARequestHandler\0indexOnKTAVector\0"
    "eraseAllKTA"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KTAMarkModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   40,    2, 0x0a /* Public */,
      10,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void KTAMarkModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KTAMarkModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnDataToTableKTA((*reinterpret_cast< KTAMarksForTable*(*)>(_a[1]))); break;
        case 1: _t->selectKTARequestAnswer((*reinterpret_cast< WeakPointerKTAMark(*)>(_a[1]))); break;
        case 2: _t->selectKTARequestHandler((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->eraseAllKTA(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KTAMarkModel::*)(KTAMarksForTable * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KTAMarkModel::returnDataToTableKTA)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KTAMarkModel::*)(WeakPointerKTAMark );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KTAMarkModel::selectKTARequestAnswer)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KTAMarkModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_KTAMarkModel.data,
    qt_meta_data_KTAMarkModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KTAMarkModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KTAMarkModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KTAMarkModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int KTAMarkModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void KTAMarkModel::returnDataToTableKTA(KTAMarksForTable * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KTAMarkModel::selectKTARequestAnswer(WeakPointerKTAMark _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
