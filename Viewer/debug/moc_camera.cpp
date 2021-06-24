/****************************************************************************
** Meta object code from reading C++ file 'camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Camera_t {
    QByteArrayData data[38];
    char stringdata0[412];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Camera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Camera_t qt_meta_stringdata_Camera = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Camera"
QT_MOC_LITERAL(1, 7, 11), // "resetCamera"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "setPosition"
QT_MOC_LITERAL(4, 32, 8), // "position"
QT_MOC_LITERAL(5, 41, 11), // "setUpVector"
QT_MOC_LITERAL(6, 53, 8), // "upVector"
QT_MOC_LITERAL(7, 62, 13), // "setViewCenter"
QT_MOC_LITERAL(8, 76, 10), // "viewCenter"
QT_MOC_LITERAL(9, 87, 9), // "translate"
QT_MOC_LITERAL(10, 97, 6), // "vLocal"
QT_MOC_LITERAL(11, 104, 23), // "CameraTranslationOption"
QT_MOC_LITERAL(12, 128, 6), // "option"
QT_MOC_LITERAL(13, 135, 14), // "translateWorld"
QT_MOC_LITERAL(14, 150, 6), // "vWorld"
QT_MOC_LITERAL(15, 157, 5), // "pitch"
QT_MOC_LITERAL(16, 163, 5), // "angle"
QT_MOC_LITERAL(17, 169, 3), // "yaw"
QT_MOC_LITERAL(18, 173, 4), // "axis"
QT_MOC_LITERAL(19, 178, 4), // "roll"
QT_MOC_LITERAL(20, 183, 20), // "pitchAboutViewCenter"
QT_MOC_LITERAL(21, 204, 18), // "yawAboutViewCenter"
QT_MOC_LITERAL(22, 223, 19), // "rollAboutViewCenter"
QT_MOC_LITERAL(23, 243, 6), // "rotate"
QT_MOC_LITERAL(24, 250, 1), // "q"
QT_MOC_LITERAL(25, 252, 21), // "rotateAboutViewCenter"
QT_MOC_LITERAL(26, 274, 14), // "projectionType"
QT_MOC_LITERAL(27, 289, 14), // "ProjectionType"
QT_MOC_LITERAL(28, 304, 9), // "nearPlane"
QT_MOC_LITERAL(29, 314, 8), // "farPlane"
QT_MOC_LITERAL(30, 323, 11), // "fieldOfView"
QT_MOC_LITERAL(31, 335, 11), // "aspectRatio"
QT_MOC_LITERAL(32, 347, 4), // "left"
QT_MOC_LITERAL(33, 352, 5), // "right"
QT_MOC_LITERAL(34, 358, 6), // "bottom"
QT_MOC_LITERAL(35, 365, 3), // "top"
QT_MOC_LITERAL(36, 369, 20), // "OrthogonalProjection"
QT_MOC_LITERAL(37, 390, 21) // "PerspectiveProjection"

    },
    "Camera\0resetCamera\0\0setPosition\0"
    "position\0setUpVector\0upVector\0"
    "setViewCenter\0viewCenter\0translate\0"
    "vLocal\0CameraTranslationOption\0option\0"
    "translateWorld\0vWorld\0pitch\0angle\0yaw\0"
    "axis\0roll\0pitchAboutViewCenter\0"
    "yawAboutViewCenter\0rollAboutViewCenter\0"
    "rotate\0q\0rotateAboutViewCenter\0"
    "projectionType\0ProjectionType\0nearPlane\0"
    "farPlane\0fieldOfView\0aspectRatio\0left\0"
    "right\0bottom\0top\0OrthogonalProjection\0"
    "PerspectiveProjection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Camera[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
      12,  154, // properties
       1,  190, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,  100,    2, 0x0a /* Public */,
       5,    1,  103,    2, 0x0a /* Public */,
       7,    1,  106,    2, 0x0a /* Public */,
       9,    2,  109,    2, 0x0a /* Public */,
       9,    1,  114,    2, 0x2a /* Public | MethodCloned */,
      13,    2,  117,    2, 0x0a /* Public */,
      13,    1,  122,    2, 0x2a /* Public | MethodCloned */,
      15,    1,  125,    2, 0x0a /* Public */,
      17,    1,  128,    2, 0x0a /* Public */,
      17,    2,  131,    2, 0x0a /* Public */,
      19,    1,  136,    2, 0x0a /* Public */,
      20,    1,  139,    2, 0x0a /* Public */,
      21,    1,  142,    2, 0x0a /* Public */,
      22,    1,  145,    2, 0x0a /* Public */,
      23,    1,  148,    2, 0x0a /* Public */,
      25,    1,  151,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QVector3D,    4,
    QMetaType::Void, QMetaType::QVector3D,    6,
    QMetaType::Void, QMetaType::QVector3D,    8,
    QMetaType::Void, QMetaType::QVector3D, 0x80000000 | 11,   10,   12,
    QMetaType::Void, QMetaType::QVector3D,   10,
    QMetaType::Void, QMetaType::QVector3D, 0x80000000 | 11,   14,   12,
    QMetaType::Void, QMetaType::QVector3D,   14,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::Float, QMetaType::QVector3D,   16,   18,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::Float,   16,
    QMetaType::Void, QMetaType::QQuaternion,   24,
    QMetaType::Void, QMetaType::QQuaternion,   24,

 // properties: name, type, flags
       4, QMetaType::QVector3D, 0x00095103,
       6, QMetaType::QVector3D, 0x00095103,
       8, QMetaType::QVector3D, 0x00095103,
      26, 0x80000000 | 27, 0x00095009,
      28, QMetaType::Float, 0x00095103,
      29, QMetaType::Float, 0x00095103,
      30, QMetaType::Float, 0x00095103,
      31, QMetaType::Float, 0x00095103,
      32, QMetaType::Float, 0x00095103,
      33, QMetaType::Float, 0x00095103,
      34, QMetaType::Float, 0x00095103,
      35, QMetaType::Float, 0x00095103,

 // enums: name, alias, flags, count, data
      27,   27, 0x0,    2,  195,

 // enum data: key, value
      36, uint(Camera::OrthogonalProjection),
      37, uint(Camera::PerspectiveProjection),

       0        // eod
};

void Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->resetCamera(); break;
        case 1: _t->setPosition((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 2: _t->setUpVector((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 3: _t->setViewCenter((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 4: _t->translate((*reinterpret_cast< const QVector3D(*)>(_a[1])),(*reinterpret_cast< CameraTranslationOption(*)>(_a[2]))); break;
        case 5: _t->translate((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 6: _t->translateWorld((*reinterpret_cast< const QVector3D(*)>(_a[1])),(*reinterpret_cast< CameraTranslationOption(*)>(_a[2]))); break;
        case 7: _t->translateWorld((*reinterpret_cast< const QVector3D(*)>(_a[1]))); break;
        case 8: _t->pitch((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 9: _t->yaw((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 10: _t->yaw((*reinterpret_cast< const float(*)>(_a[1])),(*reinterpret_cast< const QVector3D(*)>(_a[2]))); break;
        case 11: _t->roll((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 12: _t->pitchAboutViewCenter((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 13: _t->yawAboutViewCenter((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 14: _t->rollAboutViewCenter((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 15: _t->rotate((*reinterpret_cast< const QQuaternion(*)>(_a[1]))); break;
        case 16: _t->rotateAboutViewCenter((*reinterpret_cast< const QQuaternion(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Camera::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::resetCamera)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVector3D*>(_v) = _t->position(); break;
        case 1: *reinterpret_cast< QVector3D*>(_v) = _t->upVector(); break;
        case 2: *reinterpret_cast< QVector3D*>(_v) = _t->viewCenter(); break;
        case 3: *reinterpret_cast< ProjectionType*>(_v) = _t->projectionType(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->nearPlane(); break;
        case 5: *reinterpret_cast< float*>(_v) = _t->farPlane(); break;
        case 6: *reinterpret_cast< float*>(_v) = _t->fieldOfView(); break;
        case 7: *reinterpret_cast< float*>(_v) = _t->aspectRatio(); break;
        case 8: *reinterpret_cast< float*>(_v) = _t->left(); break;
        case 9: *reinterpret_cast< float*>(_v) = _t->right(); break;
        case 10: *reinterpret_cast< float*>(_v) = _t->bottom(); break;
        case 11: *reinterpret_cast< float*>(_v) = _t->top(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPosition(*reinterpret_cast< QVector3D*>(_v)); break;
        case 1: _t->setUpVector(*reinterpret_cast< QVector3D*>(_v)); break;
        case 2: _t->setViewCenter(*reinterpret_cast< QVector3D*>(_v)); break;
        case 4: _t->setNearPlane(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setFarPlane(*reinterpret_cast< float*>(_v)); break;
        case 6: _t->setFieldOfView(*reinterpret_cast< float*>(_v)); break;
        case 7: _t->setAspectRatio(*reinterpret_cast< float*>(_v)); break;
        case 8: _t->setLeft(*reinterpret_cast< float*>(_v)); break;
        case 9: _t->setRight(*reinterpret_cast< float*>(_v)); break;
        case 10: _t->setBottom(*reinterpret_cast< float*>(_v)); break;
        case 11: _t->setTop(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject Camera::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Camera.data,
    qt_meta_data_Camera,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Camera.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void Camera::resetCamera()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
