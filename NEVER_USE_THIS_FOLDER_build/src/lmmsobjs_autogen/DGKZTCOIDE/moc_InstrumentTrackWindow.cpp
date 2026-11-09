/****************************************************************************
** Meta object code from reading C++ file 'InstrumentTrackWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/InstrumentTrackWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InstrumentTrackWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__InstrumentTrackWindow_t {
    QByteArrayData data[11];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__InstrumentTrackWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__InstrumentTrackWindow_t qt_meta_stringdata_lmms__gui__InstrumentTrackWindow = {
    {
QT_MOC_LITERAL(0, 0, 32), // "lmms::gui::InstrumentTrackWindow"
QT_MOC_LITERAL(1, 33, 11), // "textChanged"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 9), // "_new_name"
QT_MOC_LITERAL(4, 56, 16), // "toggleVisibility"
QT_MOC_LITERAL(5, 73, 3), // "_on"
QT_MOC_LITERAL(6, 77, 10), // "updateName"
QT_MOC_LITERAL(7, 88, 20), // "updateInstrumentView"
QT_MOC_LITERAL(8, 109, 22), // "saveSettingsBtnClicked"
QT_MOC_LITERAL(9, 132, 18), // "viewNextInstrument"
QT_MOC_LITERAL(10, 151, 18) // "viewPrevInstrument"

    },
    "lmms::gui::InstrumentTrackWindow\0"
    "textChanged\0\0_new_name\0toggleVisibility\0"
    "_on\0updateName\0updateInstrumentView\0"
    "saveSettingsBtnClicked\0viewNextInstrument\0"
    "viewPrevInstrument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__InstrumentTrackWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       4,    1,   52,    2, 0x0a /* Public */,
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x09 /* Protected */,
       9,    0,   58,    2, 0x09 /* Protected */,
      10,    0,   59,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::InstrumentTrackWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InstrumentTrackWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->toggleVisibility((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->updateName(); break;
        case 3: _t->updateInstrumentView(); break;
        case 4: _t->saveSettingsBtnClicked(); break;
        case 5: _t->viewNextInstrument(); break;
        case 6: _t->viewPrevInstrument(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::InstrumentTrackWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__InstrumentTrackWindow.data,
    qt_meta_data_lmms__gui__InstrumentTrackWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::InstrumentTrackWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::InstrumentTrackWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__InstrumentTrackWindow.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModelView"))
        return static_cast< ModelView*>(this);
    if (!strcmp(_clname, "SerializingObjectHook"))
        return static_cast< SerializingObjectHook*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::InstrumentTrackWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
