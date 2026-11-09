/****************************************************************************
** Meta object code from reading C++ file 'AudioEngine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/AudioEngine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__AudioEngine_t {
    QByteArrayData data[7];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__AudioEngine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__AudioEngine_t qt_meta_stringdata_lmms__AudioEngine = {
    {
QT_MOC_LITERAL(0, 0, 17), // "lmms::AudioEngine"
QT_MOC_LITERAL(1, 18, 22), // "qualitySettingsChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17), // "sampleRateChanged"
QT_MOC_LITERAL(4, 60, 15), // "nextAudioBuffer"
QT_MOC_LITERAL(5, 76, 24), // "const lmms::SampleFrame*"
QT_MOC_LITERAL(6, 101, 6) // "buffer"

    },
    "lmms::AudioEngine\0qualitySettingsChanged\0"
    "\0sampleRateChanged\0nextAudioBuffer\0"
    "const lmms::SampleFrame*\0buffer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__AudioEngine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    1,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void lmms::AudioEngine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioEngine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->qualitySettingsChanged(); break;
        case 1: _t->sampleRateChanged(); break;
        case 2: _t->nextAudioBuffer((*reinterpret_cast< const lmms::SampleFrame*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AudioEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioEngine::qualitySettingsChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AudioEngine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioEngine::sampleRateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AudioEngine::*)(const lmms::SampleFrame * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AudioEngine::nextAudioBuffer)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::AudioEngine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__AudioEngine.data,
    qt_meta_data_lmms__AudioEngine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::AudioEngine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::AudioEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__AudioEngine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::AudioEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void lmms::AudioEngine::qualitySettingsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::AudioEngine::sampleRateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void lmms::AudioEngine::nextAudioBuffer(const lmms::SampleFrame * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
