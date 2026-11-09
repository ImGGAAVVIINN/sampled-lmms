/****************************************************************************
** Meta object code from reading C++ file 'FrequencyShifterControlDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/FrequencyShifter/FrequencyShifterControlDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FrequencyShifterControlDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__FrequencyShifterControlDialog_t {
    QByteArrayData data[3];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__FrequencyShifterControlDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__FrequencyShifterControlDialog_t qt_meta_stringdata_lmms__gui__FrequencyShifterControlDialog = {
    {
QT_MOC_LITERAL(0, 0, 40), // "lmms::gui::FrequencyShifterCo..."
QT_MOC_LITERAL(1, 41, 14), // "showHelpWindow"
QT_MOC_LITERAL(2, 56, 0) // ""

    },
    "lmms::gui::FrequencyShifterControlDialog\0"
    "showHelpWindow\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__FrequencyShifterControlDialog[] = {

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
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void lmms::gui::FrequencyShifterControlDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FrequencyShifterControlDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showHelpWindow(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::FrequencyShifterControlDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControlDialog::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__FrequencyShifterControlDialog.data,
    qt_meta_data_lmms__gui__FrequencyShifterControlDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::FrequencyShifterControlDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::FrequencyShifterControlDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__FrequencyShifterControlDialog.stringdata0))
        return static_cast<void*>(this);
    return EffectControlDialog::qt_metacast(_clname);
}

int lmms::gui::FrequencyShifterControlDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_lmms__gui__FrequencyShifterHelpView_t {
    QByteArrayData data[1];
    char stringdata0[36];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__FrequencyShifterHelpView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__FrequencyShifterHelpView_t qt_meta_stringdata_lmms__gui__FrequencyShifterHelpView = {
    {
QT_MOC_LITERAL(0, 0, 35) // "lmms::gui::FrequencyShifterHe..."

    },
    "lmms::gui::FrequencyShifterHelpView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__FrequencyShifterHelpView[] = {

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

void lmms::gui::FrequencyShifterHelpView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::FrequencyShifterHelpView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__FrequencyShifterHelpView.data,
    qt_meta_data_lmms__gui__FrequencyShifterHelpView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::FrequencyShifterHelpView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::FrequencyShifterHelpView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__FrequencyShifterHelpView.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int lmms::gui::FrequencyShifterHelpView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
