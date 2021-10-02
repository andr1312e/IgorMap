/****************************************************************************
** Meta object code from reading C++ file 'sectorsviewerwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Widgets/Sectors/sectorsviewerwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sectorsviewerwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
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
       7,       // revision
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
        MessageBoxWindowManager *_t = static_cast<MessageBoxWindowManager *>(_o);
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

QT_INIT_METAOBJECT const QMetaObject MessageBoxWindowManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MessageBoxWindowManager.data,
      qt_meta_data_MessageBoxWindowManager,  qt_static_metacall, nullptr, nullptr}
};


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
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
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
       7,       // revision
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
        SectorRemover *_t = static_cast<SectorRemover *>(_o);
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

QT_INIT_METAOBJECT const QMetaObject SectorRemover::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SectorRemover.data,
      qt_meta_data_SectorRemover,  qt_static_metacall, nullptr, nullptr}
};


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
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SectorRemover::deleteSectorByTimeout(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SectorRemover::addMessageBox(quint8 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SectorRemover::updateMessageBox(quint8 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SectorRemover::closeMessageBox(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SectorRemover::restartSectorBlinking(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_SectorsViewerWidget_t {
    QByteArrayData data[62];
    char stringdata0[915];
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
QT_MOC_LITERAL(14, 186, 21), // "dspActivationOnSector"
QT_MOC_LITERAL(15, 208, 8), // "targetID"
QT_MOC_LITERAL(16, 217, 7), // "DSPType"
QT_MOC_LITERAL(17, 225, 4), // "type"
QT_MOC_LITERAL(18, 230, 10), // "isPlotting"
QT_MOC_LITERAL(19, 241, 20), // "newSectorToDSPWidget"
QT_MOC_LITERAL(20, 262, 22), // "clearSectorToDSPWidget"
QT_MOC_LITERAL(21, 285, 20), // "isDSPAvailableSignal"
QT_MOC_LITERAL(22, 306, 22), // "maxDistChangedOnSector"
QT_MOC_LITERAL(23, 329, 7), // "maxDist"
QT_MOC_LITERAL(24, 337, 17), // "clearSectorToGrid"
QT_MOC_LITERAL(25, 355, 14), // "openMainWidget"
QT_MOC_LITERAL(26, 370, 23), // "repeaterNewSectorSignal"
QT_MOC_LITERAL(27, 394, 27), // "openWidgetWithCurrentParams"
QT_MOC_LITERAL(28, 422, 5), // "point"
QT_MOC_LITERAL(29, 428, 16), // "targetingAddSlot"
QT_MOC_LITERAL(30, 445, 7), // "isQuick"
QT_MOC_LITERAL(31, 453, 20), // "targetingExcludeSlot"
QT_MOC_LITERAL(32, 474, 25), // "deleteSectorByTimeoutSlot"
QT_MOC_LITERAL(33, 500, 2), // "id"
QT_MOC_LITERAL(34, 503, 21), // "restartSectorBlinking"
QT_MOC_LITERAL(35, 525, 24), // "isDSPExceedingUsageLimit"
QT_MOC_LITERAL(36, 550, 23), // "resolutionToSwitchingOn"
QT_MOC_LITERAL(37, 574, 22), // "resolutionToPlottingOn"
QT_MOC_LITERAL(38, 597, 13), // "changeDSPSlot"
QT_MOC_LITERAL(39, 611, 7), // "trackID"
QT_MOC_LITERAL(40, 619, 11), // "azUgmUpdate"
QT_MOC_LITERAL(41, 631, 2), // "az"
QT_MOC_LITERAL(42, 634, 3), // "ugm"
QT_MOC_LITERAL(43, 638, 12), // "acceptEffect"
QT_MOC_LITERAL(44, 651, 11), // "clearEffect"
QT_MOC_LITERAL(45, 663, 12), // "changeLayout"
QT_MOC_LITERAL(46, 676, 6), // "addRow"
QT_MOC_LITERAL(47, 683, 6), // "delRow"
QT_MOC_LITERAL(48, 690, 17), // "itemChangeInTable"
QT_MOC_LITERAL(49, 708, 14), // "QStandardItem*"
QT_MOC_LITERAL(50, 723, 4), // "item"
QT_MOC_LITERAL(51, 728, 19), // "listViewItemClicked"
QT_MOC_LITERAL(52, 748, 11), // "QModelIndex"
QT_MOC_LITERAL(53, 760, 19), // "fillParametersField"
QT_MOC_LITERAL(54, 780, 18), // "SectorsPrivateInfo"
QT_MOC_LITERAL(55, 799, 4), // "info"
QT_MOC_LITERAL(56, 804, 17), // "autoButtonClicked"
QT_MOC_LITERAL(57, 822, 14), // "dspModeChanged"
QT_MOC_LITERAL(58, 837, 21), // "workModeForVOIChanged"
QT_MOC_LITERAL(59, 859, 15), // "workModeChanged"
QT_MOC_LITERAL(60, 875, 18), // "userSettingChanged"
QT_MOC_LITERAL(61, 894, 20) // "letterSettingChanged"

    },
    "SectorsViewerWidget\0presetSector\0\0"
    "index\0SharedSectorParameters\0sharedSector\0"
    "newSector\0excludeSector\0deleteSector\0"
    "addSectorsToVOI\0msg\0deleteSectorToVOI\0"
    "setSectorInFocus\0setSectorOutFocus\0"
    "dspActivationOnSector\0targetID\0DSPType\0"
    "type\0isPlotting\0newSectorToDSPWidget\0"
    "clearSectorToDSPWidget\0isDSPAvailableSignal\0"
    "maxDistChangedOnSector\0maxDist\0"
    "clearSectorToGrid\0openMainWidget\0"
    "repeaterNewSectorSignal\0"
    "openWidgetWithCurrentParams\0point\0"
    "targetingAddSlot\0isQuick\0targetingExcludeSlot\0"
    "deleteSectorByTimeoutSlot\0id\0"
    "restartSectorBlinking\0isDSPExceedingUsageLimit\0"
    "resolutionToSwitchingOn\0resolutionToPlottingOn\0"
    "changeDSPSlot\0trackID\0azUgmUpdate\0az\0"
    "ugm\0acceptEffect\0clearEffect\0changeLayout\0"
    "addRow\0delRow\0itemChangeInTable\0"
    "QStandardItem*\0item\0listViewItemClicked\0"
    "QModelIndex\0fillParametersField\0"
    "SectorsPrivateInfo\0info\0autoButtonClicked\0"
    "dspModeChanged\0workModeForVOIChanged\0"
    "workModeChanged\0userSettingChanged\0"
    "letterSettingChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SectorsViewerWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      38,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  204,    2, 0x06 /* Public */,
       6,    2,  209,    2, 0x06 /* Public */,
       7,    1,  214,    2, 0x06 /* Public */,
       8,    1,  217,    2, 0x06 /* Public */,
       9,    1,  220,    2, 0x06 /* Public */,
      11,    1,  223,    2, 0x06 /* Public */,
      12,    1,  226,    2, 0x06 /* Public */,
      13,    0,  229,    2, 0x06 /* Public */,
      14,    3,  230,    2, 0x06 /* Public */,
      19,    1,  237,    2, 0x06 /* Public */,
      20,    1,  240,    2, 0x06 /* Public */,
      21,    0,  243,    2, 0x06 /* Public */,
      22,    2,  244,    2, 0x06 /* Public */,
      24,    1,  249,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    0,  252,    2, 0x0a /* Public */,
      26,    1,  253,    2, 0x0a /* Public */,
      27,    1,  256,    2, 0x0a /* Public */,
      29,    2,  259,    2, 0x0a /* Public */,
      31,    1,  264,    2, 0x0a /* Public */,
      32,    1,  267,    2, 0x0a /* Public */,
      34,    1,  270,    2, 0x0a /* Public */,
      35,    2,  273,    2, 0x0a /* Public */,
      38,    3,  278,    2, 0x0a /* Public */,
      40,    2,  285,    2, 0x0a /* Public */,
      43,    0,  290,    2, 0x08 /* Private */,
      44,    0,  291,    2, 0x08 /* Private */,
      45,    0,  292,    2, 0x08 /* Private */,
      46,    0,  293,    2, 0x08 /* Private */,
      47,    0,  294,    2, 0x08 /* Private */,
      48,    1,  295,    2, 0x08 /* Private */,
      51,    1,  298,    2, 0x08 /* Private */,
      53,    1,  301,    2, 0x08 /* Private */,
      56,    0,  304,    2, 0x08 /* Private */,
      57,    1,  305,    2, 0x08 /* Private */,
      58,    1,  308,    2, 0x08 /* Private */,
      59,    1,  311,    2, 0x08 /* Private */,
      60,    1,  314,    2, 0x08 /* Private */,
      61,    1,  317,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::UChar, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, QMetaType::QByteArray,   10,
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, QMetaType::Bool,   15,   17,   18,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   15,   23,
    QMetaType::Void, QMetaType::Int,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QPointF,   28,
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,   28,   30,
    QMetaType::Void, QMetaType::QPointF,   28,
    QMetaType::Void, QMetaType::UChar,   33,
    QMetaType::Void, QMetaType::UChar,   33,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   36,   37,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, QMetaType::Bool,   39,   17,   18,
    QMetaType::Void, QMetaType::Float, QMetaType::Float,   41,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 49,   50,
    QMetaType::Void, 0x80000000 | 52,    3,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void SectorsViewerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SectorsViewerWidget *_t = static_cast<SectorsViewerWidget *>(_o);
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
        case 8: _t->dspActivationOnSector((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 9: _t->newSectorToDSPWidget((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->clearSectorToDSPWidget((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 11: _t->isDSPAvailableSignal(); break;
        case 12: _t->maxDistChangedOnSector((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 13: _t->clearSectorToGrid((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 14: _t->openMainWidget(); break;
        case 15: _t->repeaterNewSectorSignal((*reinterpret_cast< SharedSectorParameters(*)>(_a[1]))); break;
        case 16: _t->openWidgetWithCurrentParams((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 17: _t->targetingAddSlot((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 18: _t->targetingExcludeSlot((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 19: _t->deleteSectorByTimeoutSlot((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 20: _t->restartSectorBlinking((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 21: _t->isDSPExceedingUsageLimit((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 22: _t->changeDSPSlot((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 23: _t->azUgmUpdate((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 24: _t->acceptEffect(); break;
        case 25: _t->clearEffect(); break;
        case 26: _t->changeLayout(); break;
        case 27: _t->addRow(); break;
        case 28: _t->delRow(); break;
        case 29: _t->itemChangeInTable((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 30: _t->listViewItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 31: _t->fillParametersField((*reinterpret_cast< const SectorsPrivateInfo(*)>(_a[1]))); break;
        case 32: _t->autoButtonClicked(); break;
        case 33: _t->dspModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->workModeForVOIChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->workModeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->userSettingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->letterSettingChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        {
            using _t = void (SectorsViewerWidget::*)(qint32 , DSPType , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::dspActivationOnSector)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::newSectorToDSPWidget)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::clearSectorToDSPWidget)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::isDSPAvailableSignal)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(qint32 , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::maxDistChangedOnSector)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (SectorsViewerWidget::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SectorsViewerWidget::clearSectorToGrid)) {
                *result = 13;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SectorsViewerWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_SectorsViewerWidget.data,
      qt_meta_data_SectorsViewerWidget,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 38;
    }
    return _id;
}

// SIGNAL 0
void SectorsViewerWidget::presetSector(const quint8 _t1, SharedSectorParameters _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SectorsViewerWidget::newSector(const quint8 _t1, SharedSectorParameters _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SectorsViewerWidget::excludeSector(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SectorsViewerWidget::deleteSector(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SectorsViewerWidget::addSectorsToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SectorsViewerWidget::deleteSectorToVOI(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SectorsViewerWidget::setSectorInFocus(const quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SectorsViewerWidget::setSectorOutFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void SectorsViewerWidget::dspActivationOnSector(qint32 _t1, DSPType _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SectorsViewerWidget::newSectorToDSPWidget(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void SectorsViewerWidget::clearSectorToDSPWidget(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void SectorsViewerWidget::isDSPAvailableSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void SectorsViewerWidget::maxDistChangedOnSector(qint32 _t1, float _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void SectorsViewerWidget::clearSectorToGrid(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
