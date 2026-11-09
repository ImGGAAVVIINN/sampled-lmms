/****************************************************************************
** Meta object code from reading C++ file 'LmmsPalette.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/LmmsPalette.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LmmsPalette.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__LmmsPalette_t {
    QByteArrayData data[11];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__LmmsPalette_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__LmmsPalette_t qt_meta_stringdata_lmms__gui__LmmsPalette = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::gui::LmmsPalette"
QT_MOC_LITERAL(1, 23, 10), // "background"
QT_MOC_LITERAL(2, 34, 10), // "windowText"
QT_MOC_LITERAL(3, 45, 4), // "base"
QT_MOC_LITERAL(4, 50, 4), // "text"
QT_MOC_LITERAL(5, 55, 6), // "button"
QT_MOC_LITERAL(6, 62, 6), // "shadow"
QT_MOC_LITERAL(7, 69, 10), // "buttonText"
QT_MOC_LITERAL(8, 80, 10), // "brightText"
QT_MOC_LITERAL(9, 91, 9), // "highlight"
QT_MOC_LITERAL(10, 101, 15) // "highlightedText"

    },
    "lmms::gui::LmmsPalette\0background\0"
    "windowText\0base\0text\0button\0shadow\0"
    "buttonText\0brightText\0highlight\0"
    "highlightedText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__LmmsPalette[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      10,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QColor, 0x00095103,
       2, QMetaType::QColor, 0x00095103,
       3, QMetaType::QColor, 0x00095103,
       4, QMetaType::QColor, 0x00095103,
       5, QMetaType::QColor, 0x00095103,
       6, QMetaType::QColor, 0x00095103,
       7, QMetaType::QColor, 0x00095103,
       8, QMetaType::QColor, 0x00095103,
       9, QMetaType::QColor, 0x00095103,
      10, QMetaType::QColor, 0x00095103,

       0        // eod
};

void lmms::gui::LmmsPalette::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<LmmsPalette *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->background(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->windowText(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->base(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->text(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->button(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->shadow(); break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->buttonText(); break;
        case 7: *reinterpret_cast< QColor*>(_v) = _t->brightText(); break;
        case 8: *reinterpret_cast< QColor*>(_v) = _t->highlight(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->highlightedText(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<LmmsPalette *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackground(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setWindowText(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setBase(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setText(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setButton(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setShadow(*reinterpret_cast< QColor*>(_v)); break;
        case 6: _t->setButtonText(*reinterpret_cast< QColor*>(_v)); break;
        case 7: _t->setBrightText(*reinterpret_cast< QColor*>(_v)); break;
        case 8: _t->setHighlight(*reinterpret_cast< QColor*>(_v)); break;
        case 9: _t->setHighlightedText(*reinterpret_cast< QColor*>(_v)); break;
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

QT_INIT_METAOBJECT const QMetaObject lmms::gui::LmmsPalette::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__LmmsPalette.data,
    qt_meta_data_lmms__gui__LmmsPalette,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::LmmsPalette::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::LmmsPalette::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__LmmsPalette.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::LmmsPalette::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
