/****************************************************************************
** Meta object code from reading C++ file 'Timeline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/Timeline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Timeline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__Timeline_t {
    QByteArrayData data[9];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__Timeline_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__Timeline_t qt_meta_stringdata_lmms__Timeline = {
    {
QT_MOC_LITERAL(0, 0, 14), // "lmms::Timeline"
QT_MOC_LITERAL(1, 15, 18), // "loopEnabledChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 7), // "enabled"
QT_MOC_LITERAL(4, 43, 20), // "stopBehaviourChanged"
QT_MOC_LITERAL(5, 64, 29), // "lmms::Timeline::StopBehaviour"
QT_MOC_LITERAL(6, 94, 9), // "behaviour"
QT_MOC_LITERAL(7, 104, 15), // "positionChanged"
QT_MOC_LITERAL(8, 120, 14) // "positionJumped"

    },
    "lmms::Timeline\0loopEnabledChanged\0\0"
    "enabled\0stopBehaviourChanged\0"
    "lmms::Timeline::StopBehaviour\0behaviour\0"
    "positionChanged\0positionJumped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__Timeline[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       7,    0,   40,    2, 0x06 /* Public */,
       8,    0,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::Timeline::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Timeline *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->loopEnabledChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->stopBehaviourChanged((*reinterpret_cast< lmms::Timeline::StopBehaviour(*)>(_a[1]))); break;
        case 2: _t->positionChanged(); break;
        case 3: _t->positionJumped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Timeline::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Timeline::loopEnabledChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Timeline::*)(lmms::Timeline::StopBehaviour );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Timeline::stopBehaviourChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Timeline::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Timeline::positionChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Timeline::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Timeline::positionJumped)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::Timeline::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__Timeline.data,
    qt_meta_data_lmms__Timeline,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::Timeline::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::Timeline::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__Timeline.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JournallingObject"))
        return static_cast< JournallingObject*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::Timeline::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void lmms::Timeline::loopEnabledChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lmms::Timeline::stopBehaviourChanged(lmms::Timeline::StopBehaviour _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void lmms::Timeline::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void lmms::Timeline::positionJumped()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
