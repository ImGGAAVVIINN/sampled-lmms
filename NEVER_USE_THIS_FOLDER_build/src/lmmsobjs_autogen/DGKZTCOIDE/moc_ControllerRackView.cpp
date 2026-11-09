/****************************************************************************
** Meta object code from reading C++ file 'ControllerRackView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/ControllerRackView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControllerRackView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__ControllerRackView_t {
    QByteArrayData data[11];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__ControllerRackView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__ControllerRackView_t qt_meta_stringdata_lmms__gui__ControllerRackView = {
    {
QT_MOC_LITERAL(0, 0, 29), // "lmms::gui::ControllerRackView"
QT_MOC_LITERAL(1, 30, 16), // "deleteController"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 15), // "ControllerView*"
QT_MOC_LITERAL(4, 64, 4), // "view"
QT_MOC_LITERAL(5, 69, 6), // "moveUp"
QT_MOC_LITERAL(6, 76, 8), // "moveDown"
QT_MOC_LITERAL(7, 85, 13), // "addController"
QT_MOC_LITERAL(8, 99, 11), // "Controller*"
QT_MOC_LITERAL(9, 111, 10), // "controller"
QT_MOC_LITERAL(10, 122, 16) // "removeController"

    },
    "lmms::gui::ControllerRackView\0"
    "deleteController\0\0ControllerView*\0"
    "view\0moveUp\0moveDown\0addController\0"
    "Controller*\0controller\0removeController"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__ControllerRackView[] = {

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
       1,    1,   44,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       6,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
      10,    1,   56,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::ControllerRackView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControllerRackView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->deleteController((*reinterpret_cast< ControllerView*(*)>(_a[1]))); break;
        case 1: _t->moveUp((*reinterpret_cast< ControllerView*(*)>(_a[1]))); break;
        case 2: _t->moveDown((*reinterpret_cast< ControllerView*(*)>(_a[1]))); break;
        case 3: _t->addController((*reinterpret_cast< Controller*(*)>(_a[1]))); break;
        case 4: _t->removeController((*reinterpret_cast< Controller*(*)>(_a[1]))); break;
        case 5: _t->addController(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::ControllerRackView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__ControllerRackView.data,
    qt_meta_data_lmms__gui__ControllerRackView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::ControllerRackView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::ControllerRackView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__ControllerRackView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SerializingObject"))
        return static_cast< SerializingObject*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::ControllerRackView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
