/****************************************************************************
** Meta object code from reading C++ file 'ChartRow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../ChartRow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChartRow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChartRow_t {
    QByteArrayData data[20];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChartRow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChartRow_t qt_meta_stringdata_ChartRow = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ChartRow"
QT_MOC_LITERAL(1, 9, 16), // "RequestForChange"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "text"
QT_MOC_LITERAL(4, 32, 6), // "RePlot"
QT_MOC_LITERAL(5, 39, 12), // "QList<short>"
QT_MOC_LITERAL(6, 52, 9), // "chartdata"
QT_MOC_LITERAL(7, 62, 13), // "SetCurveColor"
QT_MOC_LITERAL(8, 76, 9), // "Property*"
QT_MOC_LITERAL(9, 86, 10), // "curveColor"
QT_MOC_LITERAL(10, 97, 14), // "SetScrollSpeed"
QT_MOC_LITERAL(11, 112, 11), // "scrollSpeed"
QT_MOC_LITERAL(12, 124, 20), // "OnYScrollValueChange"
QT_MOC_LITERAL(13, 145, 5), // "value"
QT_MOC_LITERAL(14, 151, 20), // "OnXScrollValueChange"
QT_MOC_LITERAL(15, 172, 18), // "OnXAxisRangeChange"
QT_MOC_LITERAL(16, 191, 3), // "min"
QT_MOC_LITERAL(17, 195, 3), // "max"
QT_MOC_LITERAL(18, 199, 18), // "OnYAxisRangeChange"
QT_MOC_LITERAL(19, 218, 16) // "OnComboBoxChange"

    },
    "ChartRow\0RequestForChange\0\0text\0RePlot\0"
    "QList<short>\0chartdata\0SetCurveColor\0"
    "Property*\0curveColor\0SetScrollSpeed\0"
    "scrollSpeed\0OnYScrollValueChange\0value\0"
    "OnXScrollValueChange\0OnXAxisRangeChange\0"
    "min\0max\0OnYAxisRangeChange\0OnComboBoxChange"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChartRow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   62,    2, 0x0a /* Public */,
       7,    1,   65,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      12,    1,   71,    2, 0x0a /* Public */,
      14,    1,   74,    2, 0x0a /* Public */,
      15,    2,   77,    2, 0x0a /* Public */,
      18,    2,   82,    2, 0x0a /* Public */,
      19,    1,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   16,   17,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,   16,   17,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void ChartRow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChartRow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RequestForChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->RePlot((*reinterpret_cast< const QList<short>(*)>(_a[1]))); break;
        case 2: _t->SetCurveColor((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        case 3: _t->SetScrollSpeed((*reinterpret_cast< Property*(*)>(_a[1]))); break;
        case 4: _t->OnYScrollValueChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->OnXScrollValueChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->OnXAxisRangeChange((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 7: _t->OnYAxisRangeChange((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 8: _t->OnComboBoxChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<short> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Property* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Property* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChartRow::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChartRow::RequestForChange)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChartRow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ChartRow.data,
    qt_meta_data_ChartRow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChartRow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChartRow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChartRow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChartRow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ChartRow::RequestForChange(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
