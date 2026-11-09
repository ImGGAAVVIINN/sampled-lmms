/****************************************************************************
** Meta object code from reading C++ file 'MicrotunerConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/MicrotunerConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MicrotunerConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__MicrotunerConfig_t {
    QByteArrayData data[11];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__MicrotunerConfig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__MicrotunerConfig_t qt_meta_stringdata_lmms__gui__MicrotunerConfig = {
    {
QT_MOC_LITERAL(0, 0, 27), // "lmms::gui::MicrotunerConfig"
QT_MOC_LITERAL(1, 28, 15), // "updateScaleList"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "index"
QT_MOC_LITERAL(4, 51, 16), // "updateKeymapList"
QT_MOC_LITERAL(5, 68, 15), // "updateScaleForm"
QT_MOC_LITERAL(6, 84, 16), // "updateKeymapForm"
QT_MOC_LITERAL(7, 101, 17), // "loadScaleFromFile"
QT_MOC_LITERAL(8, 119, 18), // "loadKeymapFromFile"
QT_MOC_LITERAL(9, 138, 15), // "saveScaleToFile"
QT_MOC_LITERAL(10, 154, 16) // "saveKeymapToFile"

    },
    "lmms::gui::MicrotunerConfig\0updateScaleList\0"
    "\0index\0updateKeymapList\0updateScaleForm\0"
    "updateKeymapForm\0loadScaleFromFile\0"
    "loadKeymapFromFile\0saveScaleToFile\0"
    "saveKeymapToFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__MicrotunerConfig[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       4,    1,   57,    2, 0x0a /* Public */,
       5,    0,   60,    2, 0x0a /* Public */,
       6,    0,   61,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x08 /* Private */,
       8,    0,   63,    2, 0x08 /* Private */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,

       0        // eod
};

void lmms::gui::MicrotunerConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MicrotunerConfig *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateScaleList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateKeymapList((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateScaleForm(); break;
        case 3: _t->updateKeymapForm(); break;
        case 4: { bool _r = _t->loadScaleFromFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->loadKeymapFromFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->saveScaleToFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->saveKeymapToFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::MicrotunerConfig::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__MicrotunerConfig.data,
    qt_meta_data_lmms__gui__MicrotunerConfig,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::MicrotunerConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::MicrotunerConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__MicrotunerConfig.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SerializingObject"))
        return static_cast< SerializingObject*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::MicrotunerConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
