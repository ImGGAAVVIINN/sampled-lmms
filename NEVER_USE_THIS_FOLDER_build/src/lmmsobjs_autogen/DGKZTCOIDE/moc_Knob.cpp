/****************************************************************************
** Meta object code from reading C++ file 'Knob.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/Knob.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Knob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__Knob_t {
    QByteArrayData data[14];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__Knob_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__Knob_t qt_meta_stringdata_lmms__gui__Knob = {
    {
QT_MOC_LITERAL(0, 0, 15), // "lmms::gui::Knob"
QT_MOC_LITERAL(1, 16, 11), // "innerRadius"
QT_MOC_LITERAL(2, 28, 11), // "outerRadius"
QT_MOC_LITERAL(3, 40, 12), // "centerPointX"
QT_MOC_LITERAL(4, 53, 12), // "centerPointY"
QT_MOC_LITERAL(5, 66, 9), // "lineWidth"
QT_MOC_LITERAL(6, 76, 10), // "outerColor"
QT_MOC_LITERAL(7, 87, 15), // "lineActiveColor"
QT_MOC_LITERAL(8, 103, 17), // "lineInactiveColor"
QT_MOC_LITERAL(9, 121, 14), // "arcActiveColor"
QT_MOC_LITERAL(10, 136, 16), // "arcInactiveColor"
QT_MOC_LITERAL(11, 153, 7), // "knobNum"
QT_MOC_LITERAL(12, 161, 8), // "KnobType"
QT_MOC_LITERAL(13, 170, 9) // "textColor"

    },
    "lmms::gui::Knob\0innerRadius\0outerRadius\0"
    "centerPointX\0centerPointY\0lineWidth\0"
    "outerColor\0lineActiveColor\0lineInactiveColor\0"
    "arcActiveColor\0arcInactiveColor\0knobNum\0"
    "KnobType\0textColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__Knob[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      12,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Float, 0x00095103,
       2, QMetaType::Float, 0x00095103,
       3, QMetaType::Float, 0x00095103,
       4, QMetaType::Float, 0x00095103,
       5, QMetaType::Float, 0x00095103,
       6, QMetaType::QColor, 0x00095103,
       7, QMetaType::QColor, 0x00095003,
       8, QMetaType::QColor, 0x00095003,
       9, QMetaType::QColor, 0x00095003,
      10, QMetaType::QColor, 0x00095003,
      11, 0x80000000 | 12, 0x0009500b,
      13, QMetaType::QColor, 0x00095103,

 // enums: name, alias, flags, count, data

 // enum data: key, value

       0        // eod
};

void lmms::gui::Knob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<Knob *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< float*>(_v) = _t->innerRadius(); break;
        case 1: *reinterpret_cast< float*>(_v) = _t->outerRadius(); break;
        case 2: *reinterpret_cast< float*>(_v) = _t->centerPointX(); break;
        case 3: *reinterpret_cast< float*>(_v) = _t->centerPointY(); break;
        case 4: *reinterpret_cast< float*>(_v) = _t->lineWidth(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->outerColor(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->m_lineActiveColor; break;
        case 7: *reinterpret_cast< QColor*>(_v) = _t->m_lineInactiveColor; break;
        case 8: *reinterpret_cast< QColor*>(_v) = _t->m_arcActiveColor; break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->m_arcInactiveColor; break;
        case 10: *reinterpret_cast< KnobType*>(_v) = _t->knobNum(); break;
        case 11: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<Knob *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setInnerRadius(*reinterpret_cast< float*>(_v)); break;
        case 1: _t->setOuterRadius(*reinterpret_cast< float*>(_v)); break;
        case 2: _t->setCenterPointX(*reinterpret_cast< float*>(_v)); break;
        case 3: _t->setCenterPointY(*reinterpret_cast< float*>(_v)); break;
        case 4: _t->setLineWidth(*reinterpret_cast< float*>(_v)); break;
        case 5: _t->setOuterColor(*reinterpret_cast< QColor*>(_v)); break;
        case 6:
            if (_t->m_lineActiveColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_lineActiveColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 7:
            if (_t->m_lineInactiveColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_lineInactiveColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 8:
            if (_t->m_arcActiveColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_arcActiveColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 9:
            if (_t->m_arcInactiveColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_arcInactiveColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 10: _t->setknobNum(*reinterpret_cast< KnobType*>(_v)); break;
        case 11: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::Knob::staticMetaObject = { {
    QMetaObject::SuperData::link<FloatModelEditorBase::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__Knob.data,
    qt_meta_data_lmms__gui__Knob,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::Knob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::Knob::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__Knob.stringdata0))
        return static_cast<void*>(this);
    return FloatModelEditorBase::qt_metacast(_clname);
}

int lmms::gui::Knob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FloatModelEditorBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 12;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 12;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_lmms__gui__VolumeKnob_t {
    QByteArrayData data[1];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__VolumeKnob_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__VolumeKnob_t qt_meta_stringdata_lmms__gui__VolumeKnob = {
    {
QT_MOC_LITERAL(0, 0, 21) // "lmms::gui::VolumeKnob"

    },
    "lmms::gui::VolumeKnob"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__VolumeKnob[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void lmms::gui::VolumeKnob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::VolumeKnob::staticMetaObject = { {
    QMetaObject::SuperData::link<Knob::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__VolumeKnob.data,
    qt_meta_data_lmms__gui__VolumeKnob,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::VolumeKnob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::VolumeKnob::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__VolumeKnob.stringdata0))
        return static_cast<void*>(this);
    return Knob::qt_metacast(_clname);
}

int lmms::gui::VolumeKnob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Knob::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
