/****************************************************************************
** Meta object code from reading C++ file 'kresizedialog.h'
**
** Created: Sun Jan 23 19:10:52 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kresizedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kresizedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KResizeDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      34,   14,   14,   14, 0x0a,
      54,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KResizeDialog[] = {
    "KResizeDialog\0\0changeWidthValue()\0"
    "changeHeightValue()\0validateResize()\0"
};

const QMetaObject KResizeDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KResizeDialog,
      qt_meta_data_KResizeDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KResizeDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KResizeDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KResizeDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KResizeDialog))
        return static_cast<void*>(const_cast< KResizeDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int KResizeDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeWidthValue(); break;
        case 1: changeHeightValue(); break;
        case 2: validateResize(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
