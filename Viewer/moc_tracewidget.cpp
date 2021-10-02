/****************************************************************************
** Meta object code from reading C++ file 'tracewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Widgets/Trace/tracewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tracewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ComboBoxItemDelegate_t {
    QByteArrayData data[5];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ComboBoxItemDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ComboBoxItemDelegate_t qt_meta_stringdata_ComboBoxItemDelegate = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ComboBoxItemDelegate"
QT_MOC_LITERAL(1, 21, 12), // "cbCommitData"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "index"
QT_MOC_LITERAL(4, 41, 11) // "cbResetData"

    },
    "ComboBoxItemDelegate\0cbCommitData\0\0"
    "index\0cbResetData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ComboBoxItemDelegate[] = {

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
       4,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ComboBoxItemDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ComboBoxItemDelegate *_t = static_cast<ComboBoxItemDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cbCommitData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->cbResetData((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ComboBoxItemDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_ComboBoxItemDelegate.data,
      qt_meta_data_ComboBoxItemDelegate,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ComboBoxItemDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ComboBoxItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ComboBoxItemDelegate.stringdata0))
        return static_cast<void*>(this);
    return QStyledItemDelegate::qt_metacast(_clname);
}

int ComboBoxItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_TrackWidget_t {
    QByteArrayData data[42];
    char stringdata0[573];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrackWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrackWidget_t qt_meta_stringdata_TrackWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TrackWidget"
QT_MOC_LITERAL(1, 12, 18), // "activatedTableItem"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 2), // "id"
QT_MOC_LITERAL(4, 35, 16), // "ActionsWithTrack"
QT_MOC_LITERAL(5, 52, 6), // "action"
QT_MOC_LITERAL(6, 59, 12), // "addParameter"
QT_MOC_LITERAL(7, 72, 8), // "msgToVOI"
QT_MOC_LITERAL(8, 81, 3), // "msg"
QT_MOC_LITERAL(9, 85, 18), // "activeTrackDrawing"
QT_MOC_LITERAL(10, 104, 9), // "isDrawing"
QT_MOC_LITERAL(11, 114, 20), // "isDSPAvailableSignal"
QT_MOC_LITERAL(12, 135, 9), // "insertDSP"
QT_MOC_LITERAL(13, 145, 7), // "trackID"
QT_MOC_LITERAL(14, 153, 7), // "DSPType"
QT_MOC_LITERAL(15, 161, 4), // "type"
QT_MOC_LITERAL(16, 166, 10), // "isPlotting"
QT_MOC_LITERAL(17, 177, 8), // "newTrack"
QT_MOC_LITERAL(18, 186, 10), // "eraseTrack"
QT_MOC_LITERAL(19, 197, 12), // "addTraceMark"
QT_MOC_LITERAL(20, 210, 14), // "RLSOaimMessage"
QT_MOC_LITERAL(21, 225, 13), // "eraseOldTrace"
QT_MOC_LITERAL(22, 239, 7), // "idTrace"
QT_MOC_LITERAL(23, 247, 27), // "interactiveActionsWithTrack"
QT_MOC_LITERAL(24, 275, 24), // "isDSPExceedingUsageLimit"
QT_MOC_LITERAL(25, 300, 23), // "resolutionToSwitchingOn"
QT_MOC_LITERAL(26, 324, 22), // "resolutionToPlottingOn"
QT_MOC_LITERAL(27, 347, 13), // "changeDSPSlot"
QT_MOC_LITERAL(28, 361, 10), // "cleanModel"
QT_MOC_LITERAL(29, 372, 18), // "dataInModelChanged"
QT_MOC_LITERAL(30, 391, 14), // "QStandardItem*"
QT_MOC_LITERAL(31, 406, 4), // "item"
QT_MOC_LITERAL(32, 411, 19), // "listViewItemClicked"
QT_MOC_LITERAL(33, 431, 11), // "QModelIndex"
QT_MOC_LITERAL(34, 443, 5), // "index"
QT_MOC_LITERAL(35, 449, 18), // "currentModeChanged"
QT_MOC_LITERAL(36, 468, 17), // "currentDSPChanged"
QT_MOC_LITERAL(37, 486, 29), // "specialSectorSettingSwitching"
QT_MOC_LITERAL(38, 516, 5), // "state"
QT_MOC_LITERAL(39, 522, 12), // "acceptEffect"
QT_MOC_LITERAL(40, 535, 11), // "clearEffect"
QT_MOC_LITERAL(41, 547, 25) // "specialSectorGlobalAccept"

    },
    "TrackWidget\0activatedTableItem\0\0id\0"
    "ActionsWithTrack\0action\0addParameter\0"
    "msgToVOI\0msg\0activeTrackDrawing\0"
    "isDrawing\0isDSPAvailableSignal\0insertDSP\0"
    "trackID\0DSPType\0type\0isPlotting\0"
    "newTrack\0eraseTrack\0addTraceMark\0"
    "RLSOaimMessage\0eraseOldTrace\0idTrace\0"
    "interactiveActionsWithTrack\0"
    "isDSPExceedingUsageLimit\0"
    "resolutionToSwitchingOn\0resolutionToPlottingOn\0"
    "changeDSPSlot\0cleanModel\0dataInModelChanged\0"
    "QStandardItem*\0item\0listViewItemClicked\0"
    "QModelIndex\0index\0currentModeChanged\0"
    "currentDSPChanged\0specialSectorSettingSwitching\0"
    "state\0acceptEffect\0clearEffect\0"
    "specialSectorGlobalAccept"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrackWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  119,    2, 0x06 /* Public */,
       7,    1,  126,    2, 0x06 /* Public */,
       9,    2,  129,    2, 0x06 /* Public */,
      11,    0,  134,    2, 0x06 /* Public */,
      12,    3,  135,    2, 0x06 /* Public */,
      17,    1,  142,    2, 0x06 /* Public */,
      18,    1,  145,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,  148,    2, 0x0a /* Public */,
      21,    1,  151,    2, 0x0a /* Public */,
      23,    2,  154,    2, 0x0a /* Public */,
      24,    2,  159,    2, 0x0a /* Public */,
      27,    3,  164,    2, 0x0a /* Public */,
      28,    0,  171,    2, 0x0a /* Public */,
      29,    1,  172,    2, 0x08 /* Private */,
      32,    1,  175,    2, 0x08 /* Private */,
      35,    1,  178,    2, 0x08 /* Private */,
      36,    1,  181,    2, 0x08 /* Private */,
      37,    1,  184,    2, 0x08 /* Private */,
      39,    0,  187,    2, 0x08 /* Private */,
      40,    0,  188,    2, 0x08 /* Private */,
      41,    0,  189,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 4, QMetaType::UInt,    3,    5,    6,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, QMetaType::UInt, QMetaType::Bool,    3,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, QMetaType::Bool,   13,   15,   16,
    QMetaType::Void, QMetaType::UInt,   13,
    QMetaType::Void, QMetaType::UInt,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,    8,
    QMetaType::Void, QMetaType::UInt,   22,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   25,   26,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, QMetaType::Bool,   13,   15,   16,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 33,   34,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TrackWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrackWidget *_t = static_cast<TrackWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activatedTableItem((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< ActionsWithTrack(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 1: _t->msgToVOI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->activeTrackDrawing((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->isDSPAvailableSignal(); break;
        case 4: _t->insertDSP((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 5: _t->newTrack((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 6: _t->eraseTrack((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 7: _t->addTraceMark((*reinterpret_cast< RLSOaimMessage(*)>(_a[1]))); break;
        case 8: _t->eraseOldTrace((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 9: _t->interactiveActionsWithTrack((*reinterpret_cast< quint32(*)>(_a[1])),(*reinterpret_cast< ActionsWithTrack(*)>(_a[2]))); break;
        case 10: _t->isDSPExceedingUsageLimit((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 11: _t->changeDSPSlot((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 12: _t->cleanModel(); break;
        case 13: _t->dataInModelChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 14: _t->listViewItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 15: _t->currentModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->currentDSPChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->specialSectorSettingSwitching((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->acceptEffect(); break;
        case 19: _t->clearEffect(); break;
        case 20: _t->specialSectorGlobalAccept(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrackWidget::*)(quint32 , ActionsWithTrack , quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::activatedTableItem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrackWidget::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::msgToVOI)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrackWidget::*)(quint32 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::activeTrackDrawing)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrackWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::isDSPAvailableSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TrackWidget::*)(qint32 , DSPType , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::insertDSP)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TrackWidget::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::newTrack)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TrackWidget::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackWidget::eraseTrack)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrackWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_TrackWidget.data,
      qt_meta_data_TrackWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TrackWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrackWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrackWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int TrackWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void TrackWidget::activatedTableItem(quint32 _t1, ActionsWithTrack _t2, quint32 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrackWidget::msgToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrackWidget::activeTrackDrawing(quint32 _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrackWidget::isDSPAvailableSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TrackWidget::insertDSP(qint32 _t1, DSPType _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TrackWidget::newTrack(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TrackWidget::eraseTrack(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
