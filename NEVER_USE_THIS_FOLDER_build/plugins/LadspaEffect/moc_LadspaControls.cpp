/****************************************************************************
** Meta object code from reading C++ file 'LadspaControls.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/LadspaEffect/LadspaControls.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LadspaControls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__LadspaControls_t {
    QByteArrayData data[8];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__LadspaControls_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__LadspaControls_t qt_meta_stringdata_lmms__LadspaControls = {
    {
QT_MOC_LITERAL(0, 0, 20), // "lmms::LadspaControls"
QT_MOC_LITERAL(1, 21, 18), // "effectModelChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 21), // "lmms::LadspaControls*"
QT_MOC_LITERAL(4, 63, 26), // "updateLinkStatesFromGlobal"
QT_MOC_LITERAL(5, 90, 8), // "linkPort"
QT_MOC_LITERAL(6, 99, 5), // "_port"
QT_MOC_LITERAL(7, 105, 6) // "_state"

    },
    "lmms::LadspaControls\0effectModelChanged\0"
    "\0lmms::LadspaControls*\0"
    "updateLinkStatesFromGlobal\0linkPort\0"
    "_port\0_state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__LadspaControls[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x09 /* Protected */,
       5,    2,   33,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    6,    7,

       0        // eod
};

void lmms::LadspaControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LadspaControls *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->effectModelChanged((*reinterpret_cast< lmms::LadspaControls*(*)>(_a[1]))); break;
        case 1: _t->updateLinkStatesFromGlobal(); break;
        case 2: _t->linkPort((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< lmms::LadspaControls* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LadspaControls::*)(lmms::LadspaControls * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LadspaControls::effectModelChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::LadspaControls::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControls::staticMetaObject>(),
    qt_meta_stringdata_lmms__LadspaControls.data,
    qt_meta_data_lmms__LadspaControls,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::LadspaControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::LadspaControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__LadspaControls.stringdata0))
        return static_cast<void*>(this);
    return EffectControls::qt_metacast(_clname);
}

int lmms::LadspaControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EffectControls::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void lmms::LadspaControls::effectModelChanged(lmms::LadspaControls * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
