/****************************************************************************
** Meta object code from reading C++ file 'FileSearchJob.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/FileSearchJob.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileSearchJob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__FileSearchJob_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__FileSearchJob_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__FileSearchJob_t qt_meta_stringdata_lmms__gui__FileSearchJob = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::gui::FileSearchJob"
QT_MOC_LITERAL(1, 25, 10), // "foundMatch"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "path"
QT_MOC_LITERAL(4, 42, 7), // "started"
QT_MOC_LITERAL(5, 50, 8) // "finished"

    },
    "lmms::gui::FileSearchJob\0foundMatch\0"
    "\0path\0started\0finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__FileSearchJob[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,
       5,    0,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::FileSearchJob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileSearchJob *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->foundMatch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->started(); break;
        case 2: _t->finished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileSearchJob::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSearchJob::foundMatch)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileSearchJob::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSearchJob::started)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileSearchJob::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileSearchJob::finished)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::FileSearchJob::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__FileSearchJob.data,
    qt_meta_data_lmms__gui__FileSearchJob,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::FileSearchJob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::FileSearchJob::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__FileSearchJob.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int lmms::gui::FileSearchJob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void lmms::gui::FileSearchJob::foundMatch(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lmms::gui::FileSearchJob::started()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void lmms::gui::FileSearchJob::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
