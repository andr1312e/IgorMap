/****************************************************************************
** Meta object code from reading C++ file 'ktainfowindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ktainfowindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ktainfowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KTAInfoWidget_t {
    QByteArrayData data[29];
    char stringdata0[396];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KTAInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KTAInfoWidget_t qt_meta_stringdata_KTAInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "KTAInfoWidget"
QT_MOC_LITERAL(1, 14, 16), // "selectKTARequest"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 16), // "indexOnKTAVector"
QT_MOC_LITERAL(4, 49, 25), // "sampledKTAMarkVertexArray"
QT_MOC_LITERAL(5, 75, 12), // "const float*"
QT_MOC_LITERAL(6, 88, 5), // "array"
QT_MOC_LITERAL(7, 94, 4), // "size"
QT_MOC_LITERAL(8, 99, 24), // "drawSampledKTAMarkSignal"
QT_MOC_LITERAL(9, 124, 31), // "QSharedPointer<QVector<float> >"
QT_MOC_LITERAL(10, 156, 11), // "sharedArray"
QT_MOC_LITERAL(11, 168, 9), // "fillTable"
QT_MOC_LITERAL(12, 178, 17), // "KTAMarksForTable*"
QT_MOC_LITERAL(13, 196, 4), // "list"
QT_MOC_LITERAL(14, 201, 29), // "selectKTARequestAnswerHandler"
QT_MOC_LITERAL(15, 231, 18), // "WeakPointerKTAMark"
QT_MOC_LITERAL(16, 250, 13), // "selectedIndex"
QT_MOC_LITERAL(17, 264, 10), // "addKtaMark"
QT_MOC_LITERAL(18, 275, 15), // "RLSOPlotMessage"
QT_MOC_LITERAL(19, 291, 3), // "msg"
QT_MOC_LITERAL(20, 295, 5), // "isPOI"
QT_MOC_LITERAL(21, 301, 11), // "addKtaMark2"
QT_MOC_LITERAL(22, 313, 13), // "POIKtaMessage"
QT_MOC_LITERAL(23, 327, 14), // "sampledKTAMark"
QT_MOC_LITERAL(24, 342, 10), // "leftBottom"
QT_MOC_LITERAL(25, 353, 8), // "rightTop"
QT_MOC_LITERAL(26, 362, 11), // "eraseOldKTA"
QT_MOC_LITERAL(27, 374, 9), // "showTable"
QT_MOC_LITERAL(28, 384, 11) // "rowSelected"

    },
    "KTAInfoWidget\0selectKTARequest\0\0"
    "indexOnKTAVector\0sampledKTAMarkVertexArray\0"
    "const float*\0array\0size\0"
    "drawSampledKTAMarkSignal\0"
    "QSharedPointer<QVector<float> >\0"
    "sharedArray\0fillTable\0KTAMarksForTable*\0"
    "list\0selectKTARequestAnswerHandler\0"
    "WeakPointerKTAMark\0selectedIndex\0"
    "addKtaMark\0RLSOPlotMessage\0msg\0isPOI\0"
    "addKtaMark2\0POIKtaMessage\0sampledKTAMark\0"
    "leftBottom\0rightTop\0eraseOldKTA\0"
    "showTable\0rowSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KTAInfoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       8,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   80,    2, 0x0a /* Public */,
      14,    1,   83,    2, 0x0a /* Public */,
      17,    2,   86,    2, 0x0a /* Public */,
      21,    1,   91,    2, 0x0a /* Public */,
      23,    2,   94,    2, 0x0a /* Public */,
      26,    0,   99,    2, 0x08 /* Private */,
      27,    0,  100,    2, 0x08 /* Private */,
      28,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::UInt,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Bool,   19,   20,
    QMetaType::Void, 0x80000000 | 22,   19,
    QMetaType::Void, QMetaType::QPointF, QMetaType::QPointF,   24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KTAInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KTAInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectKTARequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sampledKTAMarkVertexArray((*reinterpret_cast< const float*(*)>(_a[1])),(*reinterpret_cast< const quint32(*)>(_a[2]))); break;
        case 2: _t->drawSampledKTAMarkSignal((*reinterpret_cast< QSharedPointer<QVector<float> >(*)>(_a[1]))); break;
        case 3: _t->fillTable((*reinterpret_cast< KTAMarksForTable*(*)>(_a[1]))); break;
        case 4: _t->selectKTARequestAnswerHandler((*reinterpret_cast< WeakPointerKTAMark(*)>(_a[1]))); break;
        case 5: _t->addKtaMark((*reinterpret_cast< RLSOPlotMessage(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->addKtaMark2((*reinterpret_cast< POIKtaMessage(*)>(_a[1]))); break;
        case 7: _t->sampledKTAMark((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 8: _t->eraseOldKTA(); break;
        case 9: _t->showTable(); break;
        case 10: _t->rowSelected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KTAInfoWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KTAInfoWidget::selectKTARequest)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KTAInfoWidget::*)(const float * , const quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KTAInfoWidget::sampledKTAMarkVertexArray)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (KTAInfoWidget::*)(QSharedPointer<QVector<float> > );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&KTAInfoWidget::drawSampledKTAMarkSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject KTAInfoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_KTAInfoWidget.data,
    qt_meta_data_KTAInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *KTAInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KTAInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KTAInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int KTAInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
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
void KTAInfoWidget::selectKTARequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KTAInfoWidget::sampledKTAMarkVertexArray(const float * _t1, const quint32 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void KTAInfoWidget::drawSampledKTAMarkSignal(QSharedPointer<QVector<float> > _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
