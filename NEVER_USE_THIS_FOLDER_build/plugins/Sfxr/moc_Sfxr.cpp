/****************************************************************************
** Meta object code from reading C++ file 'Sfxr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Sfxr/Sfxr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Sfxr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__SfxrInstrument_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__SfxrInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__SfxrInstrument_t qt_meta_stringdata_lmms__SfxrInstrument = {
    {
QT_MOC_LITERAL(0, 0, 20) // "lmms::SfxrInstrument"

    },
    "lmms::SfxrInstrument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__SfxrInstrument[] = {

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

void lmms::SfxrInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::SfxrInstrument::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__SfxrInstrument.data,
    qt_meta_data_lmms__SfxrInstrument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::SfxrInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::SfxrInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__SfxrInstrument.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::SfxrInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_lmms__gui__SfxrInstrumentView_t {
    QByteArrayData data[12];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__SfxrInstrumentView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__SfxrInstrumentView_t qt_meta_stringdata_lmms__gui__SfxrInstrumentView = {
    {
QT_MOC_LITERAL(0, 0, 29), // "lmms::gui::SfxrInstrumentView"
QT_MOC_LITERAL(1, 30, 9), // "genPickup"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "genLaser"
QT_MOC_LITERAL(4, 50, 12), // "genExplosion"
QT_MOC_LITERAL(5, 63, 10), // "genPowerup"
QT_MOC_LITERAL(6, 74, 6), // "genHit"
QT_MOC_LITERAL(7, 81, 7), // "genJump"
QT_MOC_LITERAL(8, 89, 7), // "genBlip"
QT_MOC_LITERAL(9, 97, 9), // "randomize"
QT_MOC_LITERAL(10, 107, 6), // "mutate"
QT_MOC_LITERAL(11, 114, 12) // "previewSound"

    },
    "lmms::gui::SfxrInstrumentView\0genPickup\0"
    "\0genLaser\0genExplosion\0genPowerup\0"
    "genHit\0genJump\0genBlip\0randomize\0"
    "mutate\0previewSound"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__SfxrInstrumentView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    0,   69,    2, 0x09 /* Protected */,
       8,    0,   70,    2, 0x09 /* Protected */,
       9,    0,   71,    2, 0x09 /* Protected */,
      10,    0,   72,    2, 0x09 /* Protected */,
      11,    0,   73,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::SfxrInstrumentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SfxrInstrumentView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->genPickup(); break;
        case 1: _t->genLaser(); break;
        case 2: _t->genExplosion(); break;
        case 3: _t->genPowerup(); break;
        case 4: _t->genHit(); break;
        case 5: _t->genJump(); break;
        case 6: _t->genBlip(); break;
        case 7: _t->randomize(); break;
        case 8: _t->mutate(); break;
        case 9: _t->previewSound(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::SfxrInstrumentView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__SfxrInstrumentView.data,
    qt_meta_data_lmms__gui__SfxrInstrumentView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::SfxrInstrumentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::SfxrInstrumentView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__SfxrInstrumentView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::SfxrInstrumentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
