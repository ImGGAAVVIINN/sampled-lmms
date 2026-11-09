/****************************************************************************
** Meta object code from reading C++ file 'AutomationClip.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/AutomationClip.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AutomationClip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__AutomationClip_t {
    QByteArrayData data[11];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__AutomationClip_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__AutomationClip_t qt_meta_stringdata_lmms__AutomationClip = {
    {
QT_MOC_LITERAL(0, 0, 20), // "lmms::AutomationClip"
QT_MOC_LITERAL(1, 21, 5), // "clear"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "objectDestroyed"
QT_MOC_LITERAL(4, 44, 13), // "lmms::jo_id_t"
QT_MOC_LITERAL(5, 58, 5), // "flipY"
QT_MOC_LITERAL(6, 64, 3), // "min"
QT_MOC_LITERAL(7, 68, 3), // "max"
QT_MOC_LITERAL(8, 72, 5), // "flipX"
QT_MOC_LITERAL(9, 78, 5), // "start"
QT_MOC_LITERAL(10, 84, 3) // "end"

    },
    "lmms::AutomationClip\0clear\0\0objectDestroyed\0"
    "lmms::jo_id_t\0flipY\0min\0max\0flipX\0"
    "start\0end"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__AutomationClip[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x0a /* Public */,
       5,    2,   53,    2, 0x0a /* Public */,
       5,    0,   58,    2, 0x0a /* Public */,
       8,    2,   59,    2, 0x0a /* Public */,
       8,    1,   64,    2, 0x2a /* Public | MethodCloned */,
       8,    0,   67,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,

       0        // eod
};

void lmms::AutomationClip::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AutomationClip *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: _t->objectDestroyed((*reinterpret_cast< lmms::jo_id_t(*)>(_a[1]))); break;
        case 2: _t->flipY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->flipY(); break;
        case 4: _t->flipX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->flipX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->flipX(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::AutomationClip::staticMetaObject = { {
    QMetaObject::SuperData::link<Clip::staticMetaObject>(),
    qt_meta_stringdata_lmms__AutomationClip.data,
    qt_meta_data_lmms__AutomationClip,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::AutomationClip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::AutomationClip::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__AutomationClip.stringdata0))
        return static_cast<void*>(this);
    return Clip::qt_metacast(_clname);
}

int lmms::AutomationClip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Clip::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
