/****************************************************************************
** Meta object code from reading C++ file 'Organic.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Organic/Organic.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Organic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__OscillatorObject_t {
    QByteArrayData data[5];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__OscillatorObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__OscillatorObject_t qt_meta_stringdata_lmms__OscillatorObject = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::OscillatorObject"
QT_MOC_LITERAL(1, 23, 16), // "oscButtonChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 12), // "updateVolume"
QT_MOC_LITERAL(4, 54, 14) // "updateDetuning"

    },
    "lmms::OscillatorObject\0oscButtonChanged\0"
    "\0updateVolume\0updateDetuning"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__OscillatorObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::OscillatorObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OscillatorObject *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->oscButtonChanged(); break;
        case 1: _t->updateVolume(); break;
        case 2: _t->updateDetuning(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::OscillatorObject::staticMetaObject = { {
    QMetaObject::SuperData::link<Model::staticMetaObject>(),
    qt_meta_stringdata_lmms__OscillatorObject.data,
    qt_meta_data_lmms__OscillatorObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::OscillatorObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::OscillatorObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__OscillatorObject.stringdata0))
        return static_cast<void*>(this);
    return Model::qt_metacast(_clname);
}

int lmms::OscillatorObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Model::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_lmms__OrganicInstrument_t {
    QByteArrayData data[4];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__OrganicInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__OrganicInstrument_t qt_meta_stringdata_lmms__OrganicInstrument = {
    {
QT_MOC_LITERAL(0, 0, 23), // "lmms::OrganicInstrument"
QT_MOC_LITERAL(1, 24, 17), // "randomiseSettings"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 17) // "updateAllDetuning"

    },
    "lmms::OrganicInstrument\0randomiseSettings\0"
    "\0updateAllDetuning"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__OrganicInstrument[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::OrganicInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OrganicInstrument *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->randomiseSettings(); break;
        case 1: _t->updateAllDetuning(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::OrganicInstrument::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__OrganicInstrument.data,
    qt_meta_data_lmms__OrganicInstrument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::OrganicInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::OrganicInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__OrganicInstrument.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::OrganicInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_lmms__gui__OrganicInstrumentView_t {
    QByteArrayData data[3];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__OrganicInstrumentView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__OrganicInstrumentView_t qt_meta_stringdata_lmms__gui__OrganicInstrumentView = {
    {
QT_MOC_LITERAL(0, 0, 32), // "lmms::gui::OrganicInstrumentView"
QT_MOC_LITERAL(1, 33, 14), // "updateKnobHint"
QT_MOC_LITERAL(2, 48, 0) // ""

    },
    "lmms::gui::OrganicInstrumentView\0"
    "updateKnobHint\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__OrganicInstrumentView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void lmms::gui::OrganicInstrumentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OrganicInstrumentView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateKnobHint(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::OrganicInstrumentView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__OrganicInstrumentView.data,
    qt_meta_data_lmms__gui__OrganicInstrumentView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::OrganicInstrumentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::OrganicInstrumentView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__OrganicInstrumentView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::OrganicInstrumentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
