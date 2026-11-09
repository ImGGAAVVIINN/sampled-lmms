/****************************************************************************
** Meta object code from reading C++ file 'SetupDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/SetupDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SetupDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__SetupDialog_t {
    QByteArrayData data[67];
    char stringdata0[1061];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__SetupDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__SetupDialog_t qt_meta_stringdata_lmms__gui__SetupDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "lmms::gui::SetupDialog"
QT_MOC_LITERAL(1, 23, 6), // "accept"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "toggleTooltips"
QT_MOC_LITERAL(4, 46, 7), // "enabled"
QT_MOC_LITERAL(5, 54, 21), // "toggleDisplayWaveform"
QT_MOC_LITERAL(6, 76, 16), // "toggleNoteLabels"
QT_MOC_LITERAL(7, 93, 20), // "toggleShowFaderTicks"
QT_MOC_LITERAL(8, 114, 25), // "toggleCompactTrackButtons"
QT_MOC_LITERAL(9, 140, 30), // "toggleOneInstrumentTrackWindow"
QT_MOC_LITERAL(10, 171, 20), // "toggleSideBarOnRight"
QT_MOC_LITERAL(11, 192, 23), // "toggleLetPreviewsFinish"
QT_MOC_LITERAL(12, 216, 24), // "toggleSoloLegacyBehavior"
QT_MOC_LITERAL(13, 241, 26), // "toggleTrackDeletionWarning"
QT_MOC_LITERAL(14, 268, 33), // "toggleMixerChannelDeletionWar..."
QT_MOC_LITERAL(15, 302, 10), // "toggleMMPZ"
QT_MOC_LITERAL(16, 313, 19), // "toggleDisableBackup"
QT_MOC_LITERAL(17, 333, 21), // "toggleOpenLastProject"
QT_MOC_LITERAL(18, 355, 21), // "detachBehaviorChanged"
QT_MOC_LITERAL(19, 377, 21), // "loopMarkerModeChanged"
QT_MOC_LITERAL(20, 399, 11), // "setLanguage"
QT_MOC_LITERAL(21, 411, 4), // "lang"
QT_MOC_LITERAL(22, 416, 19), // "setAutoSaveInterval"
QT_MOC_LITERAL(23, 436, 4), // "time"
QT_MOC_LITERAL(24, 441, 13), // "resetAutoSave"
QT_MOC_LITERAL(25, 455, 14), // "toggleAutoSave"
QT_MOC_LITERAL(26, 470, 21), // "toggleRunningAutoSave"
QT_MOC_LITERAL(27, 492, 18), // "toggleSmoothScroll"
QT_MOC_LITERAL(28, 511, 16), // "toggleAnimateAFP"
QT_MOC_LITERAL(29, 528, 21), // "vstEmbedMethodChanged"
QT_MOC_LITERAL(30, 550, 20), // "toggleVSTAlwaysOnTop"
QT_MOC_LITERAL(31, 571, 2), // "en"
QT_MOC_LITERAL(32, 574, 21), // "toggleDisableAutoQuit"
QT_MOC_LITERAL(33, 596, 21), // "toggleMixSanitization"
QT_MOC_LITERAL(34, 618, 21), // "audioInterfaceChanged"
QT_MOC_LITERAL(35, 640, 6), // "driver"
QT_MOC_LITERAL(36, 647, 23), // "updateBufferSizeWarning"
QT_MOC_LITERAL(37, 671, 5), // "value"
QT_MOC_LITERAL(38, 677, 13), // "setBufferSize"
QT_MOC_LITERAL(39, 691, 15), // "resetBufferSize"
QT_MOC_LITERAL(40, 707, 20), // "midiInterfaceChanged"
QT_MOC_LITERAL(41, 728, 26), // "toggleMidiAutoQuantization"
QT_MOC_LITERAL(42, 755, 14), // "openWorkingDir"
QT_MOC_LITERAL(43, 770, 13), // "setWorkingDir"
QT_MOC_LITERAL(44, 784, 10), // "workingDir"
QT_MOC_LITERAL(45, 795, 10), // "openVSTDir"
QT_MOC_LITERAL(46, 806, 9), // "setVSTDir"
QT_MOC_LITERAL(47, 816, 6), // "vstDir"
QT_MOC_LITERAL(48, 823, 13), // "openLADSPADir"
QT_MOC_LITERAL(49, 837, 12), // "setLADSPADir"
QT_MOC_LITERAL(50, 850, 9), // "ladspaDir"
QT_MOC_LITERAL(51, 860, 10), // "openSF2Dir"
QT_MOC_LITERAL(52, 871, 9), // "setSF2Dir"
QT_MOC_LITERAL(53, 881, 6), // "sf2Dir"
QT_MOC_LITERAL(54, 888, 11), // "openSF2File"
QT_MOC_LITERAL(55, 900, 10), // "setSF2File"
QT_MOC_LITERAL(56, 911, 7), // "sf2File"
QT_MOC_LITERAL(57, 919, 10), // "openGIGDir"
QT_MOC_LITERAL(58, 930, 9), // "setGIGDir"
QT_MOC_LITERAL(59, 940, 6), // "gigDir"
QT_MOC_LITERAL(60, 947, 12), // "openThemeDir"
QT_MOC_LITERAL(61, 960, 11), // "setThemeDir"
QT_MOC_LITERAL(62, 972, 8), // "themeDir"
QT_MOC_LITERAL(63, 981, 21), // "openBackgroundPicFile"
QT_MOC_LITERAL(64, 1003, 20), // "setBackgroundPicFile"
QT_MOC_LITERAL(65, 1024, 17), // "backgroundPicFile"
QT_MOC_LITERAL(66, 1042, 18) // "showRestartWarning"

    },
    "lmms::gui::SetupDialog\0accept\0\0"
    "toggleTooltips\0enabled\0toggleDisplayWaveform\0"
    "toggleNoteLabels\0toggleShowFaderTicks\0"
    "toggleCompactTrackButtons\0"
    "toggleOneInstrumentTrackWindow\0"
    "toggleSideBarOnRight\0toggleLetPreviewsFinish\0"
    "toggleSoloLegacyBehavior\0"
    "toggleTrackDeletionWarning\0"
    "toggleMixerChannelDeletionWarning\0"
    "toggleMMPZ\0toggleDisableBackup\0"
    "toggleOpenLastProject\0detachBehaviorChanged\0"
    "loopMarkerModeChanged\0setLanguage\0"
    "lang\0setAutoSaveInterval\0time\0"
    "resetAutoSave\0toggleAutoSave\0"
    "toggleRunningAutoSave\0toggleSmoothScroll\0"
    "toggleAnimateAFP\0vstEmbedMethodChanged\0"
    "toggleVSTAlwaysOnTop\0en\0toggleDisableAutoQuit\0"
    "toggleMixSanitization\0audioInterfaceChanged\0"
    "driver\0updateBufferSizeWarning\0value\0"
    "setBufferSize\0resetBufferSize\0"
    "midiInterfaceChanged\0toggleMidiAutoQuantization\0"
    "openWorkingDir\0setWorkingDir\0workingDir\0"
    "openVSTDir\0setVSTDir\0vstDir\0openLADSPADir\0"
    "setLADSPADir\0ladspaDir\0openSF2Dir\0"
    "setSF2Dir\0sf2Dir\0openSF2File\0setSF2File\0"
    "sf2File\0openGIGDir\0setGIGDir\0gigDir\0"
    "openThemeDir\0setThemeDir\0themeDir\0"
    "openBackgroundPicFile\0setBackgroundPicFile\0"
    "backgroundPicFile\0showRestartWarning"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__SetupDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  269,    2, 0x09 /* Protected */,
       3,    1,  270,    2, 0x08 /* Private */,
       5,    1,  273,    2, 0x08 /* Private */,
       6,    1,  276,    2, 0x08 /* Private */,
       7,    1,  279,    2, 0x08 /* Private */,
       8,    1,  282,    2, 0x08 /* Private */,
       9,    1,  285,    2, 0x08 /* Private */,
      10,    1,  288,    2, 0x08 /* Private */,
      11,    1,  291,    2, 0x08 /* Private */,
      12,    1,  294,    2, 0x08 /* Private */,
      13,    1,  297,    2, 0x08 /* Private */,
      14,    1,  300,    2, 0x08 /* Private */,
      15,    1,  303,    2, 0x08 /* Private */,
      16,    1,  306,    2, 0x08 /* Private */,
      17,    1,  309,    2, 0x08 /* Private */,
      18,    0,  312,    2, 0x08 /* Private */,
      19,    0,  313,    2, 0x08 /* Private */,
      20,    1,  314,    2, 0x08 /* Private */,
      22,    1,  317,    2, 0x08 /* Private */,
      24,    0,  320,    2, 0x08 /* Private */,
      25,    1,  321,    2, 0x08 /* Private */,
      26,    1,  324,    2, 0x08 /* Private */,
      27,    1,  327,    2, 0x08 /* Private */,
      28,    1,  330,    2, 0x08 /* Private */,
      29,    0,  333,    2, 0x08 /* Private */,
      30,    1,  334,    2, 0x08 /* Private */,
      32,    1,  337,    2, 0x08 /* Private */,
      33,    1,  340,    2, 0x08 /* Private */,
      34,    1,  343,    2, 0x08 /* Private */,
      36,    1,  346,    2, 0x08 /* Private */,
      38,    1,  349,    2, 0x08 /* Private */,
      39,    0,  352,    2, 0x08 /* Private */,
      40,    1,  353,    2, 0x08 /* Private */,
      41,    1,  356,    2, 0x08 /* Private */,
      42,    0,  359,    2, 0x08 /* Private */,
      43,    1,  360,    2, 0x08 /* Private */,
      45,    0,  363,    2, 0x08 /* Private */,
      46,    1,  364,    2, 0x08 /* Private */,
      48,    0,  367,    2, 0x08 /* Private */,
      49,    1,  368,    2, 0x08 /* Private */,
      51,    0,  371,    2, 0x08 /* Private */,
      52,    1,  372,    2, 0x08 /* Private */,
      54,    0,  375,    2, 0x08 /* Private */,
      55,    1,  376,    2, 0x08 /* Private */,
      57,    0,  379,    2, 0x08 /* Private */,
      58,    1,  380,    2, 0x08 /* Private */,
      60,    0,  383,    2, 0x08 /* Private */,
      61,    1,  384,    2, 0x08 /* Private */,
      63,    0,  387,    2, 0x08 /* Private */,
      64,    1,  388,    2, 0x08 /* Private */,
      66,    0,  391,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   31,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   47,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   56,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   59,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   62,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   65,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::SetupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SetupDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->toggleTooltips((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->toggleDisplayWaveform((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->toggleNoteLabels((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->toggleShowFaderTicks((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->toggleCompactTrackButtons((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->toggleOneInstrumentTrackWindow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->toggleSideBarOnRight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->toggleLetPreviewsFinish((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->toggleSoloLegacyBehavior((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->toggleTrackDeletionWarning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->toggleMixerChannelDeletionWarning((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->toggleMMPZ((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->toggleDisableBackup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->toggleOpenLastProject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->detachBehaviorChanged(); break;
        case 16: _t->loopMarkerModeChanged(); break;
        case 17: _t->setLanguage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->setAutoSaveInterval((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->resetAutoSave(); break;
        case 20: _t->toggleAutoSave((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->toggleRunningAutoSave((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->toggleSmoothScroll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->toggleAnimateAFP((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->vstEmbedMethodChanged(); break;
        case 25: _t->toggleVSTAlwaysOnTop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->toggleDisableAutoQuit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->toggleMixSanitization((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->audioInterfaceChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: _t->updateBufferSizeWarning((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->setBufferSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->resetBufferSize(); break;
        case 32: _t->midiInterfaceChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->toggleMidiAutoQuantization((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->openWorkingDir(); break;
        case 35: _t->setWorkingDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 36: _t->openVSTDir(); break;
        case 37: _t->setVSTDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 38: _t->openLADSPADir(); break;
        case 39: _t->setLADSPADir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 40: _t->openSF2Dir(); break;
        case 41: _t->setSF2Dir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 42: _t->openSF2File(); break;
        case 43: _t->setSF2File((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 44: _t->openGIGDir(); break;
        case 45: _t->setGIGDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 46: _t->openThemeDir(); break;
        case 47: _t->setThemeDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 48: _t->openBackgroundPicFile(); break;
        case 49: _t->setBackgroundPicFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 50: _t->showRestartWarning(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::SetupDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__SetupDialog.data,
    qt_meta_data_lmms__gui__SetupDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::SetupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::SetupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__SetupDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int lmms::gui::SetupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 51;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
