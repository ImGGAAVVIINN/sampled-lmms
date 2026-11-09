/****************************************************************************
** Meta object code from reading C++ file 'InstrumentTrackView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/InstrumentTrackView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstrumentTrackView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__InstrumentTrackView_t {
    QByteArrayData data[19];
    char stringdata0[294];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__InstrumentTrackView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__InstrumentTrackView_t qt_meta_stringdata_lmms__gui__InstrumentTrackView = {
    {
QT_MOC_LITERAL(0, 0, 30), // "lmms::gui::InstrumentTrackView"
QT_MOC_LITERAL(1, 31, 19), // "onInstrumentChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 22), // "toggleInstrumentWindow"
QT_MOC_LITERAL(4, 75, 3), // "_on"
QT_MOC_LITERAL(5, 79, 16), // "toggleMidiCCRack"
QT_MOC_LITERAL(6, 96, 24), // "activityIndicatorPressed"
QT_MOC_LITERAL(7, 121, 25), // "activityIndicatorReleased"
QT_MOC_LITERAL(8, 147, 14), // "midiInSelected"
QT_MOC_LITERAL(9, 162, 15), // "midiOutSelected"
QT_MOC_LITERAL(10, 178, 17), // "midiConfigChanged"
QT_MOC_LITERAL(11, 196, 15), // "assignMixerLine"
QT_MOC_LITERAL(12, 212, 12), // "channelIndex"
QT_MOC_LITERAL(13, 225, 15), // "createMixerLine"
QT_MOC_LITERAL(14, 241, 18), // "handleConfigChange"
QT_MOC_LITERAL(15, 260, 3), // "cls"
QT_MOC_LITERAL(16, 264, 4), // "attr"
QT_MOC_LITERAL(17, 269, 5), // "value"
QT_MOC_LITERAL(18, 275, 18) // "corruptStateUpdate"

    },
    "lmms::gui::InstrumentTrackView\0"
    "onInstrumentChanged\0\0toggleInstrumentWindow\0"
    "_on\0toggleMidiCCRack\0activityIndicatorPressed\0"
    "activityIndicatorReleased\0midiInSelected\0"
    "midiOutSelected\0midiConfigChanged\0"
    "assignMixerLine\0channelIndex\0"
    "createMixerLine\0handleConfigChange\0"
    "cls\0attr\0value\0corruptStateUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__InstrumentTrackView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    0,   78,    2, 0x08 /* Private */,
       6,    0,   79,    2, 0x08 /* Private */,
       7,    0,   80,    2, 0x08 /* Private */,
       8,    0,   81,    2, 0x08 /* Private */,
       9,    0,   82,    2, 0x08 /* Private */,
      10,    0,   83,    2, 0x08 /* Private */,
      11,    1,   84,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    3,   88,    2, 0x08 /* Private */,
      18,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   15,   16,   17,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::InstrumentTrackView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InstrumentTrackView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onInstrumentChanged(); break;
        case 1: _t->toggleInstrumentWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->toggleMidiCCRack(); break;
        case 3: _t->activityIndicatorPressed(); break;
        case 4: _t->activityIndicatorReleased(); break;
        case 5: _t->midiInSelected(); break;
        case 6: _t->midiOutSelected(); break;
        case 7: _t->midiConfigChanged(); break;
        case 8: _t->assignMixerLine((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->createMixerLine(); break;
        case 10: _t->handleConfigChange((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->corruptStateUpdate(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::InstrumentTrackView::staticMetaObject = { {
    QMetaObject::SuperData::link<TrackView::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__InstrumentTrackView.data,
    qt_meta_data_lmms__gui__InstrumentTrackView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::InstrumentTrackView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::InstrumentTrackView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__InstrumentTrackView.stringdata0))
        return static_cast<void*>(this);
    return TrackView::qt_metacast(_clname);
}

int lmms::gui::InstrumentTrackView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TrackView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
