/****************************************************************************
** Meta object code from reading C++ file 'LOMMControlDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/LOMM/LOMMControlDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LOMMControlDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__LOMMControlDialog_t {
    QByteArrayData data[5];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__LOMMControlDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__LOMMControlDialog_t qt_meta_stringdata_lmms__gui__LOMMControlDialog = {
    {
QT_MOC_LITERAL(0, 0, 28), // "lmms::gui::LOMMControlDialog"
QT_MOC_LITERAL(1, 29, 24), // "updateFeedbackVisibility"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 37), // "updateLowSideUpwardSuppressVi..."
QT_MOC_LITERAL(4, 93, 13) // "updateDisplay"

    },
    "lmms::gui::LOMMControlDialog\0"
    "updateFeedbackVisibility\0\0"
    "updateLowSideUpwardSuppressVisibility\0"
    "updateDisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__LOMMControlDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::LOMMControlDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LOMMControlDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateFeedbackVisibility(); break;
        case 1: _t->updateLowSideUpwardSuppressVisibility(); break;
        case 2: _t->updateDisplay(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::LOMMControlDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControlDialog::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__LOMMControlDialog.data,
    qt_meta_data_lmms__gui__LOMMControlDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::LOMMControlDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::LOMMControlDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__LOMMControlDialog.stringdata0))
        return static_cast<void*>(this);
    return EffectControlDialog::qt_metacast(_clname);
}

int lmms::gui::LOMMControlDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EffectControlDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
