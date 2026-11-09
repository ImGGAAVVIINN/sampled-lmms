/****************************************************************************
** Meta object code from reading C++ file 'TempoSyncKnobModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TempoSyncKnobModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TempoSyncKnobModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__TempoSyncKnobModel_t {
    QByteArrayData data[17];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__TempoSyncKnobModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__TempoSyncKnobModel_t qt_meta_stringdata_lmms__TempoSyncKnobModel = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::TempoSyncKnobModel"
QT_MOC_LITERAL(1, 25, 15), // "syncModeChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 34), // "lmms::TempoSyncKnobModel::Syn..."
QT_MOC_LITERAL(4, 77, 9), // "_new_mode"
QT_MOC_LITERAL(5, 87, 12), // "scaleChanged"
QT_MOC_LITERAL(6, 100, 10), // "_new_scale"
QT_MOC_LITERAL(7, 111, 11), // "disableSync"
QT_MOC_LITERAL(8, 123, 12), // "setTempoSync"
QT_MOC_LITERAL(9, 136, 8), // "SyncMode"
QT_MOC_LITERAL(10, 145, 10), // "_note_type"
QT_MOC_LITERAL(11, 156, 8), // "QAction*"
QT_MOC_LITERAL(12, 165, 5), // "_item"
QT_MOC_LITERAL(13, 171, 22), // "calculateTempoSyncTime"
QT_MOC_LITERAL(14, 194, 11), // "lmms::bpm_t"
QT_MOC_LITERAL(15, 206, 4), // "_bpm"
QT_MOC_LITERAL(16, 211, 12) // "updateCustom"

    },
    "lmms::TempoSyncKnobModel\0syncModeChanged\0"
    "\0lmms::TempoSyncKnobModel::SyncMode\0"
    "_new_mode\0scaleChanged\0_new_scale\0"
    "disableSync\0setTempoSync\0SyncMode\0"
    "_note_type\0QAction*\0_item\0"
    "calculateTempoSyncTime\0lmms::bpm_t\0"
    "_bpm\0updateCustom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__TempoSyncKnobModel[] = {

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
       5,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   55,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x0a /* Public */,
      13,    1,   62,    2, 0x09 /* Protected */,
      16,    0,   65,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Float,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

       0        // eod
};

void lmms::TempoSyncKnobModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TempoSyncKnobModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->syncModeChanged((*reinterpret_cast< lmms::TempoSyncKnobModel::SyncMode(*)>(_a[1]))); break;
        case 1: _t->scaleChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->disableSync(); break;
        case 3: _t->setTempoSync((*reinterpret_cast< SyncMode(*)>(_a[1]))); break;
        case 4: _t->setTempoSync((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: _t->calculateTempoSyncTime((*reinterpret_cast< lmms::bpm_t(*)>(_a[1]))); break;
        case 6: _t->updateCustom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TempoSyncKnobModel::*)(lmms::TempoSyncKnobModel::SyncMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TempoSyncKnobModel::syncModeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TempoSyncKnobModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TempoSyncKnobModel::scaleChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::TempoSyncKnobModel::staticMetaObject = { {
    QMetaObject::SuperData::link<FloatModel::staticMetaObject>(),
    qt_meta_stringdata_lmms__TempoSyncKnobModel.data,
    qt_meta_data_lmms__TempoSyncKnobModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::TempoSyncKnobModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::TempoSyncKnobModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__TempoSyncKnobModel.stringdata0))
        return static_cast<void*>(this);
    return FloatModel::qt_metacast(_clname);
}

int lmms::TempoSyncKnobModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FloatModel::qt_metacall(_c, _id, _a);
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
void lmms::TempoSyncKnobModel::syncModeChanged(lmms::TempoSyncKnobModel::SyncMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lmms::TempoSyncKnobModel::scaleChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
