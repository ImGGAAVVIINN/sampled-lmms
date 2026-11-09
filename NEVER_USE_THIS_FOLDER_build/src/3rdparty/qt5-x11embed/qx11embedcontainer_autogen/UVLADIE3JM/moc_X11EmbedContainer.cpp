/****************************************************************************
** Meta object code from reading C++ file 'X11EmbedContainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../src/3rdparty/qt5-x11embed/src/X11EmbedContainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'X11EmbedContainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QX11EmbedContainer_t {
    QByteArrayData data[6];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QX11EmbedContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QX11EmbedContainer_t qt_meta_stringdata_QX11EmbedContainer = {
    {
QT_MOC_LITERAL(0, 0, 18), // "QX11EmbedContainer"
QT_MOC_LITERAL(1, 19, 16), // "clientIsEmbedded"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "clientClosed"
QT_MOC_LITERAL(4, 50, 5), // "error"
QT_MOC_LITERAL(5, 56, 25) // "QX11EmbedContainer::Error"

    },
    "QX11EmbedContainer\0clientIsEmbedded\0"
    "\0clientClosed\0error\0QX11EmbedContainer::Error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QX11EmbedContainer[] = {

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
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    1,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,

       0        // eod
};

void QX11EmbedContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QX11EmbedContainer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->clientIsEmbedded(); break;
        case 1: _t->clientClosed(); break;
        case 2: _t->error((*reinterpret_cast< QX11EmbedContainer::Error(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QX11EmbedContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QX11EmbedContainer::clientIsEmbedded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QX11EmbedContainer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QX11EmbedContainer::clientClosed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QX11EmbedContainer::*)(QX11EmbedContainer::Error );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QX11EmbedContainer::error)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QX11EmbedContainer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QX11EmbedContainer.data,
    qt_meta_data_QX11EmbedContainer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QX11EmbedContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QX11EmbedContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QX11EmbedContainer.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QAbstractNativeEventFilter"))
        return static_cast< QAbstractNativeEventFilter*>(this);
    return QWidget::qt_metacast(_clname);
}

int QX11EmbedContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void QX11EmbedContainer::clientIsEmbedded()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QX11EmbedContainer::clientClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QX11EmbedContainer::error(QX11EmbedContainer::Error _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
