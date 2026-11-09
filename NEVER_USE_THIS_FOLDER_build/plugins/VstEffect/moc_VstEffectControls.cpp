/****************************************************************************
** Meta object code from reading C++ file 'VstEffectControls.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/VstEffect/VstEffectControls.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VstEffectControls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__VstEffectControls_t {
    QByteArrayData data[12];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__VstEffectControls_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__VstEffectControls_t qt_meta_stringdata_lmms__VstEffectControls = {
    {
QT_MOC_LITERAL(0, 0, 23), // "lmms::VstEffectControls"
QT_MOC_LITERAL(1, 24, 10), // "updateMenu"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 12), // "managePlugin"
QT_MOC_LITERAL(4, 49, 10), // "openPreset"
QT_MOC_LITERAL(5, 60, 10), // "savePreset"
QT_MOC_LITERAL(6, 71, 10), // "rollPreset"
QT_MOC_LITERAL(7, 82, 10), // "rolrPreset"
QT_MOC_LITERAL(8, 93, 9), // "selPreset"
QT_MOC_LITERAL(9, 103, 12), // "setParameter"
QT_MOC_LITERAL(10, 116, 12), // "lmms::Model*"
QT_MOC_LITERAL(11, 129, 6) // "action"

    },
    "lmms::VstEffectControls\0updateMenu\0\0"
    "managePlugin\0openPreset\0savePreset\0"
    "rollPreset\0rolrPreset\0selPreset\0"
    "setParameter\0lmms::Model*\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__VstEffectControls[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x09 /* Protected */,
       3,    0,   55,    2, 0x09 /* Protected */,
       4,    0,   56,    2, 0x09 /* Protected */,
       5,    0,   57,    2, 0x09 /* Protected */,
       6,    0,   58,    2, 0x09 /* Protected */,
       7,    0,   59,    2, 0x09 /* Protected */,
       8,    0,   60,    2, 0x09 /* Protected */,
       9,    1,   61,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void lmms::VstEffectControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VstEffectControls *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateMenu(); break;
        case 1: _t->managePlugin(); break;
        case 2: _t->openPreset(); break;
        case 3: _t->savePreset(); break;
        case 4: _t->rollPreset(); break;
        case 5: _t->rolrPreset(); break;
        case 6: _t->selPreset(); break;
        case 7: _t->setParameter((*reinterpret_cast< lmms::Model*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< lmms::Model* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::VstEffectControls::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControls::staticMetaObject>(),
    qt_meta_stringdata_lmms__VstEffectControls.data,
    qt_meta_data_lmms__VstEffectControls,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::VstEffectControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::VstEffectControls::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__VstEffectControls.stringdata0))
        return static_cast<void*>(this);
    return EffectControls::qt_metacast(_clname);
}

int lmms::VstEffectControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EffectControls::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
struct qt_meta_stringdata_lmms__gui__ManageVSTEffectView_t {
    QByteArrayData data[8];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__ManageVSTEffectView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__ManageVSTEffectView_t qt_meta_stringdata_lmms__gui__ManageVSTEffectView = {
    {
QT_MOC_LITERAL(0, 0, 30), // "lmms::gui::ManageVSTEffectView"
QT_MOC_LITERAL(1, 31, 10), // "syncPlugin"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 20), // "displayAutomatedOnly"
QT_MOC_LITERAL(4, 64, 12), // "setParameter"
QT_MOC_LITERAL(5, 77, 12), // "lmms::Model*"
QT_MOC_LITERAL(6, 90, 6), // "action"
QT_MOC_LITERAL(7, 97, 11) // "closeWindow"

    },
    "lmms::gui::ManageVSTEffectView\0"
    "syncPlugin\0\0displayAutomatedOnly\0"
    "setParameter\0lmms::Model*\0action\0"
    "closeWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__ManageVSTEffectView[] = {

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
       1,    0,   34,    2, 0x09 /* Protected */,
       3,    0,   35,    2, 0x09 /* Protected */,
       4,    1,   36,    2, 0x09 /* Protected */,
       7,    0,   39,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::ManageVSTEffectView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ManageVSTEffectView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->syncPlugin(); break;
        case 1: _t->displayAutomatedOnly(); break;
        case 2: _t->setParameter((*reinterpret_cast< lmms::Model*(*)>(_a[1]))); break;
        case 3: _t->closeWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< lmms::Model* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::ManageVSTEffectView::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__ManageVSTEffectView.data,
    qt_meta_data_lmms__gui__ManageVSTEffectView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::ManageVSTEffectView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::ManageVSTEffectView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__ManageVSTEffectView.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::gui::ManageVSTEffectView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
