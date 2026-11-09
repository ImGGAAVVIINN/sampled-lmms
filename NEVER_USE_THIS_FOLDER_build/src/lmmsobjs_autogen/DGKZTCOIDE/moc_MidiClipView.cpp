/****************************************************************************
** Meta object code from reading C++ file 'MidiClipView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/MidiClipView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MidiClipView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__MidiClipView_t {
    QByteArrayData data[16];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__MidiClipView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__MidiClipView_t qt_meta_stringdata_lmms__gui__MidiClipView = {
    {
QT_MOC_LITERAL(0, 0, 23), // "lmms::gui::MidiClipView"
QT_MOC_LITERAL(1, 24, 11), // "getMidiClip"
QT_MOC_LITERAL(2, 36, 15), // "lmms::MidiClip*"
QT_MOC_LITERAL(3, 52, 0), // ""
QT_MOC_LITERAL(4, 53, 6), // "update"
QT_MOC_LITERAL(5, 60, 15), // "openInPianoRoll"
QT_MOC_LITERAL(6, 76, 19), // "setGhostInPianoRoll"
QT_MOC_LITERAL(7, 96, 26), // "setGhostInAutomationEditor"
QT_MOC_LITERAL(8, 123, 9), // "resetName"
QT_MOC_LITERAL(9, 133, 10), // "changeName"
QT_MOC_LITERAL(10, 144, 18), // "transposeSelection"
QT_MOC_LITERAL(11, 163, 21), // "clearNotesOutOfBounds"
QT_MOC_LITERAL(12, 185, 13), // "noteFillColor"
QT_MOC_LITERAL(13, 199, 15), // "noteBorderColor"
QT_MOC_LITERAL(14, 215, 18), // "mutedNoteFillColor"
QT_MOC_LITERAL(15, 234, 20) // "mutedNoteBorderColor"

    },
    "lmms::gui::MidiClipView\0getMidiClip\0"
    "lmms::MidiClip*\0\0update\0openInPianoRoll\0"
    "setGhostInPianoRoll\0setGhostInAutomationEditor\0"
    "resetName\0changeName\0transposeSelection\0"
    "clearNotesOutOfBounds\0noteFillColor\0"
    "noteBorderColor\0mutedNoteFillColor\0"
    "mutedNoteBorderColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__MidiClipView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       4,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    3, 0x0a /* Public */,
       4,    0,   60,    3, 0x0a /* Public */,
       5,    0,   61,    3, 0x09 /* Protected */,
       6,    0,   62,    3, 0x09 /* Protected */,
       7,    0,   63,    3, 0x09 /* Protected */,
       8,    0,   64,    3, 0x09 /* Protected */,
       9,    0,   65,    3, 0x09 /* Protected */,
      10,    0,   66,    3, 0x09 /* Protected */,
      11,    0,   67,    3, 0x09 /* Protected */,

 // slots: parameters
    0x80000000 | 2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QColor, 0x00095103,
      13, QMetaType::QColor, 0x00095103,
      14, QMetaType::QColor, 0x00095103,
      15, QMetaType::QColor, 0x00095103,

       0        // eod
};

void lmms::gui::MidiClipView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MidiClipView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { lmms::MidiClip* _r = _t->getMidiClip();
            if (_a[0]) *reinterpret_cast< lmms::MidiClip**>(_a[0]) = std::move(_r); }  break;
        case 1: _t->update(); break;
        case 2: _t->openInPianoRoll(); break;
        case 3: _t->setGhostInPianoRoll(); break;
        case 4: _t->setGhostInAutomationEditor(); break;
        case 5: _t->resetName(); break;
        case 6: _t->changeName(); break;
        case 7: _t->transposeSelection(); break;
        case 8: _t->clearNotesOutOfBounds(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MidiClipView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->getNoteFillColor(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->getNoteBorderColor(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->getMutedNoteFillColor(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->getMutedNoteBorderColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MidiClipView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setNoteFillColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setNoteBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setMutedNoteFillColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setMutedNoteBorderColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::MidiClipView::staticMetaObject = { {
    QMetaObject::SuperData::link<ClipView::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__MidiClipView.data,
    qt_meta_data_lmms__gui__MidiClipView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::MidiClipView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::MidiClipView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__MidiClipView.stringdata0))
        return static_cast<void*>(this);
    return ClipView::qt_metacast(_clname);
}

int lmms::gui::MidiClipView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ClipView::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
