/****************************************************************************
** Meta object code from reading C++ file 'PatternStore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/PatternStore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PatternStore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__PatternStore_t {
    QByteArrayData data[6];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__PatternStore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__PatternStore_t qt_meta_stringdata_lmms__PatternStore = {
    {
QT_MOC_LITERAL(0, 0, 18), // "lmms::PatternStore"
QT_MOC_LITERAL(1, 19, 12), // "trackUpdated"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "play"
QT_MOC_LITERAL(4, 38, 4), // "stop"
QT_MOC_LITERAL(5, 43, 14) // "updateComboBox"

    },
    "lmms::PatternStore\0trackUpdated\0\0play\0"
    "stop\0updateComboBox"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__PatternStore[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::PatternStore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatternStore *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->trackUpdated(); break;
        case 1: _t->play(); break;
        case 2: _t->stop(); break;
        case 3: _t->updateComboBox(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PatternStore::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PatternStore::trackUpdated)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::PatternStore::staticMetaObject = { {
    QMetaObject::SuperData::link<TrackContainer::staticMetaObject>(),
    qt_meta_stringdata_lmms__PatternStore.data,
    qt_meta_data_lmms__PatternStore,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::PatternStore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::PatternStore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__PatternStore.stringdata0))
        return static_cast<void*>(this);
    return TrackContainer::qt_metacast(_clname);
}

int lmms::PatternStore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TrackContainer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void lmms::PatternStore::trackUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
