/****************************************************************************
** Meta object code from reading C++ file 'VstPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../plugins/VstBase/VstPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VstPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__VstPlugin_t {
    QByteArrayData data[25];
    char stringdata0[288];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__VstPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__VstPlugin_t qt_meta_stringdata_lmms__VstPlugin = {
    {
QT_MOC_LITERAL(0, 0, 15), // "lmms::VstPlugin"
QT_MOC_LITERAL(1, 16, 8), // "setTempo"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "lmms::bpm_t"
QT_MOC_LITERAL(4, 38, 4), // "_bpm"
QT_MOC_LITERAL(5, 43, 16), // "updateSampleRate"
QT_MOC_LITERAL(6, 60, 10), // "openPreset"
QT_MOC_LITERAL(7, 71, 10), // "setProgram"
QT_MOC_LITERAL(8, 82, 5), // "index"
QT_MOC_LITERAL(9, 88, 13), // "rotateProgram"
QT_MOC_LITERAL(10, 102, 6), // "offset"
QT_MOC_LITERAL(11, 109, 16), // "loadProgramNames"
QT_MOC_LITERAL(12, 126, 19), // "loadParameterLabels"
QT_MOC_LITERAL(13, 146, 21), // "loadParameterDisplays"
QT_MOC_LITERAL(14, 168, 20), // "updateParameterLabel"
QT_MOC_LITERAL(15, 189, 22), // "updateParameterDisplay"
QT_MOC_LITERAL(16, 212, 10), // "savePreset"
QT_MOC_LITERAL(17, 223, 8), // "setParam"
QT_MOC_LITERAL(18, 232, 1), // "i"
QT_MOC_LITERAL(19, 234, 1), // "f"
QT_MOC_LITERAL(20, 236, 10), // "idleUpdate"
QT_MOC_LITERAL(21, 247, 6), // "showUI"
QT_MOC_LITERAL(22, 254, 6), // "hideUI"
QT_MOC_LITERAL(23, 261, 8), // "toggleUI"
QT_MOC_LITERAL(24, 270, 17) // "handleClientEmbed"

    },
    "lmms::VstPlugin\0setTempo\0\0lmms::bpm_t\0"
    "_bpm\0updateSampleRate\0openPreset\0"
    "setProgram\0index\0rotateProgram\0offset\0"
    "loadProgramNames\0loadParameterLabels\0"
    "loadParameterDisplays\0updateParameterLabel\0"
    "updateParameterDisplay\0savePreset\0"
    "setParam\0i\0f\0idleUpdate\0showUI\0hideUI\0"
    "toggleUI\0handleClientEmbed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__VstPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x0a /* Public */,
       5,    0,  102,    2, 0x0a /* Public */,
       6,    0,  103,    2, 0x0a /* Public */,
       7,    1,  104,    2, 0x0a /* Public */,
       9,    1,  107,    2, 0x0a /* Public */,
      11,    0,  110,    2, 0x0a /* Public */,
      12,    0,  111,    2, 0x0a /* Public */,
      13,    0,  112,    2, 0x0a /* Public */,
      14,    1,  113,    2, 0x0a /* Public */,
      15,    1,  116,    2, 0x0a /* Public */,
      16,    0,  119,    2, 0x0a /* Public */,
      17,    2,  120,    2, 0x0a /* Public */,
      20,    0,  125,    2, 0x0a /* Public */,
      21,    0,  126,    2, 0x0a /* Public */,
      22,    0,  127,    2, 0x0a /* Public */,
      23,    0,  128,    2, 0x0a /* Public */,
      24,    0,  129,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::VstPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VstPlugin *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setTempo((*reinterpret_cast< lmms::bpm_t(*)>(_a[1]))); break;
        case 1: _t->updateSampleRate(); break;
        case 2: _t->openPreset(); break;
        case 3: _t->setProgram((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->rotateProgram((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->loadProgramNames(); break;
        case 6: _t->loadParameterLabels(); break;
        case 7: _t->loadParameterDisplays(); break;
        case 8: _t->updateParameterLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->updateParameterDisplay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->savePreset(); break;
        case 11: _t->setParam((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 12: _t->idleUpdate(); break;
        case 13: _t->showUI(); break;
        case 14: _t->hideUI(); break;
        case 15: _t->toggleUI(); break;
        case 16: _t->handleClientEmbed(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::VstPlugin::staticMetaObject = { {
    QMetaObject::SuperData::link<RemotePlugin::staticMetaObject>(),
    qt_meta_stringdata_lmms__VstPlugin.data,
    qt_meta_data_lmms__VstPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::VstPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::VstPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__VstPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "JournallingObject"))
        return static_cast< JournallingObject*>(this);
    return RemotePlugin::qt_metacast(_clname);
}

int lmms::VstPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = RemotePlugin::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
