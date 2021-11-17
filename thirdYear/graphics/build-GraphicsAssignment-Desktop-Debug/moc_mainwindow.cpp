/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GraphicsAssignment/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[56];
    char stringdata0[1006];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "Mouse_Pressed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 17), // "showMousePosition"
QT_MOC_LITERAL(4, 44, 7), // "QPoint&"
QT_MOC_LITERAL(5, 52, 3), // "pos"
QT_MOC_LITERAL(6, 56, 20), // "on_show_axes_clicked"
QT_MOC_LITERAL(7, 77, 24), // "on_setgridbutton_clicked"
QT_MOC_LITERAL(8, 102, 22), // "on_resetButton_clicked"
QT_MOC_LITERAL(9, 125, 20), // "on_setpoint1_clicked"
QT_MOC_LITERAL(10, 146, 20), // "on_setpoint2_clicked"
QT_MOC_LITERAL(11, 167, 18), // "on_DDAline_clicked"
QT_MOC_LITERAL(12, 186, 11), // "drawDDALine"
QT_MOC_LITERAL(13, 198, 1), // "r"
QT_MOC_LITERAL(14, 200, 1), // "g"
QT_MOC_LITERAL(15, 202, 1), // "b"
QT_MOC_LITERAL(16, 204, 24), // "on_bresenhamLine_clicked"
QT_MOC_LITERAL(17, 229, 25), // "on_midpointCircle_clicked"
QT_MOC_LITERAL(18, 255, 26), // "on_bresenhamCircle_clicked"
QT_MOC_LITERAL(19, 282, 26), // "on_midpointEllipse_clicked"
QT_MOC_LITERAL(20, 309, 5), // "delay"
QT_MOC_LITERAL(21, 315, 1), // "n"
QT_MOC_LITERAL(22, 317, 22), // "on_polarCircle_clicked"
QT_MOC_LITERAL(23, 340, 23), // "on_polarEllipse_clicked"
QT_MOC_LITERAL(24, 364, 20), // "on_floodfill_clicked"
QT_MOC_LITERAL(25, 385, 22), // "floodfillUtility4point"
QT_MOC_LITERAL(26, 408, 22), // "floodfillUtility8point"
QT_MOC_LITERAL(27, 431, 25), // "boundaryfillUtility4point"
QT_MOC_LITERAL(28, 457, 4), // "QRgb"
QT_MOC_LITERAL(29, 462, 25), // "boundaryfillUtility8point"
QT_MOC_LITERAL(30, 488, 23), // "on_boundaryfill_clicked"
QT_MOC_LITERAL(31, 512, 20), // "on_setVertex_clicked"
QT_MOC_LITERAL(32, 533, 22), // "on_clearVertex_clicked"
QT_MOC_LITERAL(33, 556, 13), // "initEdgeTable"
QT_MOC_LITERAL(34, 570, 16), // "storeEdgeInTable"
QT_MOC_LITERAL(35, 587, 23), // "on_scanlinefill_clicked"
QT_MOC_LITERAL(36, 611, 22), // "on_translation_clicked"
QT_MOC_LITERAL(37, 634, 9), // "poly_draw"
QT_MOC_LITERAL(38, 644, 32), // "std::vector<std::pair<int,int> >"
QT_MOC_LITERAL(39, 677, 18), // "on_scaling_clicked"
QT_MOC_LITERAL(40, 696, 19), // "on_shearing_clicked"
QT_MOC_LITERAL(41, 716, 21), // "on_shearing_2_clicked"
QT_MOC_LITERAL(42, 738, 21), // "on_reflection_clicked"
QT_MOC_LITERAL(43, 760, 21), // "on_setCorner1_clicked"
QT_MOC_LITERAL(44, 782, 21), // "on_setCorner2_clicked"
QT_MOC_LITERAL(45, 804, 23), // "on_lineclipping_clicked"
QT_MOC_LITERAL(46, 828, 11), // "draw_Window"
QT_MOC_LITERAL(47, 840, 11), // "computeCode"
QT_MOC_LITERAL(48, 852, 19), // "cohenSutherlandClip"
QT_MOC_LITERAL(49, 872, 26), // "drawDDALineByStoringPoints"
QT_MOC_LITERAL(50, 899, 37), // "on_drawDDALineByStoringPoints..."
QT_MOC_LITERAL(51, 937, 26), // "on_polygonclipping_clicked"
QT_MOC_LITERAL(52, 964, 12), // "suthHodgClip"
QT_MOC_LITERAL(53, 977, 4), // "clip"
QT_MOC_LITERAL(54, 982, 11), // "x_intersect"
QT_MOC_LITERAL(55, 994, 11) // "y_intersect"

    },
    "MainWindow\0Mouse_Pressed\0\0showMousePosition\0"
    "QPoint&\0pos\0on_show_axes_clicked\0"
    "on_setgridbutton_clicked\0"
    "on_resetButton_clicked\0on_setpoint1_clicked\0"
    "on_setpoint2_clicked\0on_DDAline_clicked\0"
    "drawDDALine\0r\0g\0b\0on_bresenhamLine_clicked\0"
    "on_midpointCircle_clicked\0"
    "on_bresenhamCircle_clicked\0"
    "on_midpointEllipse_clicked\0delay\0n\0"
    "on_polarCircle_clicked\0on_polarEllipse_clicked\0"
    "on_floodfill_clicked\0floodfillUtility4point\0"
    "floodfillUtility8point\0boundaryfillUtility4point\0"
    "QRgb\0boundaryfillUtility8point\0"
    "on_boundaryfill_clicked\0on_setVertex_clicked\0"
    "on_clearVertex_clicked\0initEdgeTable\0"
    "storeEdgeInTable\0on_scanlinefill_clicked\0"
    "on_translation_clicked\0poly_draw\0"
    "std::vector<std::pair<int,int> >\0"
    "on_scaling_clicked\0on_shearing_clicked\0"
    "on_shearing_2_clicked\0on_reflection_clicked\0"
    "on_setCorner1_clicked\0on_setCorner2_clicked\0"
    "on_lineclipping_clicked\0draw_Window\0"
    "computeCode\0cohenSutherlandClip\0"
    "drawDDALineByStoringPoints\0"
    "on_drawDDALineByStoringPoints_clicked\0"
    "on_polygonclipping_clicked\0suthHodgClip\0"
    "clip\0x_intersect\0y_intersect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  244,    2, 0x0a /* Public */,
       3,    1,  245,    2, 0x0a /* Public */,
       6,    0,  248,    2, 0x08 /* Private */,
       7,    0,  249,    2, 0x08 /* Private */,
       8,    0,  250,    2, 0x08 /* Private */,
       9,    0,  251,    2, 0x08 /* Private */,
      10,    0,  252,    2, 0x08 /* Private */,
      11,    0,  253,    2, 0x08 /* Private */,
      12,    3,  254,    2, 0x08 /* Private */,
      16,    0,  261,    2, 0x08 /* Private */,
      17,    0,  262,    2, 0x08 /* Private */,
      18,    0,  263,    2, 0x08 /* Private */,
      19,    0,  264,    2, 0x08 /* Private */,
      20,    1,  265,    2, 0x08 /* Private */,
      22,    0,  268,    2, 0x08 /* Private */,
      23,    0,  269,    2, 0x08 /* Private */,
      24,    0,  270,    2, 0x08 /* Private */,
      25,    5,  271,    2, 0x08 /* Private */,
      26,    5,  282,    2, 0x08 /* Private */,
      27,    6,  293,    2, 0x08 /* Private */,
      29,    6,  306,    2, 0x08 /* Private */,
      30,    0,  319,    2, 0x08 /* Private */,
      31,    0,  320,    2, 0x08 /* Private */,
      32,    0,  321,    2, 0x08 /* Private */,
      33,    0,  322,    2, 0x08 /* Private */,
      34,    4,  323,    2, 0x08 /* Private */,
      35,    0,  332,    2, 0x08 /* Private */,
      36,    0,  333,    2, 0x08 /* Private */,
      37,    4,  334,    2, 0x08 /* Private */,
      39,    0,  343,    2, 0x08 /* Private */,
      40,    0,  344,    2, 0x08 /* Private */,
      41,    0,  345,    2, 0x08 /* Private */,
      42,    0,  346,    2, 0x08 /* Private */,
      43,    0,  347,    2, 0x08 /* Private */,
      44,    0,  348,    2, 0x08 /* Private */,
      45,    0,  349,    2, 0x08 /* Private */,
      46,    0,  350,    2, 0x08 /* Private */,
      47,    2,  351,    2, 0x08 /* Private */,
      48,    4,  356,    2, 0x08 /* Private */,
      49,    3,  365,    2, 0x08 /* Private */,
      50,    0,  372,    2, 0x08 /* Private */,
      51,    0,  373,    2, 0x08 /* Private */,
      52,    0,  374,    2, 0x08 /* Private */,
      53,    4,  375,    2, 0x08 /* Private */,
      54,    8,  384,    2, 0x08 /* Private */,
      55,    8,  401,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 28, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 28, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,    2,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Mouse_Pressed(); break;
        case 1: _t->showMousePosition((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->on_show_axes_clicked(); break;
        case 3: _t->on_setgridbutton_clicked(); break;
        case 4: _t->on_resetButton_clicked(); break;
        case 5: _t->on_setpoint1_clicked(); break;
        case 6: _t->on_setpoint2_clicked(); break;
        case 7: _t->on_DDAline_clicked(); break;
        case 8: _t->drawDDALine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->on_bresenhamLine_clicked(); break;
        case 10: _t->on_midpointCircle_clicked(); break;
        case 11: _t->on_bresenhamCircle_clicked(); break;
        case 12: _t->on_midpointEllipse_clicked(); break;
        case 13: _t->delay((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_polarCircle_clicked(); break;
        case 15: _t->on_polarEllipse_clicked(); break;
        case 16: _t->on_floodfill_clicked(); break;
        case 17: _t->floodfillUtility4point((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 18: _t->floodfillUtility8point((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 19: _t->boundaryfillUtility4point((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QRgb(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 20: _t->boundaryfillUtility8point((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QRgb(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 21: _t->on_boundaryfill_clicked(); break;
        case 22: _t->on_setVertex_clicked(); break;
        case 23: _t->on_clearVertex_clicked(); break;
        case 24: _t->initEdgeTable(); break;
        case 25: _t->storeEdgeInTable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 26: _t->on_scanlinefill_clicked(); break;
        case 27: _t->on_translation_clicked(); break;
        case 28: _t->poly_draw((*reinterpret_cast< std::vector<std::pair<int,int> >(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 29: _t->on_scaling_clicked(); break;
        case 30: _t->on_shearing_clicked(); break;
        case 31: _t->on_shearing_2_clicked(); break;
        case 32: _t->on_reflection_clicked(); break;
        case 33: _t->on_setCorner1_clicked(); break;
        case 34: _t->on_setCorner2_clicked(); break;
        case 35: _t->on_lineclipping_clicked(); break;
        case 36: _t->draw_Window(); break;
        case 37: { int _r = _t->computeCode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->cohenSutherlandClip((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 39: _t->drawDDALineByStoringPoints((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 40: _t->on_drawDDALineByStoringPoints_clicked(); break;
        case 41: _t->on_polygonclipping_clicked(); break;
        case 42: _t->suthHodgClip(); break;
        case 43: _t->clip((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 44: { int _r = _t->x_intersect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 45: { int _r = _t->y_intersect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 46;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
