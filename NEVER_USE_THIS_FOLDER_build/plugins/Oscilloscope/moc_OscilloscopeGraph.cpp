/****************************************************************************
** Meta object code from reading C++ file 'OscilloscopeGraph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Oscilloscope/OscilloscopeGraph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OscilloscopeGraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__OscilloscopeGraph_t {
    QByteArrayData data[9];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__OscilloscopeGraph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__OscilloscopeGraph_t qt_meta_stringdata_lmms__gui__OscilloscopeGraph = {
    {
QT_MOC_LITERAL(0, 0, 28), // "lmms::gui::OscilloscopeGraph"
QT_MOC_LITERAL(1, 29, 16), // "changeSampleRate"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 9), // "monoColor"
QT_MOC_LITERAL(4, 57, 9), // "leftColor"
QT_MOC_LITERAL(5, 67, 10), // "rightColor"
QT_MOC_LITERAL(6, 78, 14), // "minorLineColor"
QT_MOC_LITERAL(7, 93, 17), // "clippingLineColor"
QT_MOC_LITERAL(8, 111, 15) // "backgroundColor"

    },
    "lmms::gui::OscilloscopeGraph\0"
    "changeSampleRate\0\0monoColor\0leftColor\0"
    "rightColor\0minorLineColor\0clippingLineColor\0"
    "backgroundColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__OscilloscopeGraph[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       6,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QColor, 0x00095003,
       4, QMetaType::QColor, 0x00095003,
       5, QMetaType::QColor, 0x00095003,
       6, QMetaType::QColor, 0x00095003,
       7, QMetaType::QColor, 0x00095003,
       8, QMetaType::QColor, 0x00095003,

       0        // eod
};

void lmms::gui::OscilloscopeGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OscilloscopeGraph *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changeSampleRate(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<OscilloscopeGraph *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->m_monoColor; break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->m_leftColor; break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->m_rightColor; break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->m_minorLineColor; break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->m_clippingLineColor; break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->m_backgroundColor; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<OscilloscopeGraph *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_monoColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_monoColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 1:
            if (_t->m_leftColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_leftColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 2:
            if (_t->m_rightColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_rightColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 3:
            if (_t->m_minorLineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_minorLineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 4:
            if (_t->m_clippingLineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_clippingLineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 5:
            if (_t->m_backgroundColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_backgroundColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::OscilloscopeGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__OscilloscopeGraph.data,
    qt_meta_data_lmms__gui__OscilloscopeGraph,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::OscilloscopeGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::OscilloscopeGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__OscilloscopeGraph.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::OscilloscopeGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
