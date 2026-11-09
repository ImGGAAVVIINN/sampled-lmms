/****************************************************************************
** Meta object code from reading C++ file 'ClipView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/ClipView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClipView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__ClipView_t {
    QByteArrayData data[19];
    char stringdata0[242];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__ClipView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__ClipView_t qt_meta_stringdata_lmms__gui__ClipView = {
    {
QT_MOC_LITERAL(0, 0, 19), // "lmms::gui::ClipView"
QT_MOC_LITERAL(1, 20, 5), // "close"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "remove"
QT_MOC_LITERAL(4, 34, 6), // "update"
QT_MOC_LITERAL(5, 41, 11), // "selectColor"
QT_MOC_LITERAL(6, 53, 14), // "randomizeColor"
QT_MOC_LITERAL(7, 68, 10), // "resetColor"
QT_MOC_LITERAL(8, 79, 12), // "updateLength"
QT_MOC_LITERAL(9, 92, 14), // "updatePosition"
QT_MOC_LITERAL(10, 107, 10), // "mutedColor"
QT_MOC_LITERAL(11, 118, 20), // "mutedBackgroundColor"
QT_MOC_LITERAL(12, 139, 13), // "selectedColor"
QT_MOC_LITERAL(13, 153, 9), // "textColor"
QT_MOC_LITERAL(14, 163, 19), // "textBackgroundColor"
QT_MOC_LITERAL(15, 183, 15), // "textShadowColor"
QT_MOC_LITERAL(16, 199, 21), // "patternClipBackground"
QT_MOC_LITERAL(17, 221, 8), // "gradient"
QT_MOC_LITERAL(18, 230, 11) // "markerColor"

    },
    "lmms::gui::ClipView\0close\0\0remove\0"
    "update\0selectColor\0randomizeColor\0"
    "resetColor\0updateLength\0updatePosition\0"
    "mutedColor\0mutedBackgroundColor\0"
    "selectedColor\0textColor\0textBackgroundColor\0"
    "textShadowColor\0patternClipBackground\0"
    "gradient\0markerColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__ClipView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       9,   62, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x09 /* Protected */,
       9,    0,   61,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QColor, 0x00095103,
      11, QMetaType::QColor, 0x00095103,
      12, QMetaType::QColor, 0x00095103,
      13, QMetaType::QColor, 0x00095103,
      14, QMetaType::QColor, 0x00095103,
      15, QMetaType::QColor, 0x00095103,
      16, QMetaType::QColor, 0x00095103,
      17, QMetaType::Bool, 0x00095103,
      18, QMetaType::QColor, 0x00095103,

       0        // eod
};

void lmms::gui::ClipView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClipView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { bool _r = _t->close();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->remove(); break;
        case 2: _t->update(); break;
        case 3: _t->selectColor(); break;
        case 4: _t->randomizeColor(); break;
        case 5: _t->resetColor(); break;
        case 6: _t->updateLength(); break;
        case 7: _t->updatePosition(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ClipView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->mutedColor(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->mutedBackgroundColor(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->selectedColor(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->textBackgroundColor(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->textShadowColor(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->patternClipBackground(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->gradient(); break;
        case 8: *reinterpret_cast< QColor*>(_v) = _t->markerColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ClipView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMutedColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setMutedBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setSelectedColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setTextBackgroundColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setTextShadowColor(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setPatternClipBackground(*reinterpret_cast< QColor*>(_v)); break;
        case 7: _t->setGradient(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setMarkerColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::ClipView::staticMetaObject = { {
    QMetaObject::SuperData::link<selectableObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__ClipView.data,
    qt_meta_data_lmms__gui__ClipView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::ClipView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::ClipView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__ClipView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModelView"))
        return static_cast< ModelView*>(this);
    return selectableObject::qt_metacast(_clname);
}

int lmms::gui::ClipView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = selectableObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
