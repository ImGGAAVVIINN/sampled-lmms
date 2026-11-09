/****************************************************************************
** Meta object code from reading C++ file 'Graph.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/Graph.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Graph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__Graph_t {
    QByteArrayData data[6];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__Graph_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__Graph_t qt_meta_stringdata_lmms__gui__Graph = {
    {
QT_MOC_LITERAL(0, 0, 16), // "lmms::gui::Graph"
QT_MOC_LITERAL(1, 17, 5), // "drawn"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "updateGraph"
QT_MOC_LITERAL(4, 36, 9), // "_startPos"
QT_MOC_LITERAL(5, 46, 7) // "_endPos"

    },
    "lmms::gui::Graph\0drawn\0\0updateGraph\0"
    "_startPos\0_endPos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__Graph[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   30,    2, 0x09 /* Protected */,
       3,    0,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::Graph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Graph *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->drawn(); break;
        case 1: _t->updateGraph((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->updateGraph(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Graph::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Graph::drawn)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::Graph::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__Graph.data,
    qt_meta_data_lmms__gui__Graph,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::Graph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::Graph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__Graph.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ModelView"))
        return static_cast< ModelView*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::Graph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void lmms::gui::Graph::drawn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_lmms__graphModel_t {
    QByteArrayData data[32];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__graphModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__graphModel_t qt_meta_stringdata_lmms__graphModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "lmms::graphModel"
QT_MOC_LITERAL(1, 17, 13), // "lengthChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "samplesChanged"
QT_MOC_LITERAL(4, 47, 8), // "startPos"
QT_MOC_LITERAL(5, 56, 6), // "endPos"
QT_MOC_LITERAL(6, 63, 12), // "rangeChanged"
QT_MOC_LITERAL(7, 76, 8), // "setRange"
QT_MOC_LITERAL(8, 85, 4), // "ymin"
QT_MOC_LITERAL(9, 90, 4), // "ymax"
QT_MOC_LITERAL(10, 95, 9), // "setLength"
QT_MOC_LITERAL(11, 105, 5), // "_size"
QT_MOC_LITERAL(12, 111, 11), // "setSampleAt"
QT_MOC_LITERAL(13, 123, 1), // "x"
QT_MOC_LITERAL(14, 125, 3), // "val"
QT_MOC_LITERAL(15, 129, 10), // "setSamples"
QT_MOC_LITERAL(16, 140, 12), // "const float*"
QT_MOC_LITERAL(17, 153, 6), // "_value"
QT_MOC_LITERAL(18, 160, 13), // "setWaveToSine"
QT_MOC_LITERAL(19, 174, 17), // "setWaveToTriangle"
QT_MOC_LITERAL(20, 192, 12), // "setWaveToSaw"
QT_MOC_LITERAL(21, 205, 15), // "setWaveToSquare"
QT_MOC_LITERAL(22, 221, 14), // "setWaveToNoise"
QT_MOC_LITERAL(23, 236, 13), // "setWaveToUser"
QT_MOC_LITERAL(24, 250, 6), // "smooth"
QT_MOC_LITERAL(25, 257, 15), // "smoothNonCyclic"
QT_MOC_LITERAL(26, 273, 9), // "normalize"
QT_MOC_LITERAL(27, 283, 6), // "invert"
QT_MOC_LITERAL(28, 290, 10), // "shiftPhase"
QT_MOC_LITERAL(29, 301, 4), // "_deg"
QT_MOC_LITERAL(30, 306, 5), // "clear"
QT_MOC_LITERAL(31, 312, 14) // "clearInvisible"

    },
    "lmms::graphModel\0lengthChanged\0\0"
    "samplesChanged\0startPos\0endPos\0"
    "rangeChanged\0setRange\0ymin\0ymax\0"
    "setLength\0_size\0setSampleAt\0x\0val\0"
    "setSamples\0const float*\0_value\0"
    "setWaveToSine\0setWaveToTriangle\0"
    "setWaveToSaw\0setWaveToSquare\0"
    "setWaveToNoise\0setWaveToUser\0smooth\0"
    "smoothNonCyclic\0normalize\0invert\0"
    "shiftPhase\0_deg\0clear\0clearInvisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__graphModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    2,  115,    2, 0x06 /* Public */,
       6,    0,  120,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,  121,    2, 0x0a /* Public */,
      10,    1,  126,    2, 0x0a /* Public */,
      12,    2,  129,    2, 0x0a /* Public */,
      15,    1,  134,    2, 0x0a /* Public */,
      18,    0,  137,    2, 0x0a /* Public */,
      19,    0,  138,    2, 0x0a /* Public */,
      20,    0,  139,    2, 0x0a /* Public */,
      21,    0,  140,    2, 0x0a /* Public */,
      22,    0,  141,    2, 0x0a /* Public */,
      23,    0,  142,    2, 0x0a /* Public */,
      24,    0,  143,    2, 0x0a /* Public */,
      25,    0,  144,    2, 0x0a /* Public */,
      26,    0,  145,    2, 0x0a /* Public */,
      27,    0,  146,    2, 0x0a /* Public */,
      28,    1,  147,    2, 0x0a /* Public */,
      30,    0,  150,    2, 0x0a /* Public */,
      31,    0,  151,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float,    8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::graphModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<graphModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->lengthChanged(); break;
        case 1: _t->samplesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->rangeChanged(); break;
        case 3: _t->setRange((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 4: _t->setLength((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setSampleAt((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 6: _t->setSamples((*reinterpret_cast< const float*(*)>(_a[1]))); break;
        case 7: _t->setWaveToSine(); break;
        case 8: _t->setWaveToTriangle(); break;
        case 9: _t->setWaveToSaw(); break;
        case 10: _t->setWaveToSquare(); break;
        case 11: _t->setWaveToNoise(); break;
        case 12: { QString _r = _t->setWaveToUser();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->smooth(); break;
        case 14: _t->smoothNonCyclic(); break;
        case 15: _t->normalize(); break;
        case 16: _t->invert(); break;
        case 17: _t->shiftPhase((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->clear(); break;
        case 19: _t->clearInvisible(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (graphModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphModel::lengthChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (graphModel::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphModel::samplesChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (graphModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&graphModel::rangeChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::graphModel::staticMetaObject = { {
    QMetaObject::SuperData::link<Model::staticMetaObject>(),
    qt_meta_stringdata_lmms__graphModel.data,
    qt_meta_data_lmms__graphModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::graphModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::graphModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__graphModel.stringdata0))
        return static_cast<void*>(this);
    return Model::qt_metacast(_clname);
}

int lmms::graphModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Model::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void lmms::graphModel::lengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::graphModel::samplesChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void lmms::graphModel::rangeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
