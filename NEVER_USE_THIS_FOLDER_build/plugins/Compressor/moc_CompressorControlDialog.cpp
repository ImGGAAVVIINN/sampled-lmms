/****************************************************************************
** Meta object code from reading C++ file 'CompressorControlDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Compressor/CompressorControlDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CompressorControlDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__CompressorControlDialog_t {
    QByteArrayData data[19];
    char stringdata0[270];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__CompressorControlDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__CompressorControlDialog_t qt_meta_stringdata_lmms__gui__CompressorControlDialog = {
    {
QT_MOC_LITERAL(0, 0, 34), // "lmms::gui::CompressorControlD..."
QT_MOC_LITERAL(1, 35, 13), // "updateDisplay"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 15), // "peakmodeChanged"
QT_MOC_LITERAL(4, 66, 17), // "stereoLinkChanged"
QT_MOC_LITERAL(5, 84, 16), // "lookaheadChanged"
QT_MOC_LITERAL(6, 101, 14), // "limiterChanged"
QT_MOC_LITERAL(7, 116, 14), // "inVolAreaColor"
QT_MOC_LITERAL(8, 131, 10), // "inVolColor"
QT_MOC_LITERAL(9, 142, 15), // "outVolAreaColor"
QT_MOC_LITERAL(10, 158, 11), // "outVolColor"
QT_MOC_LITERAL(11, 170, 18), // "gainReductionColor"
QT_MOC_LITERAL(12, 189, 9), // "kneeColor"
QT_MOC_LITERAL(13, 199, 10), // "kneeColor2"
QT_MOC_LITERAL(14, 210, 11), // "threshColor"
QT_MOC_LITERAL(15, 222, 9), // "textColor"
QT_MOC_LITERAL(16, 232, 10), // "graphColor"
QT_MOC_LITERAL(17, 243, 10), // "resetColor"
QT_MOC_LITERAL(18, 254, 15) // "backgroundColor"

    },
    "lmms::gui::CompressorControlDialog\0"
    "updateDisplay\0\0peakmodeChanged\0"
    "stereoLinkChanged\0lookaheadChanged\0"
    "limiterChanged\0inVolAreaColor\0inVolColor\0"
    "outVolAreaColor\0outVolColor\0"
    "gainReductionColor\0kneeColor\0kneeColor2\0"
    "threshColor\0textColor\0graphColor\0"
    "resetColor\0backgroundColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__CompressorControlDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      12,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QColor, 0x00095003,
       8, QMetaType::QColor, 0x00095003,
       9, QMetaType::QColor, 0x00095003,
      10, QMetaType::QColor, 0x00095003,
      11, QMetaType::QColor, 0x00095003,
      12, QMetaType::QColor, 0x00095003,
      13, QMetaType::QColor, 0x00095003,
      14, QMetaType::QColor, 0x00095003,
      15, QMetaType::QColor, 0x00095003,
      16, QMetaType::QColor, 0x00095003,
      17, QMetaType::QColor, 0x00095003,
      18, QMetaType::QColor, 0x00095003,

       0        // eod
};

void lmms::gui::CompressorControlDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CompressorControlDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateDisplay(); break;
        case 1: _t->peakmodeChanged(); break;
        case 2: _t->stereoLinkChanged(); break;
        case 3: _t->lookaheadChanged(); break;
        case 4: _t->limiterChanged(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CompressorControlDialog *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->m_inVolAreaColor; break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->m_inVolColor; break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->m_outVolAreaColor; break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->m_outVolColor; break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->m_gainReductionColor; break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->m_kneeColor; break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->m_kneeColor2; break;
        case 7: *reinterpret_cast< QColor*>(_v) = _t->m_threshColor; break;
        case 8: *reinterpret_cast< QColor*>(_v) = _t->m_textColor; break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->m_graphColor; break;
        case 10: *reinterpret_cast< QColor*>(_v) = _t->m_resetColor; break;
        case 11: *reinterpret_cast< QColor*>(_v) = _t->m_backgroundColor; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CompressorControlDialog *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_inVolAreaColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_inVolAreaColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 1:
            if (_t->m_inVolColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_inVolColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 2:
            if (_t->m_outVolAreaColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_outVolAreaColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 3:
            if (_t->m_outVolColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_outVolColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 4:
            if (_t->m_gainReductionColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_gainReductionColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 5:
            if (_t->m_kneeColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_kneeColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 6:
            if (_t->m_kneeColor2 != *reinterpret_cast< QColor*>(_v)) {
                _t->m_kneeColor2 = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 7:
            if (_t->m_threshColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_threshColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 8:
            if (_t->m_textColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_textColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 9:
            if (_t->m_graphColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_graphColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 10:
            if (_t->m_resetColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_resetColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 11:
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

QT_INIT_METAOBJECT const QMetaObject lmms::gui::CompressorControlDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<EffectControlDialog::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__CompressorControlDialog.data,
    qt_meta_data_lmms__gui__CompressorControlDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::CompressorControlDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::CompressorControlDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__CompressorControlDialog.stringdata0))
        return static_cast<void*>(this);
    return EffectControlDialog::qt_metacast(_clname);
}

int lmms::gui::CompressorControlDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EffectControlDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
