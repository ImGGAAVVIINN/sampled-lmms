/****************************************************************************
** Meta object code from reading C++ file 'TimeLineWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../include/TimeLineWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TimeLineWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lmms__gui__TimeLineWidget_t {
    QByteArrayData data[22];
    char stringdata0[383];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lmms__gui__TimeLineWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lmms__gui__TimeLineWidget_t qt_meta_stringdata_lmms__gui__TimeLineWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "lmms::gui::TimeLineWidget"
QT_MOC_LITERAL(1, 26, 24), // "regionSelectedFromPixels"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 17), // "selectionFinished"
QT_MOC_LITERAL(4, 70, 11), // "setSnapSize"
QT_MOC_LITERAL(5, 82, 8), // "snapSize"
QT_MOC_LITERAL(6, 91, 16), // "toggleAutoScroll"
QT_MOC_LITERAL(7, 108, 2), // "_n"
QT_MOC_LITERAL(8, 111, 12), // "barLineColor"
QT_MOC_LITERAL(9, 124, 14), // "barNumberColor"
QT_MOC_LITERAL(10, 139, 17), // "inactiveLoopColor"
QT_MOC_LITERAL(11, 157, 17), // "inactiveLoopBrush"
QT_MOC_LITERAL(12, 175, 22), // "inactiveLoopInnerColor"
QT_MOC_LITERAL(13, 198, 23), // "inactiveLoopHandleColor"
QT_MOC_LITERAL(14, 222, 15), // "activeLoopColor"
QT_MOC_LITERAL(15, 238, 15), // "activeLoopBrush"
QT_MOC_LITERAL(16, 254, 20), // "activeLoopInnerColor"
QT_MOC_LITERAL(17, 275, 21), // "activeLoopHandleColor"
QT_MOC_LITERAL(18, 297, 28), // "loopRectangleVerticalPadding"
QT_MOC_LITERAL(19, 326, 15), // "loopHandleWidth"
QT_MOC_LITERAL(20, 342, 19), // "mouseHotspotSelLeft"
QT_MOC_LITERAL(21, 362, 20) // "mouseHotspotSelRight"

    },
    "lmms::gui::TimeLineWidget\0"
    "regionSelectedFromPixels\0\0selectionFinished\0"
    "setSnapSize\0snapSize\0toggleAutoScroll\0"
    "_n\0barLineColor\0barNumberColor\0"
    "inactiveLoopColor\0inactiveLoopBrush\0"
    "inactiveLoopInnerColor\0inactiveLoopHandleColor\0"
    "activeLoopColor\0activeLoopBrush\0"
    "activeLoopInnerColor\0activeLoopHandleColor\0"
    "loopRectangleVerticalPadding\0"
    "loopHandleWidth\0mouseHotspotSelLeft\0"
    "mouseHotspotSelRight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lmms__gui__TimeLineWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
      14,   46, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       3,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   40,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // properties: name, type, flags
       8, QMetaType::QColor, 0x00095103,
       9, QMetaType::QColor, 0x00095103,
      10, QMetaType::QColor, 0x00095103,
      11, QMetaType::QBrush, 0x00095103,
      12, QMetaType::QColor, 0x00095103,
      13, QMetaType::QColor, 0x00095003,
      14, QMetaType::QColor, 0x00095103,
      15, QMetaType::QBrush, 0x00095103,
      16, QMetaType::QColor, 0x00095103,
      17, QMetaType::QColor, 0x00095003,
      18, QMetaType::Int, 0x00095103,
      19, QMetaType::Int, 0x00095003,
      20, QMetaType::QSize, 0x00095103,
      21, QMetaType::QSize, 0x00095103,

       0        // eod
};

void lmms::gui::TimeLineWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TimeLineWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->regionSelectedFromPixels((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->selectionFinished(); break;
        case 2: _t->setSnapSize((*reinterpret_cast< const float(*)>(_a[1]))); break;
        case 3: _t->toggleAutoScroll((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TimeLineWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeLineWidget::regionSelectedFromPixels)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TimeLineWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TimeLineWidget::selectionFinished)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<TimeLineWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->getBarLineColor(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->getBarNumberColor(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->getInactiveLoopColor(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->getInactiveLoopBrush(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->getInactiveLoopInnerColor(); break;
        case 5: *reinterpret_cast< QColor*>(_v) = _t->m_inactiveLoopHandleColor; break;
        case 6: *reinterpret_cast< QColor*>(_v) = _t->getActiveLoopColor(); break;
        case 7: *reinterpret_cast< QBrush*>(_v) = _t->getActiveLoopBrush(); break;
        case 8: *reinterpret_cast< QColor*>(_v) = _t->getActiveLoopInnerColor(); break;
        case 9: *reinterpret_cast< QColor*>(_v) = _t->m_activeLoopHandleColor; break;
        case 10: *reinterpret_cast< int*>(_v) = _t->getLoopRectangleVerticalPadding(); break;
        case 11: *reinterpret_cast< int*>(_v) = _t->m_loopHandleWidth; break;
        case 12: *reinterpret_cast< QSize*>(_v) = _t->mouseHotspotSelLeft(); break;
        case 13: *reinterpret_cast< QSize*>(_v) = _t->mouseHotspotSelRight(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<TimeLineWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBarLineColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setBarNumberColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setInactiveLoopColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setInactiveLoopBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 4: _t->setInactiveLoopInnerColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5:
            if (_t->m_inactiveLoopHandleColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_inactiveLoopHandleColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 6: _t->setActiveLoopColor(*reinterpret_cast< QColor*>(_v)); break;
        case 7: _t->setActiveLoopBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 8: _t->setActiveLoopInnerColor(*reinterpret_cast< QColor*>(_v)); break;
        case 9:
            if (_t->m_activeLoopHandleColor != *reinterpret_cast< QColor*>(_v)) {
                _t->m_activeLoopHandleColor = *reinterpret_cast< QColor*>(_v);
            }
            break;
        case 10: _t->setLoopRectangleVerticalPadding(*reinterpret_cast< int*>(_v)); break;
        case 11:
            if (_t->m_loopHandleWidth != *reinterpret_cast< int*>(_v)) {
                _t->m_loopHandleWidth = *reinterpret_cast< int*>(_v);
            }
            break;
        case 12: _t->setMouseHotspotSelLeft(*reinterpret_cast< QSize*>(_v)); break;
        case 13: _t->setMouseHotspotSelRight(*reinterpret_cast< QSize*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject lmms::gui::TimeLineWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_lmms__gui__TimeLineWidget.data,
    qt_meta_data_lmms__gui__TimeLineWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lmms::gui::TimeLineWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lmms::gui::TimeLineWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lmms__gui__TimeLineWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lmms::gui::TimeLineWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void lmms::gui::TimeLineWidget::regionSelectedFromPixels(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lmms::gui::TimeLineWidget::selectionFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
