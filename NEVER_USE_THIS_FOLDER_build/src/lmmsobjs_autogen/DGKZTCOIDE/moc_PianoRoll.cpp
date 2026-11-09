/****************************************************************************
** Meta object code from reading C++ file 'PianoRoll.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/PianoRoll.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PianoRoll.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__PianoRoll_t {
    QByteArrayData data[91];
    char stringdata0[1412];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__PianoRoll_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__PianoRoll_t qt_meta_stringdata_lmms__gui__PianoRoll = {
    {
QT_MOC_LITERAL(0, 0, 20), // "lmms::gui::PianoRoll"
QT_MOC_LITERAL(1, 21, 22), // "currentMidiClipChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 12), // "ghostClipSet"
QT_MOC_LITERAL(4, 58, 33), // "semiToneMarkerMenuScaleSetEna..."
QT_MOC_LITERAL(5, 92, 33), // "semiToneMarkerMenuChordSetEna..."
QT_MOC_LITERAL(6, 126, 4), // "play"
QT_MOC_LITERAL(7, 131, 6), // "record"
QT_MOC_LITERAL(8, 138, 15), // "recordAccompany"
QT_MOC_LITERAL(9, 154, 19), // "toggleStepRecording"
QT_MOC_LITERAL(10, 174, 4), // "stop"
QT_MOC_LITERAL(11, 179, 15), // "startRecordNote"
QT_MOC_LITERAL(12, 195, 10), // "lmms::Note"
QT_MOC_LITERAL(13, 206, 1), // "n"
QT_MOC_LITERAL(14, 208, 16), // "finishRecordNote"
QT_MOC_LITERAL(15, 225, 11), // "horScrolled"
QT_MOC_LITERAL(16, 237, 7), // "new_pos"
QT_MOC_LITERAL(17, 245, 11), // "verScrolled"
QT_MOC_LITERAL(18, 257, 11), // "setEditMode"
QT_MOC_LITERAL(19, 269, 4), // "mode"
QT_MOC_LITERAL(20, 274, 17), // "copySelectedNotes"
QT_MOC_LITERAL(21, 292, 16), // "cutSelectedNotes"
QT_MOC_LITERAL(22, 309, 10), // "pasteNotes"
QT_MOC_LITERAL(23, 320, 19), // "deleteSelectedNotes"
QT_MOC_LITERAL(24, 340, 14), // "updatePosition"
QT_MOC_LITERAL(25, 355, 23), // "updatePositionAccompany"
QT_MOC_LITERAL(26, 379, 27), // "updatePositionStepRecording"
QT_MOC_LITERAL(27, 407, 13), // "lmms::TimePos"
QT_MOC_LITERAL(28, 421, 1), // "t"
QT_MOC_LITERAL(29, 423, 14), // "zoomingChanged"
QT_MOC_LITERAL(30, 438, 15), // "zoomingYChanged"
QT_MOC_LITERAL(31, 454, 15), // "quantizeChanged"
QT_MOC_LITERAL(32, 470, 17), // "noteLengthChanged"
QT_MOC_LITERAL(33, 488, 10), // "keyChanged"
QT_MOC_LITERAL(34, 499, 13), // "quantizeNotes"
QT_MOC_LITERAL(35, 513, 14), // "QuantizeAction"
QT_MOC_LITERAL(36, 528, 24), // "updateSemiToneMarkerMenu"
QT_MOC_LITERAL(37, 553, 18), // "changeNoteEditMode"
QT_MOC_LITERAL(38, 572, 1), // "i"
QT_MOC_LITERAL(39, 574, 12), // "markSemiTone"
QT_MOC_LITERAL(40, 587, 20), // "SemiToneMarkerAction"
QT_MOC_LITERAL(41, 608, 8), // "fromMenu"
QT_MOC_LITERAL(42, 617, 12), // "hideMidiClip"
QT_MOC_LITERAL(43, 630, 15), // "lmms::MidiClip*"
QT_MOC_LITERAL(44, 646, 4), // "clip"
QT_MOC_LITERAL(45, 651, 22), // "selectRegionFromPixels"
QT_MOC_LITERAL(46, 674, 6), // "xStart"
QT_MOC_LITERAL(47, 681, 4), // "xEnd"
QT_MOC_LITERAL(48, 686, 14), // "clearGhostClip"
QT_MOC_LITERAL(49, 701, 9), // "glueNotes"
QT_MOC_LITERAL(50, 711, 14), // "fitNoteLengths"
QT_MOC_LITERAL(51, 726, 4), // "fill"
QT_MOC_LITERAL(52, 731, 12), // "reverseNotes"
QT_MOC_LITERAL(53, 744, 20), // "constrainNoteLengths"
QT_MOC_LITERAL(54, 765, 12), // "constrainMax"
QT_MOC_LITERAL(55, 778, 14), // "changeSnapMode"
QT_MOC_LITERAL(56, 793, 12), // "barLineColor"
QT_MOC_LITERAL(57, 806, 13), // "beatLineColor"
QT_MOC_LITERAL(58, 820, 9), // "lineColor"
QT_MOC_LITERAL(59, 830, 13), // "noteModeColor"
QT_MOC_LITERAL(60, 844, 9), // "noteColor"
QT_MOC_LITERAL(61, 854, 13), // "stepNoteColor"
QT_MOC_LITERAL(62, 868, 20), // "currentStepNoteColor"
QT_MOC_LITERAL(63, 889, 14), // "ghostNoteColor"
QT_MOC_LITERAL(64, 904, 13), // "noteTextColor"
QT_MOC_LITERAL(65, 918, 18), // "ghostNoteTextColor"
QT_MOC_LITERAL(66, 937, 8), // "barColor"
QT_MOC_LITERAL(67, 946, 17), // "selectedNoteColor"
QT_MOC_LITERAL(68, 964, 9), // "textColor"
QT_MOC_LITERAL(69, 974, 14), // "textColorLight"
QT_MOC_LITERAL(70, 989, 10), // "textShadow"
QT_MOC_LITERAL(71, 1000, 19), // "markedSemitoneColor"
QT_MOC_LITERAL(72, 1020, 12), // "knifeCutLine"
QT_MOC_LITERAL(73, 1033, 11), // "noteOpacity"
QT_MOC_LITERAL(74, 1045, 11), // "noteBorders"
QT_MOC_LITERAL(75, 1057, 16), // "ghostNoteOpacity"
QT_MOC_LITERAL(76, 1074, 16), // "ghostNoteBorders"
QT_MOC_LITERAL(77, 1091, 15), // "backgroundShade"
QT_MOC_LITERAL(78, 1107, 16), // "outOfBoundsShade"
QT_MOC_LITERAL(79, 1124, 13), // "whiteKeyWidth"
QT_MOC_LITERAL(80, 1138, 25), // "whiteKeyInactiveTextColor"
QT_MOC_LITERAL(81, 1164, 26), // "whiteKeyInactiveTextShadow"
QT_MOC_LITERAL(82, 1191, 26), // "whiteKeyInactiveBackground"
QT_MOC_LITERAL(83, 1218, 23), // "whiteKeyActiveTextColor"
QT_MOC_LITERAL(84, 1242, 24), // "whiteKeyActiveTextShadow"
QT_MOC_LITERAL(85, 1267, 24), // "whiteKeyActiveBackground"
QT_MOC_LITERAL(86, 1292, 26), // "whiteKeyDisabledBackground"
QT_MOC_LITERAL(87, 1319, 13), // "blackKeyWidth"
QT_MOC_LITERAL(88, 1333, 26), // "blackKeyInactiveBackground"
QT_MOC_LITERAL(89, 1360, 24), // "blackKeyActiveBackground"
QT_MOC_LITERAL(90, 1385, 26) // "blackKeyDisabledBackground"

    },
    "lmms::gui::PianoRoll\0currentMidiClipChanged\0"
    "\0ghostClipSet\0semiToneMarkerMenuScaleSetEnabled\0"
    "semiToneMarkerMenuChordSetEnabled\0"
    "play\0record\0recordAccompany\0"
    "toggleStepRecording\0stop\0startRecordNote\0"
    "lmms::Note\0n\0finishRecordNote\0horScrolled\0"
    "new_pos\0verScrolled\0setEditMode\0mode\0"
    "copySelectedNotes\0cutSelectedNotes\0"
    "pasteNotes\0deleteSelectedNotes\0"
    "updatePosition\0updatePositionAccompany\0"
    "updatePositionStepRecording\0lmms::TimePos\0"
    "t\0zoomingChanged\0zoomingYChanged\0"
    "quantizeChanged\0noteLengthChanged\0"
    "keyChanged\0quantizeNotes\0QuantizeAction\0"
    "updateSemiToneMarkerMenu\0changeNoteEditMode\0"
    "i\0markSemiTone\0SemiToneMarkerAction\0"
    "fromMenu\0hideMidiClip\0lmms::MidiClip*\0"
    "clip\0selectRegionFromPixels\0xStart\0"
    "xEnd\0clearGhostClip\0glueNotes\0"
    "fitNoteLengths\0fill\0reverseNotes\0"
    "constrainNoteLengths\0constrainMax\0"
    "changeSnapMode\0barLineColor\0beatLineColor\0"
    "lineColor\0noteModeColor\0noteColor\0"
    "stepNoteColor\0currentStepNoteColor\0"
    "ghostNoteColor\0noteTextColor\0"
    "ghostNoteTextColor\0barColor\0"
    "selectedNoteColor\0textColor\0textColorLight\0"
    "textShadow\0markedSemitoneColor\0"
    "knifeCutLine\0noteOpacity\0noteBorders\0"
    "ghostNoteOpacity\0ghostNoteBorders\0"
    "backgroundShade\0outOfBoundsShade\0"
    "whiteKeyWidth\0whiteKeyInactiveTextColor\0"
    "whiteKeyInactiveTextShadow\0"
    "whiteKeyInactiveBackground\0"
    "whiteKeyActiveTextColor\0"
    "whiteKeyActiveTextShadow\0"
    "whiteKeyActiveBackground\0"
    "whiteKeyDisabledBackground\0blackKeyWidth\0"
    "blackKeyInactiveBackground\0"
    "blackKeyActiveBackground\0"
    "blackKeyDisabledBackground"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__PianoRoll[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
      35,  292, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  214,    2, 0x06 /* Public */,
       3,    1,  215,    2, 0x06 /* Public */,
       4,    1,  218,    2, 0x06 /* Public */,
       5,    1,  221,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  224,    2, 0x09 /* Protected */,
       7,    0,  225,    2, 0x09 /* Protected */,
       8,    0,  226,    2, 0x09 /* Protected */,
       9,    0,  227,    2, 0x09 /* Protected */,
      10,    0,  228,    2, 0x09 /* Protected */,
      11,    1,  229,    2, 0x09 /* Protected */,
      14,    1,  232,    2, 0x09 /* Protected */,
      15,    1,  235,    2, 0x09 /* Protected */,
      17,    1,  238,    2, 0x09 /* Protected */,
      18,    1,  241,    2, 0x09 /* Protected */,
      20,    0,  244,    2, 0x09 /* Protected */,
      21,    0,  245,    2, 0x09 /* Protected */,
      22,    0,  246,    2, 0x09 /* Protected */,
      23,    0,  247,    2, 0x09 /* Protected */,
      24,    0,  248,    2, 0x09 /* Protected */,
      25,    0,  249,    2, 0x09 /* Protected */,
      26,    1,  250,    2, 0x09 /* Protected */,
      29,    0,  253,    2, 0x09 /* Protected */,
      30,    0,  254,    2, 0x09 /* Protected */,
      31,    0,  255,    2, 0x09 /* Protected */,
      32,    0,  256,    2, 0x09 /* Protected */,
      33,    0,  257,    2, 0x09 /* Protected */,
      34,    1,  258,    2, 0x09 /* Protected */,
      34,    0,  261,    2, 0x29 /* Protected | MethodCloned */,
      36,    0,  262,    2, 0x09 /* Protected */,
      37,    1,  263,    2, 0x09 /* Protected */,
      39,    2,  266,    2, 0x09 /* Protected */,
      39,    1,  271,    2, 0x29 /* Protected | MethodCloned */,
      42,    1,  274,    2, 0x09 /* Protected */,
      45,    2,  277,    2, 0x09 /* Protected */,
      48,    0,  282,    2, 0x09 /* Protected */,
      49,    0,  283,    2, 0x09 /* Protected */,
      50,    1,  284,    2, 0x09 /* Protected */,
      52,    0,  287,    2, 0x09 /* Protected */,
      53,    1,  288,    2, 0x09 /* Protected */,
      55,    0,  291,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, 0x80000000 | 40, QMetaType::Bool,   38,   41,
    QMetaType::Void, 0x80000000 | 40,   38,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   46,   47,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   51,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   54,
    QMetaType::Void,

 // properties: name, type, flags
      56, QMetaType::QColor, 0x00095003,
      57, QMetaType::QColor, 0x00095003,
      58, QMetaType::QColor, 0x00095003,
      59, QMetaType::QColor, 0x00095003,
      60, QMetaType::QColor, 0x00095003,
      61, QMetaType::QColor, 0x00095003,
      62, QMetaType::QColor, 0x00095003,
      63, QMetaType::QColor, 0x00095003,
      64, QMetaType::QColor, 0x00095003,
      65, QMetaType::QColor, 0x00095003,
      66, QMetaType::QColor, 0x00095003,
      67, QMetaType::QColor, 0x00095003,
      68, QMetaType::QColor, 0x00095003,
      69, QMetaType::QColor, 0x00095003,
      70, QMetaType::QColor, 0x00095003,
      71, QMetaType::QColor, 0x00095003,
      72, QMetaType::QColor, 0x00095003,
      73, QMetaType::Int, 0x00095003,
      74, QMetaType::Bool, 0x00095003,
      75, QMetaType::Int, 0x00095003,
      76, QMetaType::Bool, 0x00095003,
      77, QMetaType::QColor, 0x00095003,
      78, QMetaType::QColor, 0x00095003,
      79, QMetaType::Int, 0x00095003,
      80, QMetaType::QColor, 0x00095003,
      81, QMetaType::QColor, 0x00095003,
      82, QMetaType::QBrush, 0x00095003,
      83, QMetaType::QColor, 0x00095003,
      84, QMetaType::QColor, 0x00095003,
      85, QMetaType::QBrush, 0x00095003,
      86, QMetaType::QBrush, 0x00095003,
      87, QMetaType::Int, 0x00095003,
      88, QMetaType::QBrush, 0x00095003,
      89, QMetaType::QBrush, 0x00095003,
      90, QMetaType::QBrush, 0x00095003,

       0        // eod
};

