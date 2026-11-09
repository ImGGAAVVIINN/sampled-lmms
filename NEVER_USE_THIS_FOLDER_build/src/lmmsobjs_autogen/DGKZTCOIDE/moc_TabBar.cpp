/****************************************************************************
** Meta object code from reading C++ file 'TabBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TabBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TabBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__TabBar_t {
    QByteArrayData data[9];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__TabBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__TabBar_t qt_meta_stringdata_lmms__gui__TabBar = {
    {
QT_MOC_LITERAL(0, 0, 17), // "lmms::gui::TabBar"
QT_MOC_LITERAL(1, 18, 16), // "allWidgetsHidden"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "widgetShown"
QT_MOC_LITERAL(4, 48, 12), // "setActiveTab"
QT_MOC_LITERAL(5, 61, 3), // "_id"
QT_MOC_LITERAL(6, 65, 7), // "hideAll"
QT_MOC_LITERAL(7, 73, 10), // "_exception"
QT_MOC_LITERAL(8, 84, 10) // "tabClicked"

    },
    "lmms::gui::TabBar\0allWidgetsHidden\0\0"
    "widgetShown\0setActiveTab\0_id\0hideAll\0"
    "_exception\0tabClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__TabBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   46,    2, 0x0a /* Public */,
       6,    1,   49,    2, 0x09 /* Protected */,
       6,    0,   52,    2, 0x29 /* Protected | MethodCloned */,
       8,    1,   53,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void lmms::gui::TabBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TabBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->allWidgetsHidden(); break;
        case 1: _t->widgetShown(); break;
        case 2: _t->setActiveTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->hideAll((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->hideAll(); break;
        case 5: _t->tabClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TabBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabBar::allWidgetsHidden)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TabBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TabBar::widgetShown)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::TabBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__TabBar.data,
    qt_meta_data_lmms__gui__TabBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::TabBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::TabBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__TabBar.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::TabBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void lmms::gui::TabBar::allWidgetsHidden()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::gui::TabBar::widgetShown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
