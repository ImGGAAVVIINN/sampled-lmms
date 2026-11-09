/****************************************************************************
** Meta object code from reading C++ file 'LfoController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/LfoController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LfoController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__LfoController_t {
    QByteArrayData data[9];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__LfoController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__LfoController_t qt_meta_stringdata_lmms__LfoController = {
    {
QT_MOC_LITERAL(0, 0, 19), // "lmms::LfoController"
QT_MOC_LITERAL(1, 20, 12), // "createDialog"
QT_MOC_LITERAL(2, 33, 22), // "gui::ControllerDialog*"
QT_MOC_LITERAL(3, 56, 0), // ""
QT_MOC_LITERAL(4, 57, 8), // "QWidget*"
QT_MOC_LITERAL(5, 66, 7), // "_parent"
QT_MOC_LITERAL(6, 74, 11), // "updatePhase"
QT_MOC_LITERAL(7, 86, 20), // "updateSampleFunction"
QT_MOC_LITERAL(8, 107, 14) // "updateDuration"

    },
    "lmms::LfoController\0createDialog\0"
    "gui::ControllerDialog*\0\0QWidget*\0"
    "_parent\0updatePhase\0updateSampleFunction\0"
    "updateDuration"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__LfoController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    3, 0x0a /* Public */,
       6,    0,   37,    3, 0x09 /* Protected */,
       7,    0,   38,    3, 0x09 /* Protected */,
       8,    0,   39,    3, 0x09 /* Protected */,

 // slots: parameters
    0x80000000 | 2, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::LfoController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LfoController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { gui::ControllerDialog* _r = _t->createDialog((*reinterpret_cast< QWidget*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< gui::ControllerDialog**>(_a[0]) = std::move(_r); }  break;
        case 1: _t->updatePhase(); break;
        case 2: _t->updateSampleFunction(); break;
        case 3: _t->updateDuration(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::LfoController::staticMetaObject = { {
    QMetaObject::SuperData::link<Controller::staticMetaObject>(),
    qt_meta_stringdata_lmms__LfoController.data,
    qt_meta_data_lmms__LfoController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::LfoController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::LfoController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__LfoController.stringdata0))
        return static_cast<void*>(this);
    return Controller::qt_metacast(_clname);
}

int lmms::LfoController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Controller::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_lmms__gui__LfoControllerDialog_t {
    QByteArrayData data[3];
    char stringdata0[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__LfoControllerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__LfoControllerDialog_t qt_meta_stringdata_lmms__gui__LfoControllerDialog = {
    {
QT_MOC_LITERAL(0, 0, 30), // "lmms::gui::LfoControllerDialog"
QT_MOC_LITERAL(1, 31, 14), // "askUserDefWave"
QT_MOC_LITERAL(2, 46, 0) // ""

    },
    "lmms::gui::LfoControllerDialog\0"
    "askUserDefWave\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__LfoControllerDialog[] = {

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
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void lmms::gui::LfoControllerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LfoControllerDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->askUserDefWave(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::LfoControllerDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<ControllerDialog::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__LfoControllerDialog.data,
    qt_meta_data_lmms__gui__LfoControllerDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::LfoControllerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::LfoControllerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__LfoControllerDialog.stringdata0))
        return static_cast<void*>(this);
    return ControllerDialog::qt_metacast(_clname);
}

int lmms::gui::LfoControllerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ControllerDialog::qt_metacall(_c, _id, _a);
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
