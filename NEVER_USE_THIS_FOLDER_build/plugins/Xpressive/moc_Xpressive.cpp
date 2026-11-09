/****************************************************************************
** Meta object code from reading C++ file 'Xpressive.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Xpressive/Xpressive.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Xpressive.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__Xpressive_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__Xpressive_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__Xpressive_t qt_meta_stringdata_lmms__Xpressive = {
    {
QT_MOC_LITERAL(0, 0, 15) // "lmms::Xpressive"

    },
    "lmms::Xpressive"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__Xpressive[] = {

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

void lmms::Xpressive::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::Xpressive::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__Xpressive.data,
    qt_meta_data_lmms__Xpressive,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::Xpressive::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::Xpressive::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__Xpressive.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::Xpressive::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_lmms__gui__XpressiveView_t {
    QByteArrayData data[15];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__XpressiveView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__XpressiveView_t qt_meta_stringdata_lmms__gui__XpressiveView = {
    {
QT_MOC_LITERAL(0, 0, 24), // "lmms::gui::XpressiveView"
QT_MOC_LITERAL(1, 25, 12), // "updateLayout"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 14), // "sinWaveClicked"
QT_MOC_LITERAL(4, 54, 19), // "triangleWaveClicked"
QT_MOC_LITERAL(5, 74, 14), // "sqrWaveClicked"
QT_MOC_LITERAL(6, 89, 14), // "sawWaveClicked"
QT_MOC_LITERAL(7, 104, 16), // "noiseWaveClicked"
QT_MOC_LITERAL(8, 121, 18), // "moogSawWaveClicked"
QT_MOC_LITERAL(9, 140, 14), // "expWaveClicked"
QT_MOC_LITERAL(10, 155, 14), // "usrWaveClicked"
QT_MOC_LITERAL(11, 170, 11), // "helpClicked"
QT_MOC_LITERAL(12, 182, 17), // "expressionChanged"
QT_MOC_LITERAL(13, 200, 13), // "smoothChanged"
QT_MOC_LITERAL(14, 214, 10) // "graphDrawn"

    },
    "lmms::gui::XpressiveView\0updateLayout\0"
    "\0sinWaveClicked\0triangleWaveClicked\0"
    "sqrWaveClicked\0sawWaveClicked\0"
    "noiseWaveClicked\0moogSawWaveClicked\0"
    "expWaveClicked\0usrWaveClicked\0helpClicked\0"
    "expressionChanged\0smoothChanged\0"
    "graphDrawn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__XpressiveView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x09 /* Protected */,
       3,    0,   80,    2, 0x09 /* Protected */,
       4,    0,   81,    2, 0x09 /* Protected */,
       5,    0,   82,    2, 0x09 /* Protected */,
       6,    0,   83,    2, 0x09 /* Protected */,
       7,    0,   84,    2, 0x09 /* Protected */,
       8,    0,   85,    2, 0x09 /* Protected */,
       9,    0,   86,    2, 0x09 /* Protected */,
      10,    0,   87,    2, 0x09 /* Protected */,
      11,    0,   88,    2, 0x09 /* Protected */,
      12,    0,   89,    2, 0x09 /* Protected */,
      13,    0,   90,    2, 0x09 /* Protected */,
      14,    0,   91,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::XpressiveView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XpressiveView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateLayout(); break;
        case 1: _t->sinWaveClicked(); break;
        case 2: _t->triangleWaveClicked(); break;
        case 3: _t->sqrWaveClicked(); break;
        case 4: _t->sawWaveClicked(); break;
        case 5: _t->noiseWaveClicked(); break;
        case 6: _t->moogSawWaveClicked(); break;
        case 7: _t->expWaveClicked(); break;
        case 8: _t->usrWaveClicked(); break;
        case 9: _t->helpClicked(); break;
        case 10: _t->expressionChanged(); break;
        case 11: _t->smoothChanged(); break;
        case 12: _t->graphDrawn(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::XpressiveView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__XpressiveView.data,
    qt_meta_data_lmms__gui__XpressiveView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::XpressiveView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::XpressiveView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__XpressiveView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::XpressiveView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
struct qt_meta_stringdata_lmms__gui__XpressiveHelpView_t {
    QByteArrayData data[1];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__XpressiveHelpView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__XpressiveHelpView_t qt_meta_stringdata_lmms__gui__XpressiveHelpView = {
    {
QT_MOC_LITERAL(0, 0, 28) // "lmms::gui::XpressiveHelpView"

    },
    "lmms::gui::XpressiveHelpView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__XpressiveHelpView[] = {

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

void lmms::gui::XpressiveHelpView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::XpressiveHelpView::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__XpressiveHelpView.data,
    qt_meta_data_lmms__gui__XpressiveHelpView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::XpressiveHelpView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::XpressiveHelpView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__XpressiveHelpView.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int lmms::gui::XpressiveHelpView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
