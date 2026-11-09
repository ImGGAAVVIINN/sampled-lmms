/****************************************************************************
** Meta object code from reading C++ file 'PatternEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/PatternEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PatternEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__PatternEditor_t {
    QByteArrayData data[16];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__PatternEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__PatternEditor_t qt_meta_stringdata_lmms__gui__PatternEditor = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::gui::PatternEditor"
QT_MOC_LITERAL(1, 25, 8), // "addSteps"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 10), // "cloneSteps"
QT_MOC_LITERAL(4, 46, 11), // "removeSteps"
QT_MOC_LITERAL(5, 58, 14), // "addSampleTrack"
QT_MOC_LITERAL(6, 73, 18), // "addAutomationTrack"
QT_MOC_LITERAL(7, 92, 9), // "cloneClip"
QT_MOC_LITERAL(8, 102, 14), // "updateMaxSteps"
QT_MOC_LITERAL(9, 117, 9), // "dropEvent"
QT_MOC_LITERAL(10, 127, 11), // "QDropEvent*"
QT_MOC_LITERAL(11, 139, 2), // "de"
QT_MOC_LITERAL(12, 142, 11), // "resizeEvent"
QT_MOC_LITERAL(13, 154, 13), // "QResizeEvent*"
QT_MOC_LITERAL(14, 168, 14), // "updatePosition"
QT_MOC_LITERAL(15, 183, 18) // "updatePixelsPerBar"

    },
    "lmms::gui::PatternEditor\0addSteps\0\0"
    "cloneSteps\0removeSteps\0addSampleTrack\0"
    "addAutomationTrack\0cloneClip\0"
    "updateMaxSteps\0dropEvent\0QDropEvent*\0"
    "de\0resizeEvent\0QResizeEvent*\0"
    "updatePosition\0updatePixelsPerBar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__PatternEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x0a /* Public */,
       3,    0,   70,    2, 0x0a /* Public */,
       4,    0,   71,    2, 0x0a /* Public */,
       5,    0,   72,    2, 0x0a /* Public */,
       6,    0,   73,    2, 0x0a /* Public */,
       7,    0,   74,    2, 0x0a /* Public */,
       8,    0,   75,    2, 0x0a /* Public */,
       9,    1,   76,    2, 0x09 /* Protected */,
      12,    1,   79,    2, 0x09 /* Protected */,
      14,    0,   82,    2, 0x09 /* Protected */,
      15,    0,   83,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::PatternEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatternEditor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addSteps(); break;
        case 1: _t->cloneSteps(); break;
        case 2: _t->removeSteps(); break;
        case 3: _t->addSampleTrack(); break;
        case 4: _t->addAutomationTrack(); break;
        case 5: _t->cloneClip(); break;
        case 6: _t->updateMaxSteps(); break;
        case 7: _t->dropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 8: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 9: _t->updatePosition(); break;
        case 10: _t->updatePixelsPerBar(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::PatternEditor::staticMetaObject = { {
    QMetaObject::SuperData::link<TrackContainerView::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__PatternEditor.data,
    qt_meta_data_lmms__gui__PatternEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::PatternEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::PatternEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__PatternEditor.stringdata0))
        return static_cast<void*>(this);
    return TrackContainerView::qt_metacast(_clname);
}

int lmms::gui::PatternEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TrackContainerView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
struct qt_meta_stringdata_lmms__gui__PatternEditorWindow_t {
    QByteArrayData data[4];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__PatternEditorWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__PatternEditorWindow_t qt_meta_stringdata_lmms__gui__PatternEditorWindow = {
    {
QT_MOC_LITERAL(0, 0, 30), // "lmms::gui::PatternEditorWindow"
QT_MOC_LITERAL(1, 31, 4), // "play"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4) // "stop"

    },
    "lmms::gui::PatternEditorWindow\0play\0"
    "\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__PatternEditorWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::PatternEditorWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PatternEditorWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->stop(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::PatternEditorWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<Editor::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__PatternEditorWindow.data,
    qt_meta_data_lmms__gui__PatternEditorWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::PatternEditorWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::PatternEditorWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__PatternEditorWindow.stringdata0))
        return static_cast<void*>(this);
    return Editor::qt_metacast(_clname);
}

int lmms::gui::PatternEditorWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Editor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
