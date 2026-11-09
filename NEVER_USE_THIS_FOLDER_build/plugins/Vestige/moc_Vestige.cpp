/****************************************************************************
** Meta object code from reading C++ file 'Vestige.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Vestige/Vestige.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Vestige.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__VestigeInstrument_t {
    QByteArrayData data[10];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__VestigeInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__VestigeInstrument_t qt_meta_stringdata_lmms__VestigeInstrument = {
    {
QT_MOC_LITERAL(0, 0, 23), // "lmms::VestigeInstrument"
QT_MOC_LITERAL(1, 24, 12), // "setParameter"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 12), // "lmms::Model*"
QT_MOC_LITERAL(4, 51, 6), // "action"
QT_MOC_LITERAL(5, 58, 18), // "handleConfigChange"
QT_MOC_LITERAL(6, 77, 3), // "cls"
QT_MOC_LITERAL(7, 81, 4), // "attr"
QT_MOC_LITERAL(8, 86, 5), // "value"
QT_MOC_LITERAL(9, 92, 12) // "reloadPlugin"

    },
    "lmms::VestigeInstrument\0setParameter\0"
    "\0lmms::Model*\0action\0handleConfigChange\0"
    "cls\0attr\0value\0reloadPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__VestigeInstrument[] = {

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
       1,    1,   29,    2, 0x09 /* Protected */,
       5,    3,   32,    2, 0x09 /* Protected */,
       9,    0,   39,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    7,    8,
    QMetaType::Void,

       0        // eod
};

void lmms::VestigeInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VestigeInstrument *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setParameter((*reinterpret_cast< lmms::Model*(*)>(_a[1]))); break;
        case 1: _t->handleConfigChange((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->reloadPlugin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< lmms::Model* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::VestigeInstrument::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__VestigeInstrument.data,
    qt_meta_data_lmms__VestigeInstrument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::VestigeInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::VestigeInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__VestigeInstrument.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::VestigeInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_lmms__gui__ManageVestigeInstrumentView_t {
    QByteArrayData data[8];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__ManageVestigeInstrumentView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__ManageVestigeInstrumentView_t qt_meta_stringdata_lmms__gui__ManageVestigeInstrumentView = {
    {
QT_MOC_LITERAL(0, 0, 38), // "lmms::gui::ManageVestigeInstr..."
QT_MOC_LITERAL(1, 39, 10), // "syncPlugin"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 20), // "displayAutomatedOnly"
QT_MOC_LITERAL(4, 72, 12), // "setParameter"
QT_MOC_LITERAL(5, 85, 12), // "lmms::Model*"
QT_MOC_LITERAL(6, 98, 6), // "action"
QT_MOC_LITERAL(7, 105, 11) // "closeWindow"

    },
    "lmms::gui::ManageVestigeInstrumentView\0"
    "syncPlugin\0\0displayAutomatedOnly\0"
    "setParameter\0lmms::Model*\0action\0"
    "closeWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__ManageVestigeInstrumentView[] = {

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

void lmms::gui::ManageVestigeInstrumentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ManageVestigeInstrumentView *>(_o);
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

QT_INIT_METAOBJECT const QMetaObject lmms::gui::ManageVestigeInstrumentView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__ManageVestigeInstrumentView.data,
    qt_meta_data_lmms__gui__ManageVestigeInstrumentView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::ManageVestigeInstrumentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::ManageVestigeInstrumentView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__ManageVestigeInstrumentView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::ManageVestigeInstrumentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_lmms__gui__VestigeInstrumentView_t {
    QByteArrayData data[12];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__VestigeInstrumentView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__VestigeInstrumentView_t qt_meta_stringdata_lmms__gui__VestigeInstrumentView = {
    {
QT_MOC_LITERAL(0, 0, 32), // "lmms::gui::VestigeInstrumentView"
QT_MOC_LITERAL(1, 33, 10), // "updateMenu"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 10), // "openPlugin"
QT_MOC_LITERAL(4, 56, 12), // "managePlugin"
QT_MOC_LITERAL(5, 69, 10), // "openPreset"
QT_MOC_LITERAL(6, 80, 10), // "savePreset"
QT_MOC_LITERAL(7, 91, 11), // "nextProgram"
QT_MOC_LITERAL(8, 103, 15), // "previousProgram"
QT_MOC_LITERAL(9, 119, 9), // "selPreset"
QT_MOC_LITERAL(10, 129, 9), // "toggleGUI"
QT_MOC_LITERAL(11, 139, 10) // "noteOffAll"

    },
    "lmms::gui::VestigeInstrumentView\0"
    "updateMenu\0\0openPlugin\0managePlugin\0"
    "openPreset\0savePreset\0nextProgram\0"
    "previousProgram\0selPreset\0toggleGUI\0"
    "noteOffAll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__VestigeInstrumentView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x09 /* Protected */,
       3,    0,   65,    2, 0x09 /* Protected */,
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x09 /* Protected */,
       6,    0,   68,    2, 0x09 /* Protected */,
       7,    0,   69,    2, 0x09 /* Protected */,
       8,    0,   70,    2, 0x09 /* Protected */,
       9,    0,   71,    2, 0x09 /* Protected */,
      10,    0,   72,    2, 0x09 /* Protected */,
      11,    0,   73,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::VestigeInstrumentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VestigeInstrumentView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateMenu(); break;
        case 1: _t->openPlugin(); break;
        case 2: _t->managePlugin(); break;
        case 3: _t->openPreset(); break;
        case 4: _t->savePreset(); break;
        case 5: _t->nextProgram(); break;
        case 6: _t->previousProgram(); break;
        case 7: _t->selPreset(); break;
        case 8: _t->toggleGUI(); break;
        case 9: _t->noteOffAll(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::VestigeInstrumentView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__VestigeInstrumentView.data,
    qt_meta_data_lmms__gui__VestigeInstrumentView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::VestigeInstrumentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::VestigeInstrumentView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__VestigeInstrumentView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::VestigeInstrumentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
