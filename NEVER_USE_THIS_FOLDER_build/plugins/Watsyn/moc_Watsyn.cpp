/****************************************************************************
** Meta object code from reading C++ file 'Watsyn.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Watsyn/Watsyn.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Watsyn.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__WatsynInstrument_t {
    QByteArrayData data[11];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__WatsynInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__WatsynInstrument_t qt_meta_stringdata_lmms__WatsynInstrument = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::WatsynInstrument"
QT_MOC_LITERAL(1, 23, 13), // "updateVolumes"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 12), // "updateFreqA1"
QT_MOC_LITERAL(4, 51, 12), // "updateFreqA2"
QT_MOC_LITERAL(5, 64, 12), // "updateFreqB1"
QT_MOC_LITERAL(6, 77, 12), // "updateFreqB2"
QT_MOC_LITERAL(7, 90, 12), // "updateWaveA1"
QT_MOC_LITERAL(8, 103, 12), // "updateWaveA2"
QT_MOC_LITERAL(9, 116, 12), // "updateWaveB1"
QT_MOC_LITERAL(10, 129, 12) // "updateWaveB2"

    },
    "lmms::WatsynInstrument\0updateVolumes\0"
    "\0updateFreqA1\0updateFreqA2\0updateFreqB1\0"
    "updateFreqB2\0updateWaveA1\0updateWaveA2\0"
    "updateWaveB1\0updateWaveB2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__WatsynInstrument[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

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

       0        // eod
};

void lmms::WatsynInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WatsynInstrument *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateVolumes(); break;
        case 1: _t->updateFreqA1(); break;
        case 2: _t->updateFreqA2(); break;
        case 3: _t->updateFreqB1(); break;
        case 4: _t->updateFreqB2(); break;
        case 5: _t->updateWaveA1(); break;
        case 6: _t->updateWaveA2(); break;
        case 7: _t->updateWaveB1(); break;
        case 8: _t->updateWaveB2(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::WatsynInstrument::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__WatsynInstrument.data,
    qt_meta_data_lmms__WatsynInstrument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::WatsynInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::WatsynInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__WatsynInstrument.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::WatsynInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_lmms__gui__WatsynView_t {
    QByteArrayData data[13];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__WatsynView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__WatsynView_t qt_meta_stringdata_lmms__gui__WatsynView = {
    {
QT_MOC_LITERAL(0, 0, 21), // "lmms::gui::WatsynView"
QT_MOC_LITERAL(1, 22, 12), // "updateLayout"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "sinWaveClicked"
QT_MOC_LITERAL(4, 51, 14), // "triWaveClicked"
QT_MOC_LITERAL(5, 66, 14), // "sawWaveClicked"
QT_MOC_LITERAL(6, 81, 14), // "sqrWaveClicked"
QT_MOC_LITERAL(7, 96, 13), // "smoothClicked"
QT_MOC_LITERAL(8, 110, 16), // "normalizeClicked"
QT_MOC_LITERAL(9, 127, 13), // "invertClicked"
QT_MOC_LITERAL(10, 141, 16), // "phaseLeftClicked"
QT_MOC_LITERAL(11, 158, 17), // "phaseRightClicked"
QT_MOC_LITERAL(12, 176, 11) // "loadClicked"

    },
    "lmms::gui::WatsynView\0updateLayout\0\0"
    "sinWaveClicked\0triWaveClicked\0"
    "sawWaveClicked\0sqrWaveClicked\0"
    "smoothClicked\0normalizeClicked\0"
    "invertClicked\0phaseLeftClicked\0"
    "phaseRightClicked\0loadClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__WatsynView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x09 /* Protected */,
       3,    0,   70,    2, 0x09 /* Protected */,
       4,    0,   71,    2, 0x09 /* Protected */,
       5,    0,   72,    2, 0x09 /* Protected */,
       6,    0,   73,    2, 0x09 /* Protected */,
       7,    0,   74,    2, 0x09 /* Protected */,
       8,    0,   75,    2, 0x09 /* Protected */,
       9,    0,   76,    2, 0x09 /* Protected */,
      10,    0,   77,    2, 0x09 /* Protected */,
      11,    0,   78,    2, 0x09 /* Protected */,
      12,    0,   79,    2, 0x09 /* Protected */,

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
    QMetaType::Void,

       0        // eod
};

void lmms::gui::WatsynView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WatsynView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateLayout(); break;
        case 1: _t->sinWaveClicked(); break;
        case 2: _t->triWaveClicked(); break;
        case 3: _t->sawWaveClicked(); break;
        case 4: _t->sqrWaveClicked(); break;
        case 5: _t->smoothClicked(); break;
        case 6: _t->normalizeClicked(); break;
        case 7: _t->invertClicked(); break;
        case 8: _t->phaseLeftClicked(); break;
        case 9: _t->phaseRightClicked(); break;
        case 10: _t->loadClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::WatsynView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__WatsynView.data,
    qt_meta_data_lmms__gui__WatsynView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::WatsynView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::WatsynView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__WatsynView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::WatsynView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
