/****************************************************************************
** Meta object code from reading C++ file 'kfusion.h'
**
** Created: Mon Jan 10 17:55:11 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "kfusion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kfusion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_KFusion[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      26,   20,    8,    8, 0x0a,
      45,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_KFusion[] = {
    "KFusion\0\0validate()\0value\0factorChanged(int)\0"
    "browse()\0"
};

const QMetaObject KFusion::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KFusion,
      qt_meta_data_KFusion, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &KFusion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *KFusion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *KFusion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_KFusion))
        return static_cast<void*>(const_cast< KFusion*>(this));
    return QDialog::qt_metacast(_clname);
}

int KFusion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: validate(); break;
        case 1: factorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: browse(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
