/****************************************************************************
** Meta object code from reading C++ file 'MixerChannelView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/MixerChannelView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MixerChannelView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__MixerChannelView_t {
    QByteArrayData data[16];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__MixerChannelView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__MixerChannelView_t qt_meta_stringdata_lmms__gui__MixerChannelView = {
    {
QT_MOC_LITERAL(0, 0, 27), // "lmms::gui::MixerChannelView"
QT_MOC_LITERAL(1, 28, 13), // "renameChannel"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 10), // "resetColor"
QT_MOC_LITERAL(4, 54, 11), // "selectColor"
QT_MOC_LITERAL(5, 66, 14), // "randomizeColor"
QT_MOC_LITERAL(6, 81, 14), // "renameFinished"
QT_MOC_LITERAL(7, 96, 13), // "removeChannel"
QT_MOC_LITERAL(8, 110, 20), // "removeUnusedChannels"
QT_MOC_LITERAL(9, 131, 15), // "moveChannelLeft"
QT_MOC_LITERAL(10, 147, 16), // "moveChannelRight"
QT_MOC_LITERAL(11, 164, 16), // "backgroundActive"
QT_MOC_LITERAL(12, 181, 17), // "strokeOuterActive"
QT_MOC_LITERAL(13, 199, 19), // "strokeOuterInactive"
QT_MOC_LITERAL(14, 219, 17), // "strokeInnerActive"
QT_MOC_LITERAL(15, 237, 19) // "strokeInnerInactive"

    },
    "lmms::gui::MixerChannelView\0renameChannel\0"
    "\0resetColor\0selectColor\0randomizeColor\0"
    "renameFinished\0removeChannel\0"
    "removeUnusedChannels\0moveChannelLeft\0"
    "moveChannelRight\0backgroundActive\0"
    "strokeOuterActive\0strokeOuterInactive\0"
    "strokeInnerActive\0strokeInnerInactive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__MixerChannelView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       5,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

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

 // properties: name, type, flags
      11, QMetaType::QBrush, 0x00095103,
      12, QMetaType::QColor, 0x00095103,
      13, QMetaType::QColor, 0x00095103,
      14, QMetaType::QColor, 0x00095103,
      15, QMetaType::QColor, 0x00095103,

       0        // eod
};

void lmms::gui::MixerChannelView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MixerChannelView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->renameChannel(); break;
        case 1: _t->resetColor(); break;
        case 2: _t->selectColor(); break;
        case 3: _t->randomizeColor(); break;
        case 4: _t->renameFinished(); break;
        case 5: _t->removeChannel(); break;
        case 6: _t->removeUnusedChannels(); break;
        case 7: _t->moveChannelLeft(); break;
        case 8: _t->moveChannelRight(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MixerChannelView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QBrush*>(_v) = _t->backgroundActive(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->strokeOuterActive(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->strokeOuterInactive(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->strokeInnerActive(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->strokeInnerInactive(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<MixerChannelView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackgroundActive(*reinterpret_cast< QBrush*>(_v)); break;
        case 1: _t->setStrokeOuterActive(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setStrokeOuterInactive(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setStrokeInnerActive(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setStrokeInnerInactive(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::MixerChannelView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__MixerChannelView.data,
    qt_meta_data_lmms__gui__MixerChannelView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::MixerChannelView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::MixerChannelView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__MixerChannelView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::MixerChannelView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
