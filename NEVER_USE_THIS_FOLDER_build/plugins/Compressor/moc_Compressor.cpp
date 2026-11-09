/****************************************************************************
** Meta object code from reading C++ file 'Compressor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../plugins/Compressor/Compressor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Compressor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__CompressorEffect_t {
    QByteArrayData data[20];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__CompressorEffect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__CompressorEffect_t qt_meta_stringdata_lmms__CompressorEffect = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::CompressorEffect"
QT_MOC_LITERAL(1, 23, 14), // "calcAutoMakeup"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 10), // "calcAttack"
QT_MOC_LITERAL(4, 50, 11), // "calcRelease"
QT_MOC_LITERAL(5, 62, 14), // "calcAutoAttack"
QT_MOC_LITERAL(6, 77, 15), // "calcAutoRelease"
QT_MOC_LITERAL(7, 93, 8), // "calcHold"
QT_MOC_LITERAL(8, 102, 11), // "calcOutGain"
QT_MOC_LITERAL(9, 114, 9), // "calcRatio"
QT_MOC_LITERAL(10, 124, 9), // "calcRange"
QT_MOC_LITERAL(11, 134, 9), // "resizeRMS"
QT_MOC_LITERAL(12, 144, 19), // "calcLookaheadLength"
QT_MOC_LITERAL(13, 164, 13), // "calcThreshold"
QT_MOC_LITERAL(14, 178, 8), // "calcKnee"
QT_MOC_LITERAL(15, 187, 10), // "calcInGain"
QT_MOC_LITERAL(16, 198, 14), // "calcTiltCoeffs"
QT_MOC_LITERAL(17, 213, 7), // "calcMix"
QT_MOC_LITERAL(18, 221, 16), // "changeSampleRate"
QT_MOC_LITERAL(19, 238, 10) // "redrawKnee"

    },
    "lmms::CompressorEffect\0calcAutoMakeup\0"
    "\0calcAttack\0calcRelease\0calcAutoAttack\0"
    "calcAutoRelease\0calcHold\0calcOutGain\0"
    "calcRatio\0calcRange\0resizeRMS\0"
    "calcLookaheadLength\0calcThreshold\0"
    "calcKnee\0calcInGain\0calcTiltCoeffs\0"
    "calcMix\0changeSampleRate\0redrawKnee"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__CompressorEffect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::CompressorEffect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CompressorEffect *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->calcAutoMakeup(); break;
        case 1: _t->calcAttack(); break;
        case 2: _t->calcRelease(); break;
        case 3: _t->calcAutoAttack(); break;
        case 4: _t->calcAutoRelease(); break;
        case 5: _t->calcHold(); break;
        case 6: _t->calcOutGain(); break;
        case 7: _t->calcRatio(); break;
        case 8: _t->calcRange(); break;
        case 9: _t->resizeRMS(); break;
        case 10: _t->calcLookaheadLength(); break;
        case 11: _t->calcThreshold(); break;
        case 12: _t->calcKnee(); break;
        case 13: _t->calcInGain(); break;
        case 14: _t->calcTiltCoeffs(); break;
        case 15: _t->calcMix(); break;
        case 16: _t->changeSampleRate(); break;
        case 17: _t->redrawKnee(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject lmms::CompressorEffect::staticMetaObject = { {
    QMetaObject::SuperData::link<Effect::staticMetaObject>(),
    qt_meta_stringdata_lmms__CompressorEffect.data,
    qt_meta_data_lmms__CompressorEffect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::CompressorEffect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::CompressorEffect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__CompressorEffect.stringdata0))
        return static_cast<void*>(this);
    return Effect::qt_metacast(_clname);
}

int lmms::CompressorEffect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Effect::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
