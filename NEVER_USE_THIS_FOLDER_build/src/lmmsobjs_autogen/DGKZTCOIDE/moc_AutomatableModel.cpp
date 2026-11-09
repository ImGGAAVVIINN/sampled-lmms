/****************************************************************************
** Meta object code from reading C++ file 'AutomatableModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/AutomatableModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AutomatableModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__AutomatableModel_t {
    QByteArrayData data[12];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__AutomatableModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__AutomatableModel_t qt_meta_stringdata_lmms__AutomatableModel = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::AutomatableModel"
QT_MOC_LITERAL(1, 23, 16), // "initValueChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 3), // "val"
QT_MOC_LITERAL(4, 45, 9), // "destroyed"
QT_MOC_LITERAL(5, 55, 13), // "lmms::jo_id_t"
QT_MOC_LITERAL(6, 69, 2), // "id"
QT_MOC_LITERAL(7, 72, 5), // "reset"
QT_MOC_LITERAL(8, 78, 6), // "unlink"
QT_MOC_LITERAL(9, 85, 26), // "unlinkControllerConnection"
QT_MOC_LITERAL(10, 112, 21), // "setUseControllerValue"
QT_MOC_LITERAL(11, 134, 1) // "b"

    },
    "lmms::AutomatableModel\0initValueChanged\0"
    "\0val\0destroyed\0lmms::jo_id_t\0id\0reset\0"
    "unlink\0unlinkControllerConnection\0"
    "setUseControllerValue\0b"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__AutomatableModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,
      10,    1,   58,    2, 0x0a /* Public */,
      10,    0,   61,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,

       0        // eod
};

void lmms::AutomatableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AutomatableModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->initValueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->destroyed((*reinterpret_cast< lmms::jo_id_t(*)>(_a[1]))); break;
        case 2: _t->reset(); break;
        case 3: _t->unlink(); break;
        case 4: _t->unlinkControllerConnection(); break;
        case 5: _t->setUseControllerValue((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setUseControllerValue(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AutomatableModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutomatableModel::initValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AutomatableModel::*)(lmms::jo_id_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AutomatableModel::destroyed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::AutomatableModel::staticMetaObject = { {
    QMetaObject::SuperData::link<Model::staticMetaObject>(),
    qt_meta_stringdata_lmms__AutomatableModel.data,
    qt_meta_data_lmms__AutomatableModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::AutomatableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::AutomatableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__AutomatableModel.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JournallingObject"))
        return static_cast< JournallingObject*>(this);
    return Model::qt_metacast(_clname);
}

int lmms::AutomatableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Model::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void lmms::AutomatableModel::initValueChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lmms::AutomatableModel::destroyed(lmms::jo_id_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_lmms__FloatModel_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__FloatModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__FloatModel_t qt_meta_stringdata_lmms__FloatModel = {
    {
QT_MOC_LITERAL(0, 0, 16) // "lmms::FloatModel"

    },
    "lmms::FloatModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__FloatModel[] = {

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

void lmms::FloatModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::FloatModel::staticMetaObject = { {
    QMetaObject::SuperData::link<TypedAutomatableModel<float>::staticMetaObject>(),
    qt_meta_stringdata_lmms__FloatModel.data,
    qt_meta_data_lmms__FloatModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::FloatModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::FloatModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__FloatModel.stringdata0))
        return static_cast<void*>(this);
    return TypedAutomatableModel<float>::qt_metacast(_clname);
}

int lmms::FloatModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TypedAutomatableModel<float>::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_lmms__IntModel_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__IntModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__IntModel_t qt_meta_stringdata_lmms__IntModel = {
    {
QT_MOC_LITERAL(0, 0, 14) // "lmms::IntModel"

    },
    "lmms::IntModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__IntModel[] = {

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

void lmms::IntModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::IntModel::staticMetaObject = { {
    QMetaObject::SuperData::link<TypedAutomatableModel<int>::staticMetaObject>(),
    qt_meta_stringdata_lmms__IntModel.data,
    qt_meta_data_lmms__IntModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::IntModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::IntModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__IntModel.stringdata0))
        return static_cast<void*>(this);
    return TypedAutomatableModel<int>::qt_metacast(_clname);
}

int lmms::IntModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TypedAutomatableModel<int>::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_lmms__BoolModel_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__BoolModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__BoolModel_t qt_meta_stringdata_lmms__BoolModel = {
    {
QT_MOC_LITERAL(0, 0, 15) // "lmms::BoolModel"

    },
    "lmms::BoolModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__BoolModel[] = {

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

void lmms::BoolModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::BoolModel::staticMetaObject = { {
    QMetaObject::SuperData::link<TypedAutomatableModel<bool>::staticMetaObject>(),
    qt_meta_stringdata_lmms__BoolModel.data,
    qt_meta_data_lmms__BoolModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::BoolModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::BoolModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__BoolModel.stringdata0))
        return static_cast<void*>(this);
    return TypedAutomatableModel<bool>::qt_metacast(_clname);
}

int lmms::BoolModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TypedAutomatableModel<bool>::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