void lmms::gui::PianoRoll::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PianoRoll *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentMidiClipChanged(); break;
        case 1: _t->ghostClipSet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->semiToneMarkerMenuScaleSetEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->semiToneMarkerMenuChordSetEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->play(); break;
        case 5: _t->record(); break;
        case 6: _t->recordAccompany(); break;
        case 7: { bool _r = _t->toggleStepRecording();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->stop(); break;
        case 9: _t->startRecordNote((*reinterpret_cast< const lmms::Note(*)>(_a[1]))); break;
        case 10: _t->finishRecordNote((*reinterpret_cast< const lmms::Note(*)>(_a[1]))); break;
        case 11: _t->horScrolled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->verScrolled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setEditMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->copySelectedNotes(); break;
        case 15: _t->cutSelectedNotes(); break;
        case 16: _t->pasteNotes(); break;
        case 17: { bool _r = _t->deleteSelectedNotes();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->updatePosition(); break;
        case 19: _t->updatePositionAccompany(); break;
        case 20: _t->updatePositionStepRecording((*reinterpret_cast< const lmms::TimePos(*)>(_a[1]))); break;
        case 21: _t->zoomingChanged(); break;
        case 22: _t->zoomingYChanged(); break;
        case 23: _t->quantizeChanged(); break;
        case 24: _t->noteLengthChanged(); break;
        case 25: _t->keyChanged(); break;
        case 26: _t->quantizeNotes((*reinterpret_cast< QuantizeAction(*)>(_a[1]))); break;
        case 27: _t->quantizeNotes(); break;
        case 28: _t->updateSemiToneMarkerMenu(); break;
        case 29: _t->changeNoteEditMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->markSemiTone((*reinterpret_cast< SemiToneMarkerAction(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 31: _t->markSemiTone((*reinterpret_cast< SemiToneMarkerAction(*)>(_a[1]))); break;
        case 32: _t->hideMidiClip((*reinterpret_cast< lmms::MidiClip*(*)>(_a[1]))); break;
        case 33: _t->selectRegionFromPixels((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 34: _t->clearGhostClip(); break;
        case 35: _t->glueNotes(); break;
        case 36: _t->fitNoteLengths((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: _t->reverseNotes(); break;
        case 38: _t->constrainNoteLengths((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->changeSnapMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PianoRoll::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PianoRoll::currentMidiClipChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PianoRoll::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PianoRoll::ghostClipSet)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PianoRoll::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PianoRoll::semiToneMarkerMenuScaleSetEnabled)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PianoRoll::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PianoRoll::semiToneMarkerMenuChordSetEnabled)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<PianoRoll *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->m_barLineColor; break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->m_beatLineColor; break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->m_lineColor; break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->m_noteModeColor; break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->m_noteColor; break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->m_stepNoteColor; break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->m_currentStepNoteColor; break;
        case 7: *reinterpret_cast< QColor*>(_v) = _t->m_ghostNoteColor; break;
        case 8: *reinterpret_cast< QColor*>(_v) = _t->m_noteTextColor; break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->m_ghostNoteTextColor; break;
        case 10: *reinterpret_cast< QColor*>(_v) = _t->m_barColor; break;
        case 11: *reinterpret_cast< QColor*>(_v) = _t->m_selectedNoteColor; break;
        case 12: *reinterpret_cast< QColor*>(_v) = _t->m_textColor; break;
        case 13: *reinterpret_cast< QColor*>(_v) = _t->m_textColorLight; break;
        case 14: *reinterpret_cast< QColor*>(_v) = _t->m_textShadow; break;
        case 15: *reinterpret_cast< QColor*>(_v) = _t->m_markedSemitoneColor; break;
        case 16: *reinterpret_cast< QColor*>(_v) = _t->m_knifeCutLineColor; break;
        case 17: *reinterpret_cast< int*>(_v) = _t->m_noteOpacity; break;
        case 18: *reinterpret_cast< bool*>(_v) = _t->m_noteBorders; break;
        case 19: *reinterpret_cast< int*>(_v) = _t->m_ghostNoteOpacity; break;
        case 20: *reinterpret_cast< bool*>(_v) = _t->m_ghostNoteBorders; break;
        case 21: *reinterpret_cast< QColor*>(_v) = _t->m_backgroundShade; break;
        case 22: *reinterpret_cast< QColor*>(_v) = _t->m_outOfBoundsShade; break;
        case 23: *reinterpret_cast< int*>(_v) = _t->m_whiteKeyWidth; break;
        case 24: *reinterpret_cast< QColor*>(_v) = _t->m_whiteKeyInactiveTextColor; break;
        case 25: *reinterpret_cast< QColor*>(_v) = _t->m_whiteKeyInactiveTextShadow; break;
        case 26: *reinterpret_cast< QBrush*>(_v) = _t->m_whiteKeyInactiveBackground; break;
        case 27: *reinterpret_cast< QColor*>(_v) = _t->m_whiteKeyActiveTextColor; break;
        case 28: *reinterpret_cast< QColor*>(_v) = _t->m_whiteKeyActiveTextShadow; break;
        case 29: *reinterpret_cast< QBrush*>(_v) = _t->m_whiteKeyActiveBackground; break;
        case 30: *reinterpret_cast< QBrush*>(_v) = _t->m_whiteKeyDisabledBackground; break;
        case 31: *reinterpret_cast< int*>(_v) = _t->m_blackKeyWidth; break;
        case 32: *reinterpret_cast< QBrush*>(_v) = _t->m_blackKeyInactiveBackground; break;
        case 33: *reinterpret_cast< QBrush*>(_v) = _t->m_blackKeyActiveBackground; break;
        case 34: *reinterpret_cast< QBrush*>(_v) = _t->m_blackKeyDisabledBackground; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<PianoRoll *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_barLineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_barLineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 1:
            if (_t->m_beatLineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_beatLineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 2:
            if (_t->m_lineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_lineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 3:
            if (_t->m_noteModeColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_noteModeColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 4:
            if (_t->m_noteColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_noteColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 5:
            if (_t->m_stepNoteColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_stepNoteColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 6:
            if (_t->m_currentStepNoteColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_currentStepNoteColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 7:
            if (_t->m_ghostNoteColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_ghostNoteColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 8:
            if (_t->m_noteTextColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_noteTextColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 9:
            if (_t->m_ghostNoteTextColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_ghostNoteTextColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 10:
            if (_t->m_barColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_barColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 11:
            if (_t->m_selectedNoteColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_selectedNoteColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 12:
            if (_t->m_textColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_textColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 13:
            if (_t->m_textColorLight != *reinterpret_cast< QColor*>(_v)) {
                _t->m_textColorLight = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 14:
            if (_t->m_textShadow != *reinterpret_cast< QColor*>(_v)) {
                _t->m_textShadow = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 15:
            if (_t->m_markedSemitoneColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_markedSemitoneColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 16:
            if (_t->m_knifeCutLineColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_knifeCutLineColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 17:
            if (_t->m_noteOpacity != *reinterpret_cast< int*>(_v)) {
                _t->m_noteOpacity = *reinterpret_cast< int*>(_v);
            }
            break;
        case 18:
            if (_t->m_noteBorders != *reinterpret_cast< bool*>(_v)) {
                _t->m_noteBorders = *reinterpret_cast< bool*>(_v);
            }
            break;
        case 19:
            if (_t->m_ghostNoteOpacity != *reinterpret_cast< int*>(_v)) {
                _t->m_ghostNoteOpacity = *reinterpret_cast< int*>(_v);
            }
            break;
        case 20:
            if (_t->m_ghostNoteBorders != *reinterpret_cast< bool*>(_v)) {
                _t->m_ghostNoteBorders = *reinterpret_cast< bool*>(_v);
            }
            break;
        case 21:
            if (_t->m_backgroundShade != *reinterpret_cast< QColor*>(_v)) {
                _t->m_backgroundShade = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 22:
            if (_t->m_outOfBoundsShade != *reinterpret_cast< QColor*>(_v)) {
                _t->m_outOfBoundsShade = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 23:
            if (_t->m_whiteKeyWidth != *reinterpret_cast< int*>(_v)) {
                _t->m_whiteKeyWidth = *reinterpret_cast< int*>(_v);
            }
            break;
        case 24:
            if (_t->m_whiteKeyInactiveTextColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_whiteKeyInactiveTextColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 25:
            if (_t->m_whiteKeyInactiveTextShadow != *reinterpret_cast< QColor*>(_v)) {
                _t->m_whiteKeyInactiveTextShadow = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 26:
            if (_t->m_whiteKeyInactiveBackground != *reinterpret_cast< QBrush*>(_v)) {
                _t->m_whiteKeyInactiveBackground = *reinterpret_cast< QBrush*>(_v);
            }
            break;
        case 27:
            if (_t->m_whiteKeyActiveTextColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_whiteKeyActiveTextColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 28:
            if (_t->m_whiteKeyActiveTextShadow != *reinterpret_cast< QColor*>(_v)) {
                _t->m_whiteKeyActiveTextShadow = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 29:
            if (_t->m_whiteKeyActiveBackground != *reinterpret_cast< QBrush*>(_v)) {
                _t->m_whiteKeyActiveBackground = *reinterpret_cast< QBrush*>(_v);
            }
            break;
        case 30:
            if (_t->m_whiteKeyDisabledBackground != *reinterpret_cast< QBrush*>(_v)) {
                _t->m_whiteKeyDisabledBackground = *reinterpret_cast< QBrush*>(_v);
            }
            break;
        case 31:
            if (_t->m_blackKeyWidth != *reinterpret_cast< int*>(_v)) {
                _t->m_blackKeyWidth = *reinterpret_cast< int*>(_v);
            }
            break;
        case 32:
            if (_t->m_blackKeyInactiveBackground != *reinterpret_cast< QBrush*>(_v)) {
                _t->m_blackKeyInactiveBackground = *reinterpret_cast< QBrush*>(_v);
            }
            break;
        case 33:
            if (_t->m_blackKeyActiveBackground != *reinterpret_cast< QBrush*>(_v)) {
                _t->m_blackKeyActiveBackground = *reinterpret_cast< QBrush*>(_v);
            }
            break;
        case 34:
            if (_t->m_blackKeyDisabledBackground != *reinterpret_cast< QBrush*>(_v)) {
                _t->m_blackKeyDisabledBackground = *reinterpret_cast< QBrush*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::PianoRoll::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__PianoRoll.data,
    qt_meta_data_lmms__gui__PianoRoll,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::PianoRoll::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::PianoRoll::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__PianoRoll.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::PianoRoll::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 35;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 35;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void lmms::gui::PianoRoll::currentMidiClipChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void lmms::gui::PianoRoll::ghostClipSet(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void lmms::gui::PianoRoll::semiToneMarkerMenuScaleSetEnabled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void lmms::gui::PianoRoll::semiToneMarkerMenuChordSetEnabled(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
struct qt_meta_stringdata_lmms__gui__PianoRollWindow_t {
    QByteArrayData data[8];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__PianoRollWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__PianoRollWindow_t qt_meta_stringdata_lmms__gui__PianoRollWindow = {
    {
QT_MOC_LITERAL(0, 0, 26), // "lmms::gui::PianoRollWindow"
QT_MOC_LITERAL(1, 27, 22), // "currentMidiClipChanged"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 25), // "updateAfterMidiClipChange"
QT_MOC_LITERAL(4, 77, 12), // "ghostClipSet"
QT_MOC_LITERAL(5, 90, 5), // "state"
QT_MOC_LITERAL(6, 96, 14), // "exportMidiClip"
QT_MOC_LITERAL(7, 111, 14) // "importMidiClip"

    },
    "lmms::gui::PianoRollWindow\0"
    "currentMidiClipChanged\0\0"
    "updateAfterMidiClipChange\0ghostClipSet\0"
    "state\0exportMidiClip\0importMidiClip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__PianoRollWindow[] = {

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
       4,    1,   41,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lmms::gui::PianoRollWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PianoRollWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->currentMidiClipChanged(); break;
        case 1: _t->updateAfterMidiClipChange(); break;
        case 2: _t->ghostClipSet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->exportMidiClip(); break;
        case 4: _t->importMidiClip(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PianoRollWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PianoRollWindow::currentMidiClipChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::PianoRollWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<Editor::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__PianoRollWindow.data,
    qt_meta_data_lmms__gui__PianoRollWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::PianoRollWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::PianoRollWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__PianoRollWindow.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "SerializingObject"))
        return static_cast< SerializingObject*>(this);
    return Editor::qt_metacast(_clname);
}

int lmms::gui::PianoRollWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Editor::qt_metacall(_c, _id, _a);
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
void lmms::gui::PianoRollWindow::currentMidiClipChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
