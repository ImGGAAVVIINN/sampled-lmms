/****************************************************************************
** Meta object code from reading C++ file 'SampleClip.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/SampleClip.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SampleClip.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__SampleClip_t {
    QByteArrayData data[10];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__SampleClip_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__SampleClip_t qt_meta_stringdata_lmms__SampleClip = {
    {
QT_MOC_LITERAL(0, 0, 16), // "lmms::SampleClip"
QT_MOC_LITERAL(1, 17, 13), // "sampleChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 11), // "wasReversed"
QT_MOC_LITERAL(4, 44, 13), // "setSampleFile"
QT_MOC_LITERAL(5, 58, 2), // "sf"
QT_MOC_LITERAL(6, 61, 12), // "toggleRecord"
QT_MOC_LITERAL(7, 74, 23), // "playbackPositionChanged"
QT_MOC_LITERAL(8, 98, 16), // "updateTrackClips"
QT_MOC_LITERAL(9, 115, 12) // "tempoChanged"

    },
    "lmms::SampleClip\0sampleChanged\0\0"
    "wasReversed\0setSampleFile\0sf\0toggleRecord\0"
    "playbackPositionChanged\0updateTrackClips\0"
    "tempoChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__SampleClip[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   51,    2, 0x0a /* Public */,
       6,    0,   54,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::SampleClip::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SampleClip *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sampleChanged(); break;
        case 1: _t->wasReversed(); break;
        case 2: _t->setSampleFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->toggleRecord(); break;
        case 4: _t->playbackPositionChanged(); break;
        case 5: _t->updateTrackClips(); break;
        case 6: _t->tempoChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SampleClip::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SampleClip::sampleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SampleClip::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SampleClip::wasReversed)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::SampleClip::staticMetaObject = { {
    QMetaObject::SuperData::link<Clip::staticMetaObject>(),
    qt_meta_stringdata_lmms__SampleClip.data,
    qt_meta_data_lmms__SampleClip,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::SampleClip::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::SampleClip::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__SampleClip.stringdata0))
        return static_cast<void*>(this);
    return Clip::qt_metacast(_clname);
}

int lmms::SampleClip::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Clip::qt_metacall(_c, _id, _a);
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
void lmms::SampleClip::sampleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::SampleClip::wasReversed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
