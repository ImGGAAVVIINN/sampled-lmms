/****************************************************************************
** Meta object code from reading C++ file 'MidiPort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/MidiPort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MidiPort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__MidiPort_t {
    QByteArrayData data[9];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__MidiPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__MidiPort_t qt_meta_stringdata_lmms__MidiPort = {
    {
QT_MOC_LITERAL(0, 0, 14), // "lmms::MidiPort"
QT_MOC_LITERAL(1, 15, 20), // "readablePortsChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 20), // "writablePortsChanged"
QT_MOC_LITERAL(4, 58, 11), // "modeChanged"
QT_MOC_LITERAL(5, 70, 18), // "updateMidiPortMode"
QT_MOC_LITERAL(6, 89, 19), // "updateReadablePorts"
QT_MOC_LITERAL(7, 109, 19), // "updateWritablePorts"
QT_MOC_LITERAL(8, 129, 19) // "updateOutputProgram"

    },
    "lmms::MidiPort\0readablePortsChanged\0"
    "\0writablePortsChanged\0modeChanged\0"
    "updateMidiPortMode\0updateReadablePorts\0"
    "updateWritablePorts\0updateOutputProgram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__MidiPort[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::MidiPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MidiPort *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->readablePortsChanged(); break;
        case 1: _t->writablePortsChanged(); break;
        case 2: _t->modeChanged(); break;
        case 3: _t->updateMidiPortMode(); break;
        case 4: _t->updateReadablePorts(); break;
        case 5: _t->updateWritablePorts(); break;
        case 6: _t->updateOutputProgram(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MidiPort::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MidiPort::readablePortsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MidiPort::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MidiPort::writablePortsChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MidiPort::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MidiPort::modeChanged)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::MidiPort::staticMetaObject = { {
    QMetaObject::SuperData::link<Model::staticMetaObject>(),
    qt_meta_stringdata_lmms__MidiPort.data,
    qt_meta_data_lmms__MidiPort,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::MidiPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::MidiPort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__MidiPort.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SerializingObject"))
        return static_cast< SerializingObject*>(this);
    return Model::qt_metacast(_clname);
}

int lmms::MidiPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Model::qt_metacall(_c, _id, _a);
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
void lmms::MidiPort::readablePortsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::MidiPort::writablePortsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void lmms::MidiPort::modeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
