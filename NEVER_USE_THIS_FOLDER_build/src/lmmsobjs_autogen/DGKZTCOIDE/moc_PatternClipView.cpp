/****************************************************************************
** Meta object code from reading C++ file 'PatternClipView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/PatternClipView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PatternClipView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__PatternClipView_t {
    QByteArrayData data[11];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__PatternClipView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__PatternClipView_t qt_meta_stringdata_lmms__gui__PatternClipView = {
    {
QT_MOC_LITERAL(0, 0, 26), // "lmms::gui::PatternClipView"
QT_MOC_LITERAL(1, 27, 6), // "update"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 19), // "openInPatternEditor"
QT_MOC_LITERAL(4, 55, 9), // "resetName"
QT_MOC_LITERAL(5, 65, 10), // "changeName"
QT_MOC_LITERAL(6, 76, 21), // "emptyTrackHeightRatio"
QT_MOC_LITERAL(7, 98, 15), // "verticalPadding"
QT_MOC_LITERAL(8, 114, 19), // "noteVerticalSpacing"
QT_MOC_LITERAL(9, 134, 21), // "noteHorizontalSpacing"
QT_MOC_LITERAL(10, 156, 9) // "noteColor"

    },
    "lmms::gui::PatternClipView\0update\0\0"
    "openInPatternEditor\0resetName\0changeName\0"
    "emptyTrackHeightRatio\0verticalPadding\0"
    "noteVerticalSpacing\0noteHorizontalSpacing\0"
    "noteColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__PatternClipView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       5,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x09 /* Protected */,
       4,    0,   36,    2, 0x09 /* Protected */,
       5,    0,   37,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::Float, 0x00095003,
       7, QMetaType::Float, 0x00095003,
       8, QMetaType::Float, 0x00095003,
       9, QMetaType::Float, 0x00095003,
      10, QMetaType::QColor, 0x00095003,

       0        // eod
};

void lmms::gui::PatternClipView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatternClipView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->openInPatternEditor(); break;
        case 2: _t->resetName(); break;
        case 3: _t->changeName(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PatternClipView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->m_emptyTrackHeightRatio; break;
        case 1: *reinterpret_cast< float*>(_v) = _t->m_verticalPadding; break;
        case 2: *reinterpret_cast< float*>(_v) = _t->m_noteVerticalSpacing; break;
        case 3: *reinterpret_cast< float*>(_v) = _t->m_noteHorizontalSpacing; break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->m_noteColor; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PatternClipView *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_emptyTrackHeightRatio != *reinterpret_cast< float*>(_v)) {
                _t->m_emptyTrackHeightRatio = *reinterpret_cast< float*>(_v);
            }
            break;
        case 1:
            if (_t->m_verticalPadding != *reinterpret_cast< float*>(_v)) {
                _t->m_verticalPadding = *reinterpret_cast< float*>(_v);
            }
            break;
        case 2:
            if (_t->m_noteVerticalSpacing != *reinterpret_cast< float*>(_v)) {
                _t->m_noteVerticalSpacing = *reinterpret_cast< float*>(_v);
            }
            break;
        case 3:
            if (_t->m_noteHorizontalSpacing != *reinterpret_cast< float*>(_v)) {
                _t->m_noteHorizontalSpacing = *reinterpret_cast< float*>(_v);
            }
            break;
        case 4:
            if (_t->m_noteColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_noteColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::PatternClipView::staticMetaObject = { {
    QMetaObject::SuperData::link<ClipView::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__PatternClipView.data,
    qt_meta_data_lmms__gui__PatternClipView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::PatternClipView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::PatternClipView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__PatternClipView.stringdata0))
        return static_cast<void*>(this);
    return ClipView::qt_metacast(_clname);
}

int lmms::gui::PatternClipView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ClipView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
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
