/****************************************************************************
** Meta object code from reading C++ file 'AOSC-Installer-Core.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/AOSC-Installer-Core.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AOSC-Installer-Core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AOSC_Installer_Core[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      38,   20,   20,   20, 0x05,
      53,   20,   20,   20, 0x05,
      65,   20,   20,   20, 0x05,
      79,   20,   20,   20, 0x05,
      96,   20,   20,   20, 0x05,
     116,   20,   20,   20, 0x05,
     137,   20,   20,   20, 0x05,
     154,   20,   20,   20, 0x05,
     171,   20,   20,   20, 0x05,
     188,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_AOSC_Installer_Core[] = {
    "AOSC_Installer_Core\0\0MountFSDone(int)\0"
    "TotalFile(int)\0Copyed(int)\0CopyDone(int)\0"
    "SetGrubDone(int)\0UpdateGrubDone(int)\0"
    "UpdateFstabDone(int)\0SetUserDone(int)\0"
    "SetRootDone(int)\0SFSizeStart(int)\0"
    "SFSizeStop()\0"
};

void AOSC_Installer_Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AOSC_Installer_Core *_t = static_cast<AOSC_Installer_Core *>(_o);
        switch (_id) {
        case 0: _t->MountFSDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->TotalFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->Copyed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->CopyDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetGrubDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->UpdateGrubDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->UpdateFstabDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->SetUserDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SetRootDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->SFSizeStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->SFSizeStop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AOSC_Installer_Core::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AOSC_Installer_Core::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AOSC_Installer_Core,
      qt_meta_data_AOSC_Installer_Core, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AOSC_Installer_Core::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AOSC_Installer_Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AOSC_Installer_Core::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AOSC_Installer_Core))
        return static_cast<void*>(const_cast< AOSC_Installer_Core*>(this));
    return QThread::qt_metacast(_clname);
}

int AOSC_Installer_Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void AOSC_Installer_Core::MountFSDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AOSC_Installer_Core::TotalFile(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AOSC_Installer_Core::Copyed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AOSC_Installer_Core::CopyDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AOSC_Installer_Core::SetGrubDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AOSC_Installer_Core::UpdateGrubDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AOSC_Installer_Core::UpdateFstabDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AOSC_Installer_Core::SetUserDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AOSC_Installer_Core::SetRootDone(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AOSC_Installer_Core::SFSizeStart(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AOSC_Installer_Core::SFSizeStop()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}
static const uint qt_meta_data_StatisticsFileSize[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   19,   19,   19, 0x0a,
      43,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_StatisticsFileSize[] = {
    "StatisticsFileSize\0\0Copyed(int)\0"
    "CopyDone()\0GetReady(int)\0"
};

void StatisticsFileSize::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StatisticsFileSize *_t = static_cast<StatisticsFileSize *>(_o);
        switch (_id) {
        case 0: _t->Copyed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->CopyDone(); break;
        case 2: _t->GetReady((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData StatisticsFileSize::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StatisticsFileSize::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_StatisticsFileSize,
      qt_meta_data_StatisticsFileSize, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StatisticsFileSize::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StatisticsFileSize::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StatisticsFileSize::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatisticsFileSize))
        return static_cast<void*>(const_cast< StatisticsFileSize*>(this));
    return QThread::qt_metacast(_clname);
}

int StatisticsFileSize::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void StatisticsFileSize::Copyed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
