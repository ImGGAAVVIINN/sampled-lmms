/****************************************************************************
** Meta object code from reading C++ file 'InstrumentTrack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/InstrumentTrack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstrumentTrack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__InstrumentTrack_t {
    QByteArrayData data[12];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__InstrumentTrack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__InstrumentTrack_t qt_meta_stringdata_lmms__InstrumentTrack = {
    {
QT_MOC_LITERAL(0, 0, 21), // "lmms::InstrumentTrack"
QT_MOC_LITERAL(1, 22, 17), // "instrumentChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 10), // "midiNoteOn"
QT_MOC_LITERAL(4, 52, 10), // "lmms::Note"
QT_MOC_LITERAL(5, 63, 11), // "midiNoteOff"
QT_MOC_LITERAL(6, 75, 7), // "newNote"
QT_MOC_LITERAL(7, 83, 7), // "endNote"
QT_MOC_LITERAL(8, 91, 14), // "updateBaseNote"
QT_MOC_LITERAL(9, 106, 11), // "updatePitch"
QT_MOC_LITERAL(10, 118, 16), // "updatePitchRange"
QT_MOC_LITERAL(11, 135, 18) // "updateMixerChannel"

    },
    "lmms::InstrumentTrack\0instrumentChanged\0"
    "\0midiNoteOn\0lmms::Note\0midiNoteOff\0"
    "newNote\0endNote\0updateBaseNote\0"
    "updatePitch\0updatePitchRange\0"
    "updateMixerChannel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__InstrumentTrack[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,
       6,    0,   66,    2, 0x06 /* Public */,
       7,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   68,    2, 0x09 /* Protected */,
       9,    0,   69,    2, 0x09 /* Protected */,
      10,    0,   70,    2, 0x09 /* Protected */,
      11,    0,   71,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::InstrumentTrack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InstrumentTrack *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->instrumentChanged(); break;
        case 1: _t->midiNoteOn((*reinterpret_cast< const lmms::Note(*)>(_a[1]))); break;
        case 2: _t->midiNoteOff((*reinterpret_cast< const lmms::Note(*)>(_a[1]))); break;
        case 3: _t->newNote(); break;
        case 4: _t->endNote(); break;
        case 5: _t->updateBaseNote(); break;
        case 6: _t->updatePitch(); break;
        case 7: _t->updatePitchRange(); break;
        case 8: _t->updateMixerChannel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InstrumentTrack::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentTrack::instrumentChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InstrumentTrack::*)(const lmms::Note & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentTrack::midiNoteOn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (InstrumentTrack::*)(const lmms::Note & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentTrack::midiNoteOff)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (InstrumentTrack::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentTrack::newNote)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (InstrumentTrack::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InstrumentTrack::endNote)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::InstrumentTrack::staticMetaObject = { {
    QMetaObject::SuperData::link<Track::staticMetaObject>(),
    qt_meta_stringdata_lmms__InstrumentTrack.data,
    qt_meta_data_lmms__InstrumentTrack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::InstrumentTrack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::InstrumentTrack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__InstrumentTrack.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "MidiEventProcessor"))
        return static_cast< MidiEventProcessor*>(this);
    return Track::qt_metacast(_clname);
}

int lmms::InstrumentTrack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Track::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void lmms::InstrumentTrack::instrumentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::InstrumentTrack::midiNoteOn(const lmms::Note & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void lmms::InstrumentTrack::midiNoteOff(const lmms::Note & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void lmms::InstrumentTrack::newNote()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void lmms::InstrumentTrack::endNote()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
