/****************************************************************************
** Meta object code from reading C++ file 'VstEffectControlDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/VstEffect/VstEffectControlDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VstEffectControlDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__VstEffectControlDialog_t {
    QByteArrayData data[4];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__VstEffectControlDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__VstEffectControlDialog_t qt_meta_stringdata_lmms__gui__VstEffectControlDialog = {
    {
QT_MOC_LITERAL(0, 0, 33), // "lmms::gui::VstEffectControlDi..."
QT_MOC_LITERAL(1, 34, 14), // "togglePluginUI"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 7) // "checked"

    },
    "lmms::gui::VstEffectControlDialog\0"
    "togglePluginUI\0\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__VstEffectControlDialog[] = {

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
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void lmms::gui::VstEffectControlDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VstEffectControlDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->togglePluginUI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::VstEffectControlDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControlDialog::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__VstEffectControlDialog.data,
    qt_meta_data_lmms__gui__VstEffectControlDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::VstEffectControlDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::VstEffectControlDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__VstEffectControlDialog.stringdata0))
        return static_cast<void*>(this);
    return EffectControlDialog::qt_metacast(_clname);
}

int lmms::gui::VstEffectControlDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EffectControlDialog::qt_metacall(_c, _id, _a);
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
