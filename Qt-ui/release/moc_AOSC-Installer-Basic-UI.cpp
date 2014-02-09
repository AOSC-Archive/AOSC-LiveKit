/****************************************************************************
** Meta object code from reading C++ file 'AOSC-Installer-Basic-UI.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/AOSC-Installer-Basic-UI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AOSC-Installer-Basic-UI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProgressTabWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      30,   18,   18,   18, 0x05,
      41,   18,   18,   18, 0x05,
      51,   18,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
      61,   18,   18,   18, 0x0a,
      79,   18,   18,   18, 0x0a,
     102,   97,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProgressTabWidget[] = {
    "ProgressTabWidget\0\0NextSetp()\0PervStep()\0"
    "AskHide()\0AskShow()\0NextStepClicked()\0"
    "PervStepClicked()\0Text\0"
    "SetNextButtonText(QString)\0"
};

void ProgressTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProgressTabWidget *_t = static_cast<ProgressTabWidget *>(_o);
        switch (_id) {
        case 0: _t->NextSetp(); break;
        case 1: _t->PervStep(); break;
        case 2: _t->AskHide(); break;
        case 3: _t->AskShow(); break;
        case 4: _t->NextStepClicked(); break;
        case 5: _t->PervStepClicked(); break;
        case 6: _t->SetNextButtonText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProgressTabWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProgressTabWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProgressTabWidget,
      qt_meta_data_ProgressTabWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProgressTabWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProgressTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProgressTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProgressTabWidget))
        return static_cast<void*>(const_cast< ProgressTabWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProgressTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ProgressTabWidget::NextSetp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ProgressTabWidget::PervStep()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void ProgressTabWidget::AskHide()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void ProgressTabWidget::AskShow()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
static const uint qt_meta_data_WelcomeTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_WelcomeTab[] = {
    "WelcomeTab\0"
};

void WelcomeTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData WelcomeTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WelcomeTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_WelcomeTab,
      qt_meta_data_WelcomeTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WelcomeTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WelcomeTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WelcomeTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WelcomeTab))
        return static_cast<void*>(const_cast< WelcomeTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int WelcomeTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_GetStartedTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_GetStartedTab[] = {
    "GetStartedTab\0"
};

void GetStartedTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GetStartedTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GetStartedTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_GetStartedTab,
      qt_meta_data_GetStartedTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GetStartedTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GetStartedTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GetStartedTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GetStartedTab))
        return static_cast<void*>(const_cast< GetStartedTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int GetStartedTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ReadingTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ReadingTab[] = {
    "ReadingTab\0\0CheckBoxChanged()\0"
};

void ReadingTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ReadingTab *_t = static_cast<ReadingTab *>(_o);
        switch (_id) {
        case 0: _t->CheckBoxChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ReadingTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ReadingTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_ReadingTab,
      qt_meta_data_ReadingTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReadingTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReadingTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReadingTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReadingTab))
        return static_cast<void*>(const_cast< ReadingTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int ReadingTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_GPartedDiskTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   15,   15,   15, 0x0a,
      79,   15,   15,   15, 0x0a,
     103,   15,   15,   15, 0x0a,
     120,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GPartedDiskTab[] = {
    "GPartedDiskTab\0\0,\0PartedDone(QString,QString)\0"
    "SetCurrentDiskPartition(QString)\0"
    "SetCurrentDisk(QString)\0StartPartiting()\0"
    "ReadyToGo()\0"
};

void GPartedDiskTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GPartedDiskTab *_t = static_cast<GPartedDiskTab *>(_o);
        switch (_id) {
        case 0: _t->PartedDone((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->SetCurrentDiskPartition((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->SetCurrentDisk((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->StartPartiting(); break;
        case 4: _t->ReadyToGo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GPartedDiskTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GPartedDiskTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_GPartedDiskTab,
      qt_meta_data_GPartedDiskTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GPartedDiskTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GPartedDiskTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GPartedDiskTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GPartedDiskTab))
        return static_cast<void*>(const_cast< GPartedDiskTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int GPartedDiskTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GPartedDiskTab::PartedDone(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_MainWorkTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      32,   30,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   12,   12,   12, 0x0a,
      86,   79,   12,   12, 0x0a,
     103,   12,   12,   12, 0x0a,
     122,   12,   12,   12, 0x0a,
     139,   12,   12,   12, 0x0a,
     153,   12,   12,   12, 0x0a,
     170,   12,   12,   12, 0x0a,
     190,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWorkTab[] = {
    "MainWorkTab\0\0MountFS(QString)\0,\0"
    "S_StartInstall(QString,QString)\0"
    "StartInstall()\0Status\0MountFSDone(int)\0"
    "TotalFileDone(int)\0FileCopying(int)\0"
    "CopyDone(int)\0SetGrubDone(int)\0"
    "UpdateGrubDone(int)\0UpdateFstabDone(int)\0"
};

void MainWorkTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWorkTab *_t = static_cast<MainWorkTab *>(_o);
        switch (_id) {
        case 0: _t->MountFS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->S_StartInstall((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->StartInstall(); break;
        case 3: _t->MountFSDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->TotalFileDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->FileCopying((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->CopyDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->SetGrubDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->UpdateGrubDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->UpdateFstabDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWorkTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWorkTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_MainWorkTab,
      qt_meta_data_MainWorkTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWorkTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWorkTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWorkTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWorkTab))
        return static_cast<void*>(const_cast< MainWorkTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int MainWorkTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWorkTab::MountFS(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWorkTab::S_StartInstall(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
static const uint qt_meta_data_UserTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,    9,    8,    8, 0x05,
      61,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      71,    8,    8,    8, 0x0a,
      92,    8,    8,    8, 0x0a,
     109,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UserTab[] = {
    "UserTab\0\0,,\0"
    "StartSetUserInformation(QString,QString,QString)\0"
    "AllDone()\0SetUserInformation()\0"
    "SetRootDone(int)\0SetUserDone(int)\0"
};

void UserTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UserTab *_t = static_cast<UserTab *>(_o);
        switch (_id) {
        case 0: _t->StartSetUserInformation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->AllDone(); break;
        case 2: _t->SetUserInformation(); break;
        case 3: _t->SetRootDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SetUserDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData UserTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UserTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_UserTab,
      qt_meta_data_UserTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UserTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UserTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UserTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserTab))
        return static_cast<void*>(const_cast< UserTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int UserTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void UserTab::StartSetUserInformation(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UserTab::AllDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_DoneTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DoneTab[] = {
    "DoneTab\0"
};

void DoneTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DoneTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DoneTab::staticMetaObject = {
    { &ProgressTabWidget::staticMetaObject, qt_meta_stringdata_DoneTab,
      qt_meta_data_DoneTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DoneTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DoneTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DoneTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DoneTab))
        return static_cast<void*>(const_cast< DoneTab*>(this));
    return ProgressTabWidget::qt_metacast(_clname);
}

int DoneTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ProgressTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_ProgressTab[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      24,   12,   12,   12, 0x0a,
      35,   12,   12,   12, 0x0a,
      45,   12,   12,   12, 0x0a,
      57,   55,   12,   12, 0x0a,
      85,   55,   12,   12, 0x0a,
     118,  115,   12,   12, 0x0a,
     167,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProgressTab[] = {
    "ProgressTab\0\0NextStep()\0PervStep()\0"
    "AskHide()\0AskShow()\0,\0PartedDone(QString,QString)\0"
    "StartInstall(QString,QString)\0,,\0"
    "StartSetUserInformation(QString,QString,QString)\0"
    "AllDone()\0"
};

void ProgressTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProgressTab *_t = static_cast<ProgressTab *>(_o);
        switch (_id) {
        case 0: _t->NextStep(); break;
        case 1: _t->PervStep(); break;
        case 2: _t->AskHide(); break;
        case 3: _t->AskShow(); break;
        case 4: _t->PartedDone((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->StartInstall((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->StartSetUserInformation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->AllDone(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProgressTab::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProgressTab::staticMetaObject = {
    { &QTabWidget::staticMetaObject, qt_meta_stringdata_ProgressTab,
      qt_meta_data_ProgressTab, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProgressTab::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProgressTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProgressTab::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProgressTab))
        return static_cast<void*>(const_cast< ProgressTab*>(this));
    return QTabWidget::qt_metacast(_clname);
}

int ProgressTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
