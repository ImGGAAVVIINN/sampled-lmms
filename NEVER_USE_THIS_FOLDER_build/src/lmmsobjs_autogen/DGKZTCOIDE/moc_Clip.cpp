/****************************************************************************
** Meta object code from reading C++ file 'Clip.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/Clip.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Clip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__Clip_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__Clip_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__Clip_t qt_meta_stringdata_lmms__Clip = {
    {
QT_MOC_LITERAL(0, 0, 10), // "lmms::Clip"
QT_MOC_LITERAL(1, 11, 13), // "lengthChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "positionChanged"
QT_MOC_LITERAL(4, 42, 13), // "destroyedClip"
QT_MOC_LITERAL(5, 56, 12), // "colorChanged"
QT_MOC_LITERAL(6, 69, 10) // "toggleMute"

    },
    "lmms::Clip\0lengthChanged\0\0positionChanged\0"
    "destroyedClip\0colorChanged\0toggleMute"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__Clip[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void lmms::Clip::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Clip *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->lengthChanged(); break;
        case 1: _t->positionChanged(); break;
        case 2: _t->destroyedClip(); break;
        case 3: _t->colorChanged(); break;
        case 4: _t->toggleMute(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Clip::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Clip::lengthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Clip::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Clip::positionChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Clip::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Clip::destroyedClip)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Clip::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Clip::colorChanged)) {
                *result = 3;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::Clip::staticMetaObject = { {
    QMetaObject::SuperData::link<Model::staticMetaObject>(),
    qt_meta_stringdata_lmms__Clip.data,
    qt_meta_data_lmms__Clip,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::Clip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::Clip::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__Clip.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JournallingObject"))
        return static_cast< JournallingObject*>(this);
    return Model::qt_metacast(_clname);
}

int lmms::Clip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Model::qt_metacall(_c, _id, _a);
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
void lmms::Clip::lengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::Clip::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void lmms::Clip::destroyedClip()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void lmms::Clip::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
