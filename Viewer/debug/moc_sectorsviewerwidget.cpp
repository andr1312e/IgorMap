/****************************************************************************
** Meta object code from reading C++ file 'sectorsviewerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../sectorsviewerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sectorsviewerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MessageBoxWindowManager_t {
    QByteArrayData data[9];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MessageBoxWindowManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MessageBoxWindowManager_t qt_meta_stringdata_MessageBoxWindowManager = {
    {
QT_MOC_LITERAL(0, 0, 23), // "MessageBoxWindowManager"
QT_MOC_LITERAL(1, 24, 10), // "userAnswer"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 2), // "id"
QT_MOC_LITERAL(4, 39, 23), // "QMessageBox::ButtonRole"
QT_MOC_LITERAL(5, 63, 4), // "role"
QT_MOC_LITERAL(6, 68, 21), // "messageBoxButtonClick"
QT_MOC_LITERAL(7, 90, 16), // "QAbstractButton*"
QT_MOC_LITERAL(8, 107, 6) // "button"

    },
    "MessageBoxWindowManager\0userAnswer\0\0"
    "id\0QMessageBox::ButtonRole\0role\0"
    "messageBoxButtonClick\0QAbstractButton*\0"
    "button"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MessageBoxWindowManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   29,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void MessageBoxWindowManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MessageBoxWindowManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->userAnswer((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QMessageBox::ButtonRole(*)>(_a[2]))); break;
        case 1: _t->messageBoxButtonClick((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MessageBoxWindowManager::*)(quint8 , QMessageBox::ButtonRole );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageBoxWindowManager::userAnswer)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MessageBoxWindowManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MessageBoxWindowManager.data,
    qt_meta_data_MessageBoxWindowManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MessageBoxWindowManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MessageBoxWindowManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MessageBoxWindowManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MessageBoxWindowManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MessageBoxWindowManager::userAnswer(quint8 _t1, QMessageBox::ButtonRole _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SectorRemover_t {
    QByteArrayData data[17];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SectorRemover_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SectorRemover_t qt_meta_stringdata_SectorRemover = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SectorRemover"
QT_MOC_LITERAL(1, 14, 14), // "sectorBlinking"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 2), // "id"
QT_MOC_LITERAL(4, 33, 25), // "ActionsWithBlinkingSector"
QT_MOC_LITERAL(5, 59, 6), // "action"
QT_MOC_LITERAL(6, 66, 21), // "deleteSectorByTimeout"
QT_MOC_LITERAL(7, 88, 13), // "addMessageBox"
QT_MOC_LITERAL(8, 102, 8), // "timeLeft"
QT_MOC_LITERAL(9, 111, 16), // "updateMessageBox"
QT_MOC_LITERAL(10, 128, 15), // "closeMessageBox"
QT_MOC_LITERAL(11, 144, 21), // "restartSectorBlinking"
QT_MOC_LITERAL(12, 166, 17), // "userAnswerHandler"
QT_MOC_LITERAL(13, 184, 23), // "QMessageBox::ButtonRole"
QT_MOC_LITERAL(14, 208, 4), // "role"
QT_MOC_LITERAL(15, 213, 15), // "timeoutDropping"
QT_MOC_LITERAL(16, 229, 15) // "timeoutBlinking"

    },
    "SectorRemover\0sectorBlinking\0\0id\0"
    "ActionsWithBlinkingSector\0action\0"
    "deleteSectorByTimeout\0addMessageBox\0"
    "timeLeft\0updateMessageBox\0closeMessageBox\0"
    "restartSectorBlinking\0userAnswerHandler\0"
    "QMessageBox::ButtonRole\0role\0"
    "timeoutDropping\0timeoutBlinking"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorRemover[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       6,    1,   64,    2, 0x06 /* Public */,
       7,    2,   67,    2, 0x06 /* Public */,
       9,    2,   72,    2, 0x06 /* Public */,
      10,    1,   77,    2, 0x06 /* Public */,
      11,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   83,    2, 0x0a /* Public */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    3,    8,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    3,    8,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 13,    3,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SectorRemover::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SectorRemover *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sectorBlinking((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< ActionsWithBlinkingSector(*)>(_a[2]))); break;
        case 1: _t->deleteSectorByTimeout((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 2: _t->addMessageBox((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 3: _t->updateMessageBox((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 4: _t->closeMessageBox((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 5: _t->restartSectorBlinking((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 6: _t->userAnswerHandler((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< QMessageBox::ButtonRole(*)>(_a[2]))); break;
        case 7: _t->timeoutDropping(); break;
        case 8: _t->timeoutBlinking(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SectorRemover::*)(quint8 , ActionsWithBlinkingSector );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorRemover::sectorBlinking)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SectorRemover::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorRemover::deleteSectorByTimeout)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SectorRemover::*)(quint8 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorRemover::addMessageBox)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SectorRemover::*)(quint8 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorRemover::updateMessageBox)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SectorRemover::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorRemover::closeMessageBox)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SectorRemover::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorRemover::restartSectorBlinking)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SectorRemover::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_SectorRemover.data,
    qt_meta_data_SectorRemover,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SectorRemover::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SectorRemover::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SectorRemover.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SectorRemover::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SectorRemover::sectorBlinking(quint8 _t1, ActionsWithBlinkingSector _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SectorRemover::deleteSectorByTimeout(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SectorRemover::addMessageBox(quint8 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SectorRemover::updateMessageBox(quint8 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SectorRemover::closeMessageBox(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SectorRemover::restartSectorBlinking(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_SectorsViewerWidget_t {
    QByteArrayData data[38];
    char stringdata0[540];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SectorsViewerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SectorsViewerWidget_t qt_meta_stringdata_SectorsViewerWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "SectorsViewerWidget"
QT_MOC_LITERAL(1, 20, 12), // "presetSector"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 22), // "SharedSectorParameters"
QT_MOC_LITERAL(5, 63, 12), // "sharedSector"
QT_MOC_LITERAL(6, 76, 9), // "newSector"
QT_MOC_LITERAL(7, 86, 13), // "excludeSector"
QT_MOC_LITERAL(8, 100, 12), // "deleteSector"
QT_MOC_LITERAL(9, 113, 15), // "addSectorsToVOI"
QT_MOC_LITERAL(10, 129, 3), // "msg"
QT_MOC_LITERAL(11, 133, 17), // "deleteSectorToVOI"
QT_MOC_LITERAL(12, 151, 16), // "setSectorInFocus"
QT_MOC_LITERAL(13, 168, 17), // "setSectorOutFocus"
QT_MOC_LITERAL(14, 186, 14), // "openMainWidget"
QT_MOC_LITERAL(15, 201, 23), // "repeaterNewSectorSignal"
QT_MOC_LITERAL(16, 225, 27), // "openWidgetWithCurrentParams"
QT_MOC_LITERAL(17, 253, 5), // "point"
QT_MOC_LITERAL(18, 259, 16), // "targetingAddSlot"
QT_MOC_LITERAL(19, 276, 7), // "isQuick"
QT_MOC_LITERAL(20, 284, 20), // "targetingExcludeSlot"
QT_MOC_LITERAL(21, 305, 25), // "deleteSectorByTimeoutSlot"
QT_MOC_LITERAL(22, 331, 2), // "id"
QT_MOC_LITERAL(23, 334, 21), // "restartSectorBlinking"
QT_MOC_LITERAL(24, 356, 12), // "acceptEffect"
QT_MOC_LITERAL(25, 369, 11), // "clearEffect"
QT_MOC_LITERAL(26, 381, 12), // "changeLayout"
QT_MOC_LITERAL(27, 394, 6), // "addRow"
QT_MOC_LITERAL(28, 401, 6), // "delRow"
QT_MOC_LITERAL(29, 408, 17), // "itemChangeInTable"
QT_MOC_LITERAL(30, 426, 14), // "QStandardItem*"
QT_MOC_LITERAL(31, 441, 4), // "item"
QT_MOC_LITERAL(32, 446, 19), // "listViewItemClicked"
QT_MOC_LITERAL(33, 466, 11), // "QModelIndex"
QT_MOC_LITERAL(34, 478, 19), // "fillParametersFeild"
QT_MOC_LITERAL(35, 498, 18), // "SectorsPrivateInfo"
QT_MOC_LITERAL(36, 517, 4), // "info"
QT_MOC_LITERAL(37, 522, 17) // "autoButtonClicked"

    },
    "SectorsViewerWidget\0presetSector\0\0"
    "index\0SharedSectorParameters\0sharedSector\0"
    "newSector\0excludeSector\0deleteSector\0"
    "addSectorsToVOI\0msg\0deleteSectorToVOI\0"
    "setSectorInFocus\0setSectorOutFocus\0"
    "openMainWidget\0repeaterNewSectorSignal\0"
    "openWidgetWithCurrentParams\0point\0"
    "targetingAddSlot\0isQuick\0targetingExcludeSlot\0"
    "deleteSectorByTimeoutSlot\0id\0"
    "restartSectorBlinking\0acceptEffect\0"
    "clearEffect\0changeLayout\0addRow\0delRow\0"
    "itemChangeInTable\0QStandardItem*\0item\0"
    "listViewItemClicked\0QModelIndex\0"
    "fillParametersFeild\0SectorsPrivateInfo\0"
    "info\0autoButtonClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorsViewerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  134,    2, 0x06 /* Public */,
       6,    2,  139,    2, 0x06 /* Public */,
       7,    1,  144,    2, 0x06 /* Public */,
       8,    1,  147,    2, 0x06 /* Public */,
       9,    1,  150,    2, 0x06 /* Public */,
      11,    1,  153,    2, 0x06 /* Public */,
      12,    1,  156,    2, 0x06 /* Public */,
      13,    0,  159,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  160,    2, 0x0a /* Public */,
      15,    1,  161,    2, 0x0a /* Public */,
      16,    1,  164,    2, 0x0a /* Public */,
      18,    2,  167,    2, 0x0a /* Public */,
      20,    1,  172,    2, 0x0a /* Public */,
      21,    1,  175,    2, 0x0a /* Public */,
      23,    1,  178,    2, 0x0a /* Public */,
      24,    0,  181,    2, 0x08 /* Private */,
      25,    0,  182,    2, 0x08 /* Private */,
      26,    0,  183,    2, 0x08 /* Private */,
      27,    0,  184,    2, 0x08 /* Private */,
      28,    0,  185,    2, 0x08 /* Private */,
      29,    1,  186,    2, 0x08 /* Private */,
      32,    1,  189,    2, 0x08 /* Private */,
      34,    1,  192,    2, 0x08 /* Private */,
      37,    0,  195,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QPointF,   17,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   17,   19,
    QMetaType::Void, QMetaType::QPointF,   17,
    QMetaType::Void, QMetaType::UChar,   22,
    QMetaType::Void, QMetaType::UChar,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 33,    3,
    QMetaType::Void, 0x80000000 | 35,   36,
    QMetaType::Void,

       0        // eod
};

void SectorsViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SectorsViewerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->presetSector((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< SharedSectorParameters(*)>(_a[2]))); break;
        case 1: _t->newSector((*reinterpret_cast< const quint8(*)>(_a[1])),(*reinterpret_cast< SharedSectorParameters(*)>(_a[2]))); break;
        case 2: _t->excludeSector((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 3: _t->deleteSector((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 4: _t->addSectorsToVOI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 5: _t->deleteSectorToVOI((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->setSectorInFocus((*reinterpret_cast< const quint8(*)>(_a[1]))); break;
        case 7: _t->setSectorOutFocus(); break;
        case 8: _t->openMainWidget(); break;
        case 9: _t->repeaterNewSectorSignal((*reinterpret_cast< SharedSectorParameters(*)>(_a[1]))); break;
        case 10: _t->openWidgetWithCurrentParams((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 11: _t->targetingAddSlot((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->targetingExcludeSlot((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 13: _t->deleteSectorByTimeoutSlot((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 14: _t->restartSectorBlinking((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 15: _t->acceptEffect(); break;
        case 16: _t->clearEffect(); break;
        case 17: _t->changeLayout(); break;
        case 18: _t->addRow(); break;
        case 19: _t->delRow(); break;
        case 20: _t->itemChangeInTable((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 21: _t->listViewItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 22: _t->fillParametersFeild((*reinterpret_cast< const SectorsPrivateInfo(*)>(_a[1]))); break;
        case 23: _t->autoButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SectorsViewerWidget::*)(const quint8 , SharedSectorParameters );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::presetSector)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(const quint8 , SharedSectorParameters );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::newSector)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(const quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::excludeSector)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(const quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::deleteSector)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::addSectorsToVOI)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::deleteSectorToVOI)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(const quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::setSectorInFocus)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::setSectorOutFocus)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SectorsViewerWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWidget::staticMetaObject>(),
    qt_meta_stringdata_SectorsViewerWidget.data,
    qt_meta_data_SectorsViewerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SectorsViewerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SectorsViewerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SectorsViewerWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int SectorsViewerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void SectorsViewerWidget::presetSector(const quint8 _t1, SharedSectorParameters _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SectorsViewerWidget::newSector(const quint8 _t1, SharedSectorParameters _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SectorsViewerWidget::excludeSector(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SectorsViewerWidget::deleteSector(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SectorsViewerWidget::addSectorsToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SectorsViewerWidget::deleteSectorToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SectorsViewerWidget::setSectorInFocus(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SectorsViewerWidget::setSectorOutFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
