/****************************************************************************
** Meta object code from reading C++ file 'TrackOperationsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TrackOperationsWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackOperationsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__TrackOperationsWidget_t {
    QByteArrayData data[17];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__TrackOperationsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__TrackOperationsWidget_t qt_meta_stringdata_lmms__gui__TrackOperationsWidget = {
    {
QT_MOC_LITERAL(0, 0, 32), // "lmms::gui::TrackOperationsWidget"
QT_MOC_LITERAL(1, 33, 21), // "trackRemovalScheduled"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 21), // "lmms::gui::TrackView*"
QT_MOC_LITERAL(4, 78, 1), // "t"
QT_MOC_LITERAL(5, 80, 10), // "cloneTrack"
QT_MOC_LITERAL(6, 91, 11), // "removeTrack"
QT_MOC_LITERAL(7, 103, 10), // "updateMenu"
QT_MOC_LITERAL(8, 114, 16), // "selectTrackColor"
QT_MOC_LITERAL(9, 131, 19), // "randomizeTrackColor"
QT_MOC_LITERAL(10, 151, 15), // "resetTrackColor"
QT_MOC_LITERAL(11, 167, 15), // "resetClipColors"
QT_MOC_LITERAL(12, 183, 15), // "toggleRecording"
QT_MOC_LITERAL(13, 199, 2), // "on"
QT_MOC_LITERAL(14, 202, 11), // "recordingOn"
QT_MOC_LITERAL(15, 214, 12), // "recordingOff"
QT_MOC_LITERAL(16, 227, 10) // "clearTrack"

    },
    "lmms::gui::TrackOperationsWidget\0"
    "trackRemovalScheduled\0\0lmms::gui::TrackView*\0"
    "t\0cloneTrack\0removeTrack\0updateMenu\0"
    "selectTrackColor\0randomizeTrackColor\0"
    "resetTrackColor\0resetClipColors\0"
    "toggleRecording\0on\0recordingOn\0"
    "recordingOff\0clearTrack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__TrackOperationsWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    1,   84,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::TrackOperationsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrackOperationsWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->trackRemovalScheduled((*reinterpret_cast< lmms::gui::TrackView*(*)>(_a[1]))); break;
        case 1: _t->cloneTrack(); break;
        case 2: _t->removeTrack(); break;
        case 3: _t->updateMenu(); break;
        case 4: _t->selectTrackColor(); break;
        case 5: _t->randomizeTrackColor(); break;
        case 6: _t->resetTrackColor(); break;
        case 7: _t->resetClipColors(); break;
        case 8: _t->toggleRecording((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->recordingOn(); break;
        case 10: _t->recordingOff(); break;
        case 11: _t->clearTrack(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrackOperationsWidget::*)(lmms::gui::TrackView * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackOperationsWidget::trackRemovalScheduled)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::TrackOperationsWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__TrackOperationsWidget.data,
    qt_meta_data_lmms__gui__TrackOperationsWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::TrackOperationsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::TrackOperationsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__TrackOperationsWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::TrackOperationsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void lmms::gui::TrackOperationsWidget::trackRemovalScheduled(lmms::gui::TrackView * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
