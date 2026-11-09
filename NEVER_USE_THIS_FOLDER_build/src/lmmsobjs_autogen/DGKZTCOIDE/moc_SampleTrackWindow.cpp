/****************************************************************************
** Meta object code from reading C++ file 'SampleTrackWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/SampleTrackWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SampleTrackWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__SampleTrackWindow_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__SampleTrackWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__SampleTrackWindow_t qt_meta_stringdata_lmms__gui__SampleTrackWindow = {
    {
QT_MOC_LITERAL(0, 0, 28), // "lmms::gui::SampleTrackWindow"
QT_MOC_LITERAL(1, 29, 11), // "textChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 8), // "new_name"
QT_MOC_LITERAL(4, 51, 16), // "toggleVisibility"
QT_MOC_LITERAL(5, 68, 2), // "on"
QT_MOC_LITERAL(6, 71, 10) // "updateName"

    },
    "lmms::gui::SampleTrackWindow\0textChanged\0"
    "\0new_name\0toggleVisibility\0on\0updateName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__SampleTrackWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       6,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::SampleTrackWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SampleTrackWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->toggleVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateName(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::SampleTrackWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__SampleTrackWindow.data,
    qt_meta_data_lmms__gui__SampleTrackWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::SampleTrackWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::SampleTrackWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__SampleTrackWindow.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModelView"))
        return static_cast< ModelView*>(this);
    if (!strcmp(_clname, "SerializingObjectHook"))
        return static_cast< SerializingObjectHook*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::SampleTrackWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
