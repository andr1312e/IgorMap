/****************************************************************************
** Meta object code from reading C++ file 'dspwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dspwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dspwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FFTWProcessor_t {
    QByteArrayData data[16];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FFTWProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FFTWProcessor_t qt_meta_stringdata_FFTWProcessor = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FFTWProcessor"
QT_MOC_LITERAL(1, 14, 13), // "processedData"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "targetID"
QT_MOC_LITERAL(4, 38, 7), // "counter"
QT_MOC_LITERAL(5, 46, 11), // "VectorOfAmp"
QT_MOC_LITERAL(6, 58, 6), // "vector"
QT_MOC_LITERAL(7, 65, 6), // "doWork"
QT_MOC_LITERAL(8, 72, 14), // "dspChangedSlot"
QT_MOC_LITERAL(9, 87, 10), // "isPlotting"
QT_MOC_LITERAL(10, 98, 14), // "newDataForWork"
QT_MOC_LITERAL(11, 113, 1), // "N"
QT_MOC_LITERAL(12, 115, 13), // "VectorRawData"
QT_MOC_LITERAL(13, 129, 6), // "matrix"
QT_MOC_LITERAL(14, 136, 8), // "setPlane"
QT_MOC_LITERAL(15, 145, 1) // "M"

    },
    "FFTWProcessor\0processedData\0\0targetID\0"
    "counter\0VectorOfAmp\0vector\0doWork\0"
    "dspChangedSlot\0isPlotting\0newDataForWork\0"
    "N\0VectorRawData\0matrix\0setPlane\0M"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FFTWProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   46,    2, 0x0a /* Public */,
       8,    2,   47,    2, 0x0a /* Public */,
      10,    4,   52,    2, 0x0a /* Public */,
      14,    3,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, 0x80000000 | 5,    3,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 12,    3,    4,   11,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, QMetaType::UInt,    3,   11,   15,

       0        // eod
};

void FFTWProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FFTWProcessor *_t = static_cast<FFTWProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processedData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< VectorOfAmp(*)>(_a[3]))); break;
        case 1: _t->doWork(); break;
        case 2: _t->dspChangedSlot((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->newDataForWork((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3])),(*reinterpret_cast< VectorRawData(*)>(_a[4]))); break;
        case 4: _t->setPlane((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FFTWProcessor::*)(qint32 , quint32 , VectorOfAmp );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FFTWProcessor::processedData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FFTWProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FFTWProcessor.data,
      qt_meta_data_FFTWProcessor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *FFTWProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FFTWProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FFTWProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FFTWProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void FFTWProcessor::processedData(qint32 _t1, quint32 _t2, VectorOfAmp _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_DSPDataHandler_t {
    QByteArrayData data[35];
    char stringdata0[483];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DSPDataHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DSPDataHandler_t qt_meta_stringdata_DSPDataHandler = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DSPDataHandler"
QT_MOC_LITERAL(1, 15, 10), // "dspChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "targetID"
QT_MOC_LITERAL(4, 36, 10), // "isPlotting"
QT_MOC_LITERAL(5, 47, 17), // "prepareFFTWSignal"
QT_MOC_LITERAL(6, 65, 1), // "N"
QT_MOC_LITERAL(7, 67, 1), // "M"
QT_MOC_LITERAL(8, 69, 22), // "dataReadyForProcessing"
QT_MOC_LITERAL(9, 92, 5), // "index"
QT_MOC_LITERAL(10, 98, 13), // "VectorRawData"
QT_MOC_LITERAL(11, 112, 6), // "matrix"
QT_MOC_LITERAL(12, 119, 14), // "dspPackToScene"
QT_MOC_LITERAL(13, 134, 33), // "QSharedPointer<QVector<DSPDat..."
QT_MOC_LITERAL(14, 168, 12), // "sharedVector"
QT_MOC_LITERAL(15, 181, 36), // "sendColorRangesOnSceneRepeate..."
QT_MOC_LITERAL(16, 218, 6), // "target"
QT_MOC_LITERAL(17, 225, 11), // "ColorRanges"
QT_MOC_LITERAL(18, 237, 11), // "colorRanges"
QT_MOC_LITERAL(19, 249, 18), // "deleteDSPFromScene"
QT_MOC_LITERAL(20, 268, 17), // "dspMessageHandler"
QT_MOC_LITERAL(21, 286, 18), // "RLSODSPDataMessage"
QT_MOC_LITERAL(22, 305, 3), // "msg"
QT_MOC_LITERAL(23, 309, 14), // "prepareDSPInfo"
QT_MOC_LITERAL(24, 324, 7), // "DSPType"
QT_MOC_LITERAL(25, 332, 4), // "type"
QT_MOC_LITERAL(26, 337, 7), // "setData"
QT_MOC_LITERAL(27, 345, 7), // "counter"
QT_MOC_LITERAL(28, 353, 11), // "VectorOfAmp"
QT_MOC_LITERAL(29, 365, 6), // "vector"
QT_MOC_LITERAL(30, 372, 8), // "showPlot"
QT_MOC_LITERAL(31, 381, 28), // "setPositionOnVectorOfDSPSlot"
QT_MOC_LITERAL(32, 410, 3), // "pos"
QT_MOC_LITERAL(33, 414, 33), // "setPositionOnVectorOfDSPPleer..."
QT_MOC_LITERAL(34, 448, 34) // "sendColorRangesOnSceneRepeate..."

    },
    "DSPDataHandler\0dspChanged\0\0targetID\0"
    "isPlotting\0prepareFFTWSignal\0N\0M\0"
    "dataReadyForProcessing\0index\0VectorRawData\0"
    "matrix\0dspPackToScene\0"
    "QSharedPointer<QVector<DSPData> >\0"
    "sharedVector\0sendColorRangesOnSceneRepeaterSignal\0"
    "target\0ColorRanges\0colorRanges\0"
    "deleteDSPFromScene\0dspMessageHandler\0"
    "RLSODSPDataMessage\0msg\0prepareDSPInfo\0"
    "DSPType\0type\0setData\0counter\0VectorOfAmp\0"
    "vector\0showPlot\0setPositionOnVectorOfDSPSlot\0"
    "pos\0setPositionOnVectorOfDSPPleerSlot\0"
    "sendColorRangesOnSceneRepeaterSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DSPDataHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       5,    3,   84,    2, 0x06 /* Public */,
       8,    4,   91,    2, 0x06 /* Public */,
      12,    2,  100,    2, 0x06 /* Public */,
      15,    2,  105,    2, 0x06 /* Public */,
      19,    1,  110,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,  113,    2, 0x0a /* Public */,
      23,    3,  116,    2, 0x0a /* Public */,
      26,    3,  123,    2, 0x0a /* Public */,
      30,    1,  130,    2, 0x0a /* Public */,
      31,    2,  133,    2, 0x0a /* Public */,
      33,    2,  138,    2, 0x0a /* Public */,
      34,    2,  143,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, QMetaType::UInt,    3,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 10,    3,    9,    6,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,    3,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17,   16,   18,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24, QMetaType::Bool,    3,   25,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt, 0x80000000 | 28,    3,   27,   29,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt,   16,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::UInt,   16,   32,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17,   16,   18,

       0        // eod
};

void DSPDataHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DSPDataHandler *_t = static_cast<DSPDataHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dspChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->prepareFFTWSignal((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3]))); break;
        case 2: _t->dataReadyForProcessing((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< quint32(*)>(_a[3])),(*reinterpret_cast< VectorRawData(*)>(_a[4]))); break;
        case 3: _t->dspPackToScene((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< QSharedPointer<QVector<DSPData> >(*)>(_a[2]))); break;
        case 4: _t->sendColorRangesOnSceneRepeaterSignal((*reinterpret_cast< const qint32(*)>(_a[1])),(*reinterpret_cast< ColorRanges(*)>(_a[2]))); break;
        case 5: _t->deleteDSPFromScene((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 6: _t->dspMessageHandler((*reinterpret_cast< RLSODSPDataMessage(*)>(_a[1]))); break;
        case 7: _t->prepareDSPInfo((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 8: _t->setData((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2])),(*reinterpret_cast< VectorOfAmp(*)>(_a[3]))); break;
        case 9: _t->showPlot((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 10: _t->setPositionOnVectorOfDSPSlot((*reinterpret_cast< const qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 11: _t->setPositionOnVectorOfDSPPleerSlot((*reinterpret_cast< const qint32(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 12: _t->sendColorRangesOnSceneRepeaterSlot((*reinterpret_cast< const qint32(*)>(_a[1])),(*reinterpret_cast< ColorRanges(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RLSODSPDataMessage >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DSPDataHandler::*)(qint32 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPDataHandler::dspChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DSPDataHandler::*)(qint32 , quint32 , quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPDataHandler::prepareFFTWSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DSPDataHandler::*)(qint32 , quint32 , quint32 , VectorRawData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPDataHandler::dataReadyForProcessing)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DSPDataHandler::*)(qint32 , QSharedPointer<QVector<DSPData>> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPDataHandler::dspPackToScene)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DSPDataHandler::*)(const qint32 , ColorRanges );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPDataHandler::sendColorRangesOnSceneRepeaterSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DSPDataHandler::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPDataHandler::deleteDSPFromScene)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DSPDataHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DSPDataHandler.data,
      qt_meta_data_DSPDataHandler,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DSPDataHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DSPDataHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DSPDataHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DSPDataHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void DSPDataHandler::dspChanged(qint32 _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DSPDataHandler::prepareFFTWSignal(qint32 _t1, quint32 _t2, quint32 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DSPDataHandler::dataReadyForProcessing(qint32 _t1, quint32 _t2, quint32 _t3, VectorRawData _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DSPDataHandler::dspPackToScene(qint32 _t1, QSharedPointer<QVector<DSPData>> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DSPDataHandler::sendColorRangesOnSceneRepeaterSignal(const qint32 _t1, ColorRanges _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DSPDataHandler::deleteDSPFromScene(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
struct qt_meta_stringdata_DSPWidget_t {
    QByteArrayData data[30];
    char stringdata0[438];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DSPWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DSPWidget_t qt_meta_stringdata_DSPWidget = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DSPWidget"
QT_MOC_LITERAL(1, 10, 27), // "isExceedingUsageLimitSignal"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 23), // "resolutionToSwitchingOn"
QT_MOC_LITERAL(4, 63, 22), // "resolutionToPlottingOn"
QT_MOC_LITERAL(5, 86, 9), // "changeDSP"
QT_MOC_LITERAL(6, 96, 8), // "targetID"
QT_MOC_LITERAL(7, 105, 7), // "DSPType"
QT_MOC_LITERAL(8, 113, 4), // "type"
QT_MOC_LITERAL(9, 118, 10), // "isPlotting"
QT_MOC_LITERAL(10, 129, 31), // "updateComboBoxWithTargetsSignal"
QT_MOC_LITERAL(11, 161, 11), // "showDSPPlot"
QT_MOC_LITERAL(12, 173, 22), // "dspAvailabilityRequest"
QT_MOC_LITERAL(13, 196, 9), // "insertDSP"
QT_MOC_LITERAL(14, 206, 9), // "removeDSP"
QT_MOC_LITERAL(15, 216, 9), // "newTarget"
QT_MOC_LITERAL(16, 226, 11), // "clearTarget"
QT_MOC_LITERAL(17, 238, 17), // "customMenuForList"
QT_MOC_LITERAL(18, 256, 3), // "pos"
QT_MOC_LITERAL(19, 260, 19), // "listViewItemClicked"
QT_MOC_LITERAL(20, 280, 11), // "QModelIndex"
QT_MOC_LITERAL(21, 292, 5), // "index"
QT_MOC_LITERAL(22, 298, 29), // "updateComboBoxWithTargetsSlot"
QT_MOC_LITERAL(23, 328, 15), // "plottingToggled"
QT_MOC_LITERAL(24, 344, 15), // "acceptEffectDSP"
QT_MOC_LITERAL(25, 360, 14), // "clearEffectDSP"
QT_MOC_LITERAL(26, 375, 14), // "acceptEffectCT"
QT_MOC_LITERAL(27, 390, 13), // "clearEffectCT"
QT_MOC_LITERAL(28, 404, 21), // "showHidePlotterWidget"
QT_MOC_LITERAL(29, 426, 11) // "openDSPFile"

    },
    "DSPWidget\0isExceedingUsageLimitSignal\0"
    "\0resolutionToSwitchingOn\0"
    "resolutionToPlottingOn\0changeDSP\0"
    "targetID\0DSPType\0type\0isPlotting\0"
    "updateComboBoxWithTargetsSignal\0"
    "showDSPPlot\0dspAvailabilityRequest\0"
    "insertDSP\0removeDSP\0newTarget\0clearTarget\0"
    "customMenuForList\0pos\0listViewItemClicked\0"
    "QModelIndex\0index\0updateComboBoxWithTargetsSlot\0"
    "plottingToggled\0acceptEffectDSP\0"
    "clearEffectDSP\0acceptEffectCT\0"
    "clearEffectCT\0showHidePlotterWidget\0"
    "openDSPFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DSPWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       5,    3,  114,    2, 0x06 /* Public */,
      10,    0,  121,    2, 0x06 /* Public */,
      11,    1,  122,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,  125,    2, 0x0a /* Public */,
      13,    3,  126,    2, 0x0a /* Public */,
      14,    1,  133,    2, 0x0a /* Public */,
      15,    1,  136,    2, 0x0a /* Public */,
      16,    1,  139,    2, 0x0a /* Public */,
      17,    1,  142,    2, 0x08 /* Private */,
      19,    1,  145,    2, 0x08 /* Private */,
      22,    0,  148,    2, 0x08 /* Private */,
      23,    0,  149,    2, 0x08 /* Private */,
      24,    0,  150,    2, 0x08 /* Private */,
      25,    0,  151,    2, 0x08 /* Private */,
      26,    0,  152,    2, 0x08 /* Private */,
      27,    0,  153,    2, 0x08 /* Private */,
      28,    0,  154,    2, 0x08 /* Private */,
      29,    1,  155,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, QMetaType::Bool,    6,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, QMetaType::Bool,    6,    8,    9,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QPoint,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void DSPWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DSPWidget *_t = static_cast<DSPWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->isExceedingUsageLimitSignal((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->changeDSP((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->updateComboBoxWithTargetsSignal(); break;
        case 3: _t->showDSPPlot((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->dspAvailabilityRequest(); break;
        case 5: _t->insertDSP((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< DSPType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 6: _t->removeDSP((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 7: _t->newTarget((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->clearTarget((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 9: _t->customMenuForList((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: _t->listViewItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->updateComboBoxWithTargetsSlot(); break;
        case 12: _t->plottingToggled(); break;
        case 13: _t->acceptEffectDSP(); break;
        case 14: _t->clearEffectDSP(); break;
        case 15: _t->acceptEffectCT(); break;
        case 16: _t->clearEffectCT(); break;
        case 17: _t->showHidePlotterWidget(); break;
        case 18: _t->openDSPFile((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DSPWidget::*)(bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPWidget::isExceedingUsageLimitSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DSPWidget::*)(qint32 , DSPType , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPWidget::changeDSP)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DSPWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPWidget::updateComboBoxWithTargetsSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DSPWidget::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DSPWidget::showDSPPlot)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DSPWidget::staticMetaObject = {
    { &BaseWidget::staticMetaObject, qt_meta_stringdata_DSPWidget.data,
      qt_meta_data_DSPWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DSPWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DSPWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DSPWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWidget::qt_metacast(_clname);
}

int DSPWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void DSPWidget::isExceedingUsageLimitSignal(bool _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DSPWidget::changeDSP(qint32 _t1, DSPType _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DSPWidget::updateComboBoxWithTargetsSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void DSPWidget::showDSPPlot(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
