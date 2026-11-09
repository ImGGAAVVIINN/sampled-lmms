/****************************************************************************
** Meta object code from reading C++ file 'EffectRackView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/EffectRackView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectRackView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__EffectRackView_t {
    QByteArrayData data[10];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__EffectRackView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__EffectRackView_t qt_meta_stringdata_lmms__gui__EffectRackView = {
    {
QT_MOC_LITERAL(0, 0, 25), // "lmms::gui::EffectRackView"
QT_MOC_LITERAL(1, 26, 10), // "clearViews"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 6), // "moveUp"
QT_MOC_LITERAL(4, 45, 11), // "EffectView*"
QT_MOC_LITERAL(5, 57, 4), // "view"
QT_MOC_LITERAL(6, 62, 8), // "moveDown"
QT_MOC_LITERAL(7, 71, 12), // "deletePlugin"
QT_MOC_LITERAL(8, 84, 6), // "update"
QT_MOC_LITERAL(9, 91, 9) // "addEffect"

    },
    "lmms::gui::EffectRackView\0clearViews\0"
    "\0moveUp\0EffectView*\0view\0moveDown\0"
    "deletePlugin\0update\0addEffect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__EffectRackView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       7,    1,   51,    2, 0x0a /* Public */,
       8,    0,   54,    2, 0x08 /* Private */,
       9,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::EffectRackView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EffectRackView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clearViews(); break;
        case 1: _t->moveUp((*reinterpret_cast< EffectView*(*)>(_a[1]))); break;
        case 2: _t->moveDown((*reinterpret_cast< EffectView*(*)>(_a[1]))); break;
        case 3: _t->deletePlugin((*reinterpret_cast< EffectView*(*)>(_a[1]))); break;
        case 4: _t->update(); break;
        case 5: _t->addEffect(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::EffectRackView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__EffectRackView.data,
    qt_meta_data_lmms__gui__EffectRackView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::EffectRackView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::EffectRackView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__EffectRackView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModelView"))
        return static_cast< ModelView*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::EffectRackView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
