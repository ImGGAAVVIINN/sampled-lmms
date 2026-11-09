/****************************************************************************
** Meta object code from reading C++ file 'RemotePlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/RemotePlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RemotePlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__ProcessWatcher_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__ProcessWatcher_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__ProcessWatcher_t qt_meta_stringdata_lmms__ProcessWatcher = {
    {
QT_MOC_LITERAL(0, 0, 20) // "lmms::ProcessWatcher"

    },
    "lmms::ProcessWatcher"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__ProcessWatcher[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void lmms::ProcessWatcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::ProcessWatcher::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_lmms__ProcessWatcher.data,
    qt_meta_data_lmms__ProcessWatcher,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::ProcessWatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::ProcessWatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__ProcessWatcher.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int lmms::ProcessWatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_lmms__RemotePlugin_t {
    QByteArrayData data[11];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__RemotePlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__RemotePlugin_t qt_meta_stringdata_lmms__RemotePlugin = {
    {
QT_MOC_LITERAL(0, 0, 18), // "lmms::RemotePlugin"
QT_MOC_LITERAL(1, 19, 6), // "showUI"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "hideUI"
QT_MOC_LITERAL(4, 34, 15), // "processFinished"
QT_MOC_LITERAL(5, 50, 8), // "exitCode"
QT_MOC_LITERAL(6, 59, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(7, 80, 10), // "exitStatus"
QT_MOC_LITERAL(8, 91, 14), // "processErrored"
QT_MOC_LITERAL(9, 106, 22), // "QProcess::ProcessError"
QT_MOC_LITERAL(10, 129, 3) // "err"

    },
    "lmms::RemotePlugin\0showUI\0\0hideUI\0"
    "processFinished\0exitCode\0QProcess::ExitStatus\0"
    "exitStatus\0processErrored\0"
    "QProcess::ProcessError\0err"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__RemotePlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    2,   36,    2, 0x08 /* Private */,
       8,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void lmms::RemotePlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RemotePlugin *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showUI(); break;
        case 1: _t->hideUI(); break;
        case 2: _t->processFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 3: _t->processErrored((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::RemotePlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__RemotePlugin.data,
    qt_meta_data_lmms__RemotePlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::RemotePlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::RemotePlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__RemotePlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "RemotePluginBase"))
        return static_cast< RemotePluginBase*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::RemotePlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
