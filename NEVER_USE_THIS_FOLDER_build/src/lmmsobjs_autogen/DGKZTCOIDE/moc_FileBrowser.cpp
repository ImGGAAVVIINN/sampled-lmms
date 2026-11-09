/****************************************************************************
** Meta object code from reading C++ file 'FileBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/FileBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__FileBrowser_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__FileBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__FileBrowser_t qt_meta_stringdata_lmms__gui__FileBrowser = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::gui::FileBrowser"
QT_MOC_LITERAL(1, 23, 10), // "reloadTree"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "expandItems"
QT_MOC_LITERAL(4, 47, 14), // "QList<QString>"
QT_MOC_LITERAL(5, 62, 12), // "expandedDirs"
QT_MOC_LITERAL(6, 75, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 92, 4), // "item"
QT_MOC_LITERAL(8, 97, 17) // "giveFocusToFilter"

    },
    "lmms::gui::FileBrowser\0reloadTree\0\0"
    "expandItems\0QList<QString>\0expandedDirs\0"
    "QTreeWidgetItem*\0item\0giveFocusToFilter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__FileBrowser[] = {

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
       1,    0,   34,    2, 0x08 /* Private */,
       3,    2,   35,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x28 /* Private | MethodCloned */,
       8,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6,    5,    7,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::FileBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileBrowser *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->reloadTree(); break;
        case 1: _t->expandItems((*reinterpret_cast< const QList<QString>(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 2: _t->expandItems((*reinterpret_cast< const QList<QString>(*)>(_a[1]))); break;
        case 3: _t->giveFocusToFilter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::FileBrowser::staticMetaObject = { {
    QMetaObject::SuperData::link<SideBarWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__FileBrowser.data,
    qt_meta_data_lmms__gui__FileBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::FileBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::FileBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__FileBrowser.stringdata0))
        return static_cast<void*>(this);
    return SideBarWidget::qt_metacast(_clname);
}

int lmms::gui::FileBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SideBarWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_lmms__gui__FileBrowserTreeWidget_t {
    QByteArrayData data[13];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__FileBrowserTreeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__FileBrowserTreeWidget_t qt_meta_stringdata_lmms__gui__FileBrowserTreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 32), // "lmms::gui::FileBrowserTreeWidget"
QT_MOC_LITERAL(1, 33, 16), // "activateListItem"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 68, 4), // "item"
QT_MOC_LITERAL(5, 73, 6), // "column"
QT_MOC_LITERAL(6, 80, 24), // "openInNewInstrumentTrack"
QT_MOC_LITERAL(7, 105, 9), // "FileItem*"
QT_MOC_LITERAL(8, 115, 10), // "songEditor"
QT_MOC_LITERAL(9, 126, 20), // "openInNewSampleTrack"
QT_MOC_LITERAL(10, 147, 13), // "openInSlicerT"
QT_MOC_LITERAL(11, 161, 27), // "sendToActiveInstrumentTrack"
QT_MOC_LITERAL(12, 189, 15) // "updateDirectory"

    },
    "lmms::gui::FileBrowserTreeWidget\0"
    "activateListItem\0\0QTreeWidgetItem*\0"
    "item\0column\0openInNewInstrumentTrack\0"
    "FileItem*\0songEditor\0openInNewSampleTrack\0"
    "openInSlicerT\0sendToActiveInstrumentTrack\0"
    "updateDirectory"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__FileBrowserTreeWidget[] = {

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
       1,    2,   44,    2, 0x08 /* Private */,
       6,    2,   49,    2, 0x08 /* Private */,
       9,    1,   54,    2, 0x08 /* Private */,
      10,    2,   57,    2, 0x08 /* Private */,
      11,    1,   62,    2, 0x08 /* Private */,
      12,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    4,    8,
    QMetaType::Bool, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool,    4,    8,
    QMetaType::Void, 0x80000000 | 7,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void lmms::gui::FileBrowserTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileBrowserTreeWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->activateListItem((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->openInNewInstrumentTrack((*reinterpret_cast< FileItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: { bool _r = _t->openInNewSampleTrack((*reinterpret_cast< FileItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->openInSlicerT((*reinterpret_cast< FileItem*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->sendToActiveInstrumentTrack((*reinterpret_cast< FileItem*(*)>(_a[1]))); break;
        case 5: _t->updateDirectory((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::FileBrowserTreeWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QTreeWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__FileBrowserTreeWidget.data,
    qt_meta_data_lmms__gui__FileBrowserTreeWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::FileBrowserTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::FileBrowserTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__FileBrowserTreeWidget.stringdata0))
        return static_cast<void*>(this);
    return QTreeWidget::qt_metacast(_clname);
}

int lmms::gui::FileBrowserTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
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
