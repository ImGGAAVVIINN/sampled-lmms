/****************************************************************************
** Meta object code from reading C++ file 'EnvelopeGraph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/EnvelopeGraph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EnvelopeGraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__EnvelopeGraph_t {
    QByteArrayData data[5];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__EnvelopeGraph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__EnvelopeGraph_t qt_meta_stringdata_lmms__gui__EnvelopeGraph = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::gui::EnvelopeGraph"
QT_MOC_LITERAL(1, 25, 13), // "noAmountColor"
QT_MOC_LITERAL(2, 39, 15), // "fullAmountColor"
QT_MOC_LITERAL(3, 55, 15), // "markerFillColor"
QT_MOC_LITERAL(4, 71, 18) // "markerOutlineColor"

    },
    "lmms::gui::EnvelopeGraph\0noAmountColor\0"
    "fullAmountColor\0markerFillColor\0"
    "markerOutlineColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__EnvelopeGraph[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QColor, 0x00095003,
       2, QMetaType::QColor, 0x00095003,
       3, QMetaType::QColor, 0x00095003,
       4, QMetaType::QColor, 0x00095003,

       0        // eod
};

void lmms::gui::EnvelopeGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<EnvelopeGraph *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->m_noAmountColor; break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->m_fullAmountColor; break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->m_markerFillColor; break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->m_markerOutlineColor; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<EnvelopeGraph *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_noAmountColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_noAmountColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 1:
            if (_t->m_fullAmountColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_fullAmountColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 2:
            if (_t->m_markerFillColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_markerFillColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 3:
            if (_t->m_markerOutlineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_markerOutlineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
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

QT_INIT_METAOBJECT const QMetaObject lmms::gui::EnvelopeGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__EnvelopeGraph.data,
    qt_meta_data_lmms__gui__EnvelopeGraph,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::EnvelopeGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::EnvelopeGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__EnvelopeGraph.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModelView"))
        return static_cast< ModelView*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::EnvelopeGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
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
