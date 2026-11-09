/****************************************************************************
** Meta object code from reading C++ file 'Song.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/Song.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Song.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__Song_t {
    QByteArrayData data[57];
    char stringdata0[767];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__Song_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__Song_t qt_meta_stringdata_lmms__Song = {
    {
QT_MOC_LITERAL(0, 0, 10), // "lmms::Song"
QT_MOC_LITERAL(1, 11, 13), // "projectLoaded"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "playbackStateChanged"
QT_MOC_LITERAL(4, 47, 20), // "selectedTrackChanged"
QT_MOC_LITERAL(5, 68, 6), // "Track*"
QT_MOC_LITERAL(6, 75, 5), // "track"
QT_MOC_LITERAL(7, 81, 17), // "recordModeChanged"
QT_MOC_LITERAL(8, 99, 10), // "RecordMode"
QT_MOC_LITERAL(9, 110, 4), // "mode"
QT_MOC_LITERAL(10, 115, 18), // "captureUnavailable"
QT_MOC_LITERAL(11, 134, 22), // "playbackPositionJumped"
QT_MOC_LITERAL(12, 157, 13), // "lengthChanged"
QT_MOC_LITERAL(13, 171, 4), // "bars"
QT_MOC_LITERAL(14, 176, 12), // "tempoChanged"
QT_MOC_LITERAL(15, 189, 11), // "lmms::bpm_t"
QT_MOC_LITERAL(16, 201, 6), // "newBPM"
QT_MOC_LITERAL(17, 208, 20), // "timeSignatureChanged"
QT_MOC_LITERAL(18, 229, 14), // "oldTicksPerBar"
QT_MOC_LITERAL(19, 244, 11), // "ticksPerBar"
QT_MOC_LITERAL(20, 256, 15), // "controllerAdded"
QT_MOC_LITERAL(21, 272, 17), // "lmms::Controller*"
QT_MOC_LITERAL(22, 290, 17), // "controllerRemoved"
QT_MOC_LITERAL(23, 308, 7), // "stopped"
QT_MOC_LITERAL(24, 316, 8), // "modified"
QT_MOC_LITERAL(25, 325, 22), // "projectFileNameChanged"
QT_MOC_LITERAL(26, 348, 16), // "scaleListChanged"
QT_MOC_LITERAL(27, 365, 5), // "index"
QT_MOC_LITERAL(28, 371, 17), // "keymapListChanged"
QT_MOC_LITERAL(29, 389, 8), // "playSong"
QT_MOC_LITERAL(30, 398, 13), // "playAndRecord"
QT_MOC_LITERAL(31, 412, 11), // "playPattern"
QT_MOC_LITERAL(32, 424, 12), // "playMidiClip"
QT_MOC_LITERAL(33, 437, 21), // "const lmms::MidiClip*"
QT_MOC_LITERAL(34, 459, 14), // "midiClipToPlay"
QT_MOC_LITERAL(35, 474, 4), // "loop"
QT_MOC_LITERAL(36, 479, 11), // "togglePause"
QT_MOC_LITERAL(37, 491, 4), // "stop"
QT_MOC_LITERAL(38, 496, 11), // "startExport"
QT_MOC_LITERAL(39, 508, 10), // "stopExport"
QT_MOC_LITERAL(40, 519, 11), // "setModified"
QT_MOC_LITERAL(41, 531, 12), // "clearProject"
QT_MOC_LITERAL(42, 544, 15), // "addPatternTrack"
QT_MOC_LITERAL(43, 560, 19), // "recordSelectedTrack"
QT_MOC_LITERAL(44, 580, 14), // "recordNewTrack"
QT_MOC_LITERAL(45, 595, 6), // "record"
QT_MOC_LITERAL(46, 602, 9), // "insertBar"
QT_MOC_LITERAL(47, 612, 9), // "removeBar"
QT_MOC_LITERAL(48, 622, 14), // "addSampleTrack"
QT_MOC_LITERAL(49, 637, 18), // "addAutomationTrack"
QT_MOC_LITERAL(50, 656, 8), // "setTempo"
QT_MOC_LITERAL(51, 665, 16), // "setTimeSignature"
QT_MOC_LITERAL(52, 682, 19), // "masterVolumeChanged"
QT_MOC_LITERAL(53, 702, 21), // "savePlayStartPosition"
QT_MOC_LITERAL(54, 724, 19), // "updateFramesPerTick"
QT_MOC_LITERAL(55, 744, 8), // "NewTrack"
QT_MOC_LITERAL(56, 753, 13) // "SelectedTrack"

    },
    "lmms::Song\0projectLoaded\0\0"
    "playbackStateChanged\0selectedTrackChanged\0"
    "Track*\0track\0recordModeChanged\0"
    "RecordMode\0mode\0captureUnavailable\0"
    "playbackPositionJumped\0lengthChanged\0"
    "bars\0tempoChanged\0lmms::bpm_t\0newBPM\0"
    "timeSignatureChanged\0oldTicksPerBar\0"
    "ticksPerBar\0controllerAdded\0"
    "lmms::Controller*\0controllerRemoved\0"
    "stopped\0modified\0projectFileNameChanged\0"
    "scaleListChanged\0index\0keymapListChanged\0"
    "playSong\0playAndRecord\0playPattern\0"
    "playMidiClip\0const lmms::MidiClip*\0"
    "midiClipToPlay\0loop\0togglePause\0stop\0"
    "startExport\0stopExport\0setModified\0"
    "clearProject\0addPatternTrack\0"
    "recordSelectedTrack\0recordNewTrack\0"
    "record\0insertBar\0removeBar\0addSampleTrack\0"
    "addAutomationTrack\0setTempo\0"
    "setTimeSignature\0masterVolumeChanged\0"
    "savePlayStartPosition\0updateFramesPerTick\0"
    "NewTrack\0SelectedTrack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__Song[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       1,  280, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  214,    2, 0x06 /* Public */,
       3,    0,  215,    2, 0x06 /* Public */,
       4,    1,  216,    2, 0x06 /* Public */,
       7,    1,  219,    2, 0x06 /* Public */,
      10,    0,  222,    2, 0x06 /* Public */,
      11,    0,  223,    2, 0x06 /* Public */,
      12,    1,  224,    2, 0x06 /* Public */,
      14,    1,  227,    2, 0x06 /* Public */,
      17,    2,  230,    2, 0x06 /* Public */,
      20,    1,  235,    2, 0x06 /* Public */,
      22,    1,  238,    2, 0x06 /* Public */,
      23,    0,  241,    2, 0x06 /* Public */,
      24,    0,  242,    2, 0x06 /* Public */,
      25,    0,  243,    2, 0x06 /* Public */,
      26,    1,  244,    2, 0x06 /* Public */,
      28,    1,  247,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      29,    0,  250,    2, 0x0a /* Public */,
      30,    0,  251,    2, 0x0a /* Public */,
      31,    0,  252,    2, 0x0a /* Public */,
      32,    2,  253,    2, 0x0a /* Public */,
      32,    1,  258,    2, 0x2a /* Public | MethodCloned */,
      36,    0,  261,    2, 0x0a /* Public */,
      37,    0,  262,    2, 0x0a /* Public */,
      38,    0,  263,    2, 0x0a /* Public */,
      39,    0,  264,    2, 0x0a /* Public */,
      40,    0,  265,    2, 0x0a /* Public */,
      41,    0,  266,    2, 0x0a /* Public */,
      42,    0,  267,    2, 0x0a /* Public */,
      43,    0,  268,    2, 0x0a /* Public */,
      44,    0,  269,    2, 0x0a /* Public */,
      45,    0,  270,    2, 0x0a /* Public */,
      46,    0,  271,    2, 0x08 /* Private */,
      47,    0,  272,    2, 0x08 /* Private */,
      48,    0,  273,    2, 0x08 /* Private */,
      49,    0,  274,    2, 0x08 /* Private */,
      50,    0,  275,    2, 0x08 /* Private */,
      51,    0,  276,    2, 0x08 /* Private */,
      52,    0,  277,    2, 0x08 /* Private */,
      53,    0,  278,    2, 0x08 /* Private */,
      54,    0,  279,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   18,   19,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Int,   27,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 33, QMetaType::Bool,   34,   35,
    QMetaType::Void, 0x80000000 | 33,   34,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
       8,    8, 0x2,    2,  285,

 // enum data: key, value
      55, uint(lmms::Song::RecordMode::NewTrack),
      56, uint(lmms::Song::RecordMode::SelectedTrack),

       0        // eod
};

