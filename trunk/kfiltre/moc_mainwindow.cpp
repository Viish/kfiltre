/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Jan 11 17:06:50 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      19,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      35,   11,   11,   11, 0x0a,
      44,   11,   11,   11, 0x0a,
      51,   11,   11,   11, 0x0a,
      58,   11,   11,   11, 0x0a,
      65,   11,   11,   11, 0x0a,
      81,   11,   11,   11, 0x0a,
     100,   11,   11,   11, 0x0a,
     114,   11,   11,   11, 0x0a,
     126,   11,   11,   11, 0x0a,
     144,   11,   11,   11, 0x0a,
     156,   11,   11,   11, 0x0a,
     179,   11,   11,   11, 0x0a,
     198,   11,   11,   11, 0x0a,
     219,   11,   11,   11, 0x0a,
     238,   11,   11,   11, 0x0a,
     247,   11,   11,   11, 0x0a,
     268,   11,   11,   11, 0x0a,
     283,   11,   11,   11, 0x0a,
     298,   11,   11,   11, 0x08,
     342,  336,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0open()\0save()\0saveAs()\0"
    "toGray()\0crop()\0undo()\0redo()\0"
    "showHistogram()\0showYUVHistogram()\0"
    "setRectTool()\0selectAll()\0cancelSelection()\0"
    "applyBlur()\0applyEdgeEnhancement()\0"
    "applyPaintEffect()\0applyEdgeDetection()\0"
    "showResizeDialog()\0fusion()\0"
    "normalizeHistogram()\0smartResizeH()\0"
    "smartResizeV()\0on_tabWidget_currentChanged(QWidget*)\0"
    "index\0on_tabWidget_tabCloseRequested(int)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        case 1: save(); break;
        case 2: saveAs(); break;
        case 3: toGray(); break;
        case 4: crop(); break;
        case 5: undo(); break;
        case 6: redo(); break;
        case 7: showHistogram(); break;
        case 8: showYUVHistogram(); break;
        case 9: setRectTool(); break;
        case 10: selectAll(); break;
        case 11: cancelSelection(); break;
        case 12: applyBlur(); break;
        case 13: applyEdgeEnhancement(); break;
        case 14: applyPaintEffect(); break;
        case 15: applyEdgeDetection(); break;
        case 16: showResizeDialog(); break;
        case 17: fusion(); break;
        case 18: normalizeHistogram(); break;
        case 19: smartResizeH(); break;
        case 20: smartResizeV(); break;
        case 21: on_tabWidget_currentChanged((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 22: on_tabWidget_tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
