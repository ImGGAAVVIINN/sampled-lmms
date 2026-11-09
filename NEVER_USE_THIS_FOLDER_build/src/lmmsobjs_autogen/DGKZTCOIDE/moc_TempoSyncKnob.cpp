/****************************************************************************
** Meta object code from reading C++ file 'TempoSyncKnob.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TempoSyncKnob.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TempoSyncKnob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__TempoSyncKnob_t {
    QByteArrayData data[7];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__TempoSyncKnob_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__TempoSyncKnob_t qt_meta_stringdata_lmms__gui__TempoSyncKnob = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::gui::TempoSyncKnob"
QT_MOC_LITERAL(1, 25, 22), // "syncDescriptionChanged"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 16), // "_new_description"
QT_MOC_LITERAL(4, 66, 15), // "syncIconChanged"
QT_MOC_LITERAL(5, 82, 17), // "updateDescAndIcon"
QT_MOC_LITERAL(6, 100, 10) // "showCustom"

    },
    "lmms::gui::TempoSyncKnob\0"
    "syncDescriptionChanged\0\0_new_description\0"
    "syncIconChanged\0updateDescAndIcon\0"
    "showCustom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__TempoSyncKnob[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x09 /* Protected */,
       6,    0,   39,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::TempoSyncKnob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TempoSyncKnob *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->syncDescriptionChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->syncIconChanged(); break;
        case 2: _t->updateDescAndIcon(); break;
        case 3: _t->showCustom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TempoSyncKnob::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TempoSyncKnob::syncDescriptionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TempoSyncKnob::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TempoSyncKnob::syncIconChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::TempoSyncKnob::staticMetaObject = { {
    QMetaObject::SuperData::link<Knob::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__TempoSyncKnob.data,
    qt_meta_data_lmms__gui__TempoSyncKnob,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::TempoSyncKnob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::TempoSyncKnob::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__TempoSyncKnob.stringdata0))
        return static_cast<void*>(this);
    return Knob::qt_metacast(_clname);
}

int lmms::gui::TempoSyncKnob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Knob::qt_metacall(_c, _id, _a);
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
void lmms::gui::TempoSyncKnob::syncDescriptionChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lmms::gui::TempoSyncKnob::syncIconChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
