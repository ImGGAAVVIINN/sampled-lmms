/****************************************************************************
** Meta object code from reading C++ file 'WaveShaperControls.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/WaveShaper/WaveShaperControls.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WaveShaperControls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__WaveShaperControls_t {
    QByteArrayData data[7];
    char stringdata0[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__WaveShaperControls_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__WaveShaperControls_t qt_meta_stringdata_lmms__WaveShaperControls = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::WaveShaperControls"
QT_MOC_LITERAL(1, 25, 14), // "samplesChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 12), // "resetClicked"
QT_MOC_LITERAL(4, 54, 13), // "smoothClicked"
QT_MOC_LITERAL(5, 68, 13), // "addOneClicked"
QT_MOC_LITERAL(6, 82, 13) // "subOneClicked"

    },
    "lmms::WaveShaperControls\0samplesChanged\0"
    "\0resetClicked\0smoothClicked\0addOneClicked\0"
    "subOneClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__WaveShaperControls[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       3,    0,   44,    2, 0x08 /* Private */,
       4,    0,   45,    2, 0x08 /* Private */,
       5,    0,   46,    2, 0x08 /* Private */,
       6,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::WaveShaperControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WaveShaperControls *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->samplesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->resetClicked(); break;
        case 2: _t->smoothClicked(); break;
        case 3: _t->addOneClicked(); break;
        case 4: _t->subOneClicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::WaveShaperControls::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControls::staticMetaObject>(),
    qt_meta_stringdata_lmms__WaveShaperControls.data,
    qt_meta_data_lmms__WaveShaperControls,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::WaveShaperControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::WaveShaperControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__WaveShaperControls.stringdata0))
        return static_cast<void*>(this);
    return EffectControls::qt_metacast(_clname);
}

int lmms::WaveShaperControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EffectControls::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
