/****************************************************************************
** Meta object code from reading C++ file 'Carla.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/CarlaBase/Carla.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Carla.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__CarlaInstrument_t {
    QByteArrayData data[12];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__CarlaInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__CarlaInstrument_t qt_meta_stringdata_lmms__CarlaInstrument = {
    {
QT_MOC_LITERAL(0, 0, 21), // "lmms::CarlaInstrument"
QT_MOC_LITERAL(1, 22, 8), // "uiClosed"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "paramsUpdated"
QT_MOC_LITERAL(4, 46, 17), // "sampleRateChanged"
QT_MOC_LITERAL(5, 64, 13), // "refreshParams"
QT_MOC_LITERAL(6, 78, 4), // "init"
QT_MOC_LITERAL(7, 83, 16), // "clearParamModels"
QT_MOC_LITERAL(8, 100, 17), // "paramModelChanged"
QT_MOC_LITERAL(9, 118, 8), // "uint32_t"
QT_MOC_LITERAL(10, 127, 5), // "index"
QT_MOC_LITERAL(11, 133, 16) // "updateParamModel"

    },
    "lmms::CarlaInstrument\0uiClosed\0\0"
    "paramsUpdated\0sampleRateChanged\0"
    "refreshParams\0init\0clearParamModels\0"
    "paramModelChanged\0uint32_t\0index\0"
    "updateParamModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__CarlaInstrument[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       5,    0,   60,    2, 0x28 /* Private | MethodCloned */,
       7,    0,   61,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
      11,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void lmms::CarlaInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CarlaInstrument *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->uiClosed(); break;
        case 1: _t->paramsUpdated(); break;
        case 2: _t->sampleRateChanged(); break;
        case 3: _t->refreshParams((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->refreshParams(); break;
        case 5: _t->clearParamModels(); break;
        case 6: _t->paramModelChanged((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 7: _t->updateParamModel((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CarlaInstrument::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarlaInstrument::uiClosed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CarlaInstrument::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarlaInstrument::paramsUpdated)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::CarlaInstrument::staticMetaObject = { {
    QMetaObject::SuperData::link<Instrument::staticMetaObject>(),
    qt_meta_stringdata_lmms__CarlaInstrument.data,
    qt_meta_data_lmms__CarlaInstrument,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::CarlaInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::CarlaInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__CarlaInstrument.stringdata0))
        return static_cast<void*>(this);
    return Instrument::qt_metacast(_clname);
}

int lmms::CarlaInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Instrument::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void lmms::CarlaInstrument::uiClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::CarlaInstrument::paramsUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_lmms__gui__CarlaParamsSubWindow_t {
    QByteArrayData data[4];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__CarlaParamsSubWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__CarlaParamsSubWindow_t qt_meta_stringdata_lmms__gui__CarlaParamsSubWindow = {
    {
QT_MOC_LITERAL(0, 0, 31), // "lmms::gui::CarlaParamsSubWindow"
QT_MOC_LITERAL(1, 32, 8), // "uiClosed"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 7) // "resized"

    },
    "lmms::gui::CarlaParamsSubWindow\0"
    "uiClosed\0\0resized"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__CarlaParamsSubWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::CarlaParamsSubWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CarlaParamsSubWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->uiClosed(); break;
        case 1: _t->resized(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CarlaParamsSubWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarlaParamsSubWindow::uiClosed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CarlaParamsSubWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarlaParamsSubWindow::resized)) {
                *result = 1;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::CarlaParamsSubWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<SubWindow::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__CarlaParamsSubWindow.data,
    qt_meta_data_lmms__gui__CarlaParamsSubWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::CarlaParamsSubWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::CarlaParamsSubWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__CarlaParamsSubWindow.stringdata0))
        return static_cast<void*>(this);
    return SubWindow::qt_metacast(_clname);
}

int lmms::gui::CarlaParamsSubWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SubWindow::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void lmms::gui::CarlaParamsSubWindow::uiClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::gui::CarlaParamsSubWindow::resized()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_lmms__gui__CarlaInstrumentView_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__CarlaInstrumentView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__CarlaInstrumentView_t qt_meta_stringdata_lmms__gui__CarlaInstrumentView = {
    {
QT_MOC_LITERAL(0, 0, 30), // "lmms::gui::CarlaInstrumentView"
QT_MOC_LITERAL(1, 31, 8), // "toggleUI"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 8), // "uiClosed"
QT_MOC_LITERAL(4, 50, 18), // "toggleParamsWindow"
QT_MOC_LITERAL(5, 69, 14) // "paramsUiClosed"

    },
    "lmms::gui::CarlaInstrumentView\0toggleUI\0"
    "\0uiClosed\0toggleParamsWindow\0"
    "paramsUiClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__CarlaInstrumentView[] = {

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
       1,    1,   34,    2, 0x08 /* Private */,
       3,    0,   37,    2, 0x08 /* Private */,
       4,    0,   38,    2, 0x08 /* Private */,
       5,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::CarlaInstrumentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CarlaInstrumentView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->toggleUI((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->uiClosed(); break;
        case 2: _t->toggleParamsWindow(); break;
        case 3: _t->paramsUiClosed(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::CarlaInstrumentView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentViewFixedSize::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__CarlaInstrumentView.data,
    qt_meta_data_lmms__gui__CarlaInstrumentView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::CarlaInstrumentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::CarlaInstrumentView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__CarlaInstrumentView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentViewFixedSize::qt_metacast(_clname);
}

int lmms::gui::CarlaInstrumentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentViewFixedSize::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_lmms__gui__CarlaParamsView_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__CarlaParamsView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__CarlaParamsView_t qt_meta_stringdata_lmms__gui__CarlaParamsView = {
    {
QT_MOC_LITERAL(0, 0, 26), // "lmms::gui::CarlaParamsView"
QT_MOC_LITERAL(1, 27, 8), // "uiClosed"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "refreshKnobs"
QT_MOC_LITERAL(4, 50, 11), // "filterKnobs"
QT_MOC_LITERAL(5, 62, 15), // "clearFilterText"
QT_MOC_LITERAL(6, 78, 13) // "windowResized"

    },
    "lmms::gui::CarlaParamsView\0uiClosed\0"
    "\0refreshKnobs\0filterKnobs\0clearFilterText\0"
    "windowResized"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__CarlaParamsView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::CarlaParamsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CarlaParamsView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->uiClosed(); break;
        case 1: _t->refreshKnobs(); break;
        case 2: _t->filterKnobs(); break;
        case 3: _t->clearFilterText(); break;
        case 4: _t->windowResized(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CarlaParamsView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CarlaParamsView::uiClosed)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::CarlaParamsView::staticMetaObject = { {
    QMetaObject::SuperData::link<InstrumentView::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__CarlaParamsView.data,
    qt_meta_data_lmms__gui__CarlaParamsView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::CarlaParamsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::CarlaParamsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__CarlaParamsView.stringdata0))
        return static_cast<void*>(this);
    return InstrumentView::qt_metacast(_clname);
}

int lmms::gui::CarlaParamsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = InstrumentView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void lmms::gui::CarlaParamsView::uiClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
