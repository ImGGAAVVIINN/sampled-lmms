/****************************************************************************
** Meta object code from reading C++ file 'TrackContentWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TrackContentWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TrackContentWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__TrackContentWidget_t {
    QByteArrayData data[18];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__TrackContentWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__TrackContentWidget_t qt_meta_stringdata_lmms__gui__TrackContentWidget = {
    {
QT_MOC_LITERAL(0, 0, 29), // "lmms::gui::TrackContentWidget"
QT_MOC_LITERAL(1, 30, 6), // "update"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 14), // "changePosition"
QT_MOC_LITERAL(4, 53, 13), // "lmms::TimePos"
QT_MOC_LITERAL(5, 67, 6), // "newPos"
QT_MOC_LITERAL(6, 74, 16), // "updateBackground"
QT_MOC_LITERAL(7, 91, 11), // "darkerColor"
QT_MOC_LITERAL(8, 103, 12), // "lighterColor"
QT_MOC_LITERAL(9, 116, 15), // "coarseGridColor"
QT_MOC_LITERAL(10, 132, 13), // "fineGridColor"
QT_MOC_LITERAL(11, 146, 15), // "horizontalColor"
QT_MOC_LITERAL(12, 162, 11), // "embossColor"
QT_MOC_LITERAL(13, 174, 15), // "coarseGridWidth"
QT_MOC_LITERAL(14, 190, 13), // "fineGridWidth"
QT_MOC_LITERAL(15, 204, 15), // "horizontalWidth"
QT_MOC_LITERAL(16, 220, 11), // "embossWidth"
QT_MOC_LITERAL(17, 232, 12) // "embossOffset"

    },
    "lmms::gui::TrackContentWidget\0update\0"
    "\0changePosition\0lmms::TimePos\0newPos\0"
    "updateBackground\0darkerColor\0lighterColor\0"
    "coarseGridColor\0fineGridColor\0"
    "horizontalColor\0embossColor\0coarseGridWidth\0"
    "fineGridWidth\0horizontalWidth\0embossWidth\0"
    "embossOffset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__TrackContentWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
      11,   40, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       3,    0,   38,    2, 0x2a /* Public | MethodCloned */,
       6,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QBrush, 0x00095103,
       8, QMetaType::QBrush, 0x00095103,
       9, QMetaType::QBrush, 0x00095103,
      10, QMetaType::QBrush, 0x00095103,
      11, QMetaType::QBrush, 0x00095103,
      12, QMetaType::QBrush, 0x00095103,
      13, QMetaType::Int, 0x00095103,
      14, QMetaType::Int, 0x00095103,
      15, QMetaType::Int, 0x00095103,
      16, QMetaType::Int, 0x00095103,
      17, QMetaType::Int, 0x00095103,

       0        // eod
};

void lmms::gui::TrackContentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrackContentWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->update(); break;
        case 1: _t->changePosition((*reinterpret_cast< const lmms::TimePos(*)>(_a[1]))); break;
        case 2: _t->changePosition(); break;
        case 3: _t->updateBackground(); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TrackContentWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QBrush*>(_v) = _t->darkerColor(); break;
        case 1: *reinterpret_cast< QBrush*>(_v) = _t->lighterColor(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->coarseGridColor(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->fineGridColor(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->horizontalColor(); break;
        case 5: *reinterpret_cast< QBrush*>(_v) = _t->embossColor(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->coarseGridWidth(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->fineGridWidth(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->horizontalWidth(); break;
        case 9: *reinterpret_cast< int*>(_v) = _t->embossWidth(); break;
        case 10: *reinterpret_cast< int*>(_v) = _t->embossOffset(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TrackContentWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDarkerColor(*reinterpret_cast< QBrush*>(_v)); break;
        case 1: _t->setLighterColor(*reinterpret_cast< QBrush*>(_v)); break;
        case 2: _t->setCoarseGridColor(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setFineGridColor(*reinterpret_cast< QBrush*>(_v)); break;
        case 4: _t->setHorizontalColor(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setEmbossColor(*reinterpret_cast< QBrush*>(_v)); break;
        case 6: _t->setCoarseGridWidth(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setFineGridWidth(*reinterpret_cast< int*>(_v)); break;
        case 8: _t->setHorizontalWidth(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setEmbossWidth(*reinterpret_cast< int*>(_v)); break;
        case 10: _t->setEmbossOffset(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::TrackContentWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__TrackContentWidget.data,
    qt_meta_data_lmms__gui__TrackContentWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::TrackContentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::TrackContentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__TrackContentWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JournallingObject"))
        return static_cast< JournallingObject*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::TrackContentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