void lmms::Song::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Song *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->projectLoaded(); break;
        case 1: _t->playbackStateChanged(); break;
        case 2: _t->selectedTrackChanged((*reinterpret_cast< Track*(*)>(_a[1]))); break;
        case 3: _t->recordModeChanged((*reinterpret_cast< RecordMode(*)>(_a[1]))); break;
        case 4: _t->captureUnavailable(); break;
        case 5: _t->playbackPositionJumped(); break;
        case 6: _t->lengthChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->tempoChanged((*reinterpret_cast< lmms::bpm_t(*)>(_a[1]))); break;
        case 8: _t->timeSignatureChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->controllerAdded((*reinterpret_cast< lmms::Controller*(*)>(_a[1]))); break;
        case 10: _t->controllerRemoved((*reinterpret_cast< lmms::Controller*(*)>(_a[1]))); break;
        case 11: _t->stopped(); break;
        case 12: _t->modified(); break;
        case 13: _t->projectFileNameChanged(); break;
        case 14: _t->scaleListChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->keymapListChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->playSong(); break;
        case 17: _t->playAndRecord(); break;
        case 18: _t->playPattern(); break;
        case 19: _t->playMidiClip((*reinterpret_cast< const lmms::MidiClip*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 20: _t->playMidiClip((*reinterpret_cast< const lmms::MidiClip*(*)>(_a[1]))); break;
        case 21: _t->togglePause(); break;
        case 22: _t->stop(); break;
        case 23: _t->startExport(); break;
        case 24: _t->stopExport(); break;
        case 25: _t->setModified(); break;
        case 26: _t->clearProject(); break;
        case 27: _t->addPatternTrack(); break;
        case 28: _t->recordSelectedTrack(); break;
        case 29: _t->recordNewTrack(); break;
        case 30: _t->record(); break;
        case 31: _t->insertBar(); break;
        case 32: _t->removeBar(); break;
        case 33: _t->addSampleTrack(); break;
        case 34: _t->addAutomationTrack(); break;
        case 35: _t->setTempo(); break;
        case 36: _t->setTimeSignature(); break;
        case 37: _t->masterVolumeChanged(); break;
        case 38: _t->savePlayStartPosition(); break;
        case 39: _t->updateFramesPerTick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Track* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< lmms::Controller* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< lmms::Controller* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::projectLoaded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::playbackStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Song::*)(Track * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::selectedTrackChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Song::*)(RecordMode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::recordModeChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::captureUnavailable)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::playbackPositionJumped)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Song::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::lengthChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Song::*)(lmms::bpm_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::tempoChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Song::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::timeSignatureChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Song::*)(lmms::Controller * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::controllerAdded)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Song::*)(lmms::Controller * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::controllerRemoved)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::stopped)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::modified)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (Song::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::projectFileNameChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (Song::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::scaleListChanged)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (Song::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Song::keymapListChanged)) {
                *result = 15;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::Song::staticMetaObject = { {
    QMetaObject::SuperData::link<TrackContainer::staticMetaObject>(),
    qt_meta_stringdata_lmms__Song.data,
    qt_meta_data_lmms__Song,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::Song::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::Song::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__Song.stringdata0))
        return static_cast<void*>(this);
    return TrackContainer::qt_metacast(_clname);
}

int lmms::Song::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TrackContainer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void lmms::Song::projectLoaded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::Song::playbackStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void lmms::Song::selectedTrackChanged(Track * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void lmms::Song::recordModeChanged(RecordMode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void lmms::Song::captureUnavailable()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void lmms::Song::playbackPositionJumped()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void lmms::Song::lengthChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void lmms::Song::tempoChanged(lmms::bpm_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void lmms::Song::timeSignatureChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void lmms::Song::controllerAdded(lmms::Controller * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void lmms::Song::controllerRemoved(lmms::Controller * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void lmms::Song::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void lmms::Song::modified()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void lmms::Song::projectFileNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void lmms::Song::scaleListChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void lmms::Song::keymapListChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
