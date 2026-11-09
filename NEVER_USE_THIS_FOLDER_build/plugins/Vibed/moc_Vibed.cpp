/****************************************************************************
** Meta object code from reading C++ file 'Vibed.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Vibed/Vibed.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Vibed.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__Vibed_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__Vibed_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__Vibed_t qt_meta_stringdata_lmms__Vibed = {
    {
QT_MOC_LITERAL(0, 0, 11) // "lmms::Vibed"

    },
    "lmms::Vibed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__Vibed[] = {

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

void lmms::Vibed::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::Vibed::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__Vibed.data,
    qt_meta_data_lmms__Vibed,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::Vibed::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::Vibed::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__Vibed.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::Vibed::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_lmms__gui__VibedView_t {
    QByteArrayData data[14];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__VibedView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__VibedView_t qt_meta_stringdata_lmms__gui__VibedView = {
    {
QT_MOC_LITERAL(0, 0, 20), // "lmms::gui::VibedView"
QT_MOC_LITERAL(1, 21, 10), // "showString"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "str"
QT_MOC_LITERAL(4, 37, 16), // "contextMenuEvent"
QT_MOC_LITERAL(5, 54, 18), // "QContextMenuEvent*"
QT_MOC_LITERAL(6, 73, 14), // "sinWaveClicked"
QT_MOC_LITERAL(7, 88, 19), // "triangleWaveClicked"
QT_MOC_LITERAL(8, 108, 14), // "sawWaveClicked"
QT_MOC_LITERAL(9, 123, 14), // "sqrWaveClicked"
QT_MOC_LITERAL(10, 138, 16), // "noiseWaveClicked"
QT_MOC_LITERAL(11, 155, 14), // "usrWaveClicked"
QT_MOC_LITERAL(12, 170, 13), // "smoothClicked"
QT_MOC_LITERAL(13, 184, 16) // "normalizeClicked"

    },
    "lmms::gui::VibedView\0showString\0\0str\0"
    "contextMenuEvent\0QContextMenuEvent*\0"
    "sinWaveClicked\0triangleWaveClicked\0"
    "sawWaveClicked\0sqrWaveClicked\0"
    "noiseWaveClicked\0usrWaveClicked\0"
    "smoothClicked\0normalizeClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__VibedView[] = {

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
       1,    1,   64,    2, 0x0a /* Public */,
       4,    1,   67,    2, 0x0a /* Public */,
       6,    0,   70,    2, 0x09 /* Protected */,
       7,    0,   71,    2, 0x09 /* Protected */,
       8,    0,   72,    2, 0x09 /* Protected */,
       9,    0,   73,    2, 0x09 /* Protected */,
      10,    0,   74,    2, 0x09 /* Protected */,
      11,    0,   75,    2, 0x09 /* Protected */,
      12,    0,   76,    2, 0x09 /* Protected */,
      13,    0,   77,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
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

void lmms::gui::VibedView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VibedView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showString((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->contextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        case 2: _t->sinWaveClicked(); break;
        case 3: _t->triangleWaveClicked(); break;
        case 4: _t->sawWaveClicked(); break;
        case 5: _t->sqrWaveClicked(); break;
        case 6: _t->noiseWaveClicked(); break;
        case 7: _t->usrWaveClicked(); break;
        case 8: _t->smoothClicked(); break;
        case 9: _t->normalizeClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::VibedView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__VibedView.data,
    qt_meta_data_lmms__gui__VibedView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::VibedView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::VibedView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__VibedView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::VibedView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
