/****************************************************************************
** Meta object code from reading C++ file 'SampleStretch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/SampleStretch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SampleStretch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__SampleStretchResult_t {
    QByteArrayData data[9];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__SampleStretchResult_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__SampleStretchResult_t qt_meta_stringdata_lmms__SampleStretchResult = {
    {
QT_MOC_LITERAL(0, 0, 25), // "lmms::SampleStretchResult"
QT_MOC_LITERAL(1, 26, 5), // "ready"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "uint64_t"
QT_MOC_LITERAL(4, 42, 10), // "generation"
QT_MOC_LITERAL(5, 53, 3), // "key"
QT_MOC_LITERAL(6, 57, 23), // "std::shared_ptr<Sample>"
QT_MOC_LITERAL(7, 81, 9), // "stretched"
QT_MOC_LITERAL(8, 91, 7) // "deliver"

    },
    "lmms::SampleStretchResult\0ready\0\0"
    "uint64_t\0generation\0key\0std::shared_ptr<Sample>\0"
    "stretched\0deliver"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__SampleStretchResult[] = {

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
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    3,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 6,    4,    5,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 6,    4,    5,    7,

       0        // eod
};

void lmms::SampleStretchResult::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SampleStretchResult *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ready((*reinterpret_cast< uint64_t(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2])),(*reinterpret_cast< std::shared_ptr<Sample>(*)>(_a[3]))); break;
        case 1: _t->deliver((*reinterpret_cast< uint64_t(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2])),(*reinterpret_cast< std::shared_ptr<Sample>(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SampleStretchResult::*)(uint64_t , uint64_t , std::shared_ptr<Sample> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SampleStretchResult::ready)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::SampleStretchResult::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__SampleStretchResult.data,
    qt_meta_data_lmms__SampleStretchResult,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::SampleStretchResult::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::SampleStretchResult::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__SampleStretchResult.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::SampleStretchResult::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void lmms::SampleStretchResult::ready(uint64_t _t1, uint64_t _t2, std::shared_ptr<Sample> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_lmms__SampleStretchManager_t {
    QByteArrayData data[1];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__SampleStretchManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__SampleStretchManager_t qt_meta_stringdata_lmms__SampleStretchManager = {
    {
QT_MOC_LITERAL(0, 0, 26) // "lmms::SampleStretchManager"

    },
    "lmms::SampleStretchManager"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__SampleStretchManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void lmms::SampleStretchManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::SampleStretchManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__SampleStretchManager.data,
    qt_meta_data_lmms__SampleStretchManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::SampleStretchManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::SampleStretchManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__SampleStretchManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::SampleStretchManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
