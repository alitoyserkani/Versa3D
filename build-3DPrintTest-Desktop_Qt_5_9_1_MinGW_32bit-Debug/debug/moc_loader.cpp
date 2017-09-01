/****************************************************************************
** Meta object code from reading C++ file 'loader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/loader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Loader_t {
    QByteArrayData data[12];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Loader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Loader_t qt_meta_stringdata_Loader = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Loader"
QT_MOC_LITERAL(1, 7, 11), // "loaded_file"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "filename"
QT_MOC_LITERAL(4, 29, 8), // "got_mesh"
QT_MOC_LITERAL(5, 38, 5), // "Mesh*"
QT_MOC_LITERAL(6, 44, 1), // "m"
QT_MOC_LITERAL(7, 46, 9), // "is_reload"
QT_MOC_LITERAL(8, 56, 13), // "error_bad_stl"
QT_MOC_LITERAL(9, 70, 16), // "error_empty_mesh"
QT_MOC_LITERAL(10, 87, 21), // "warning_confusing_stl"
QT_MOC_LITERAL(11, 109, 18) // "error_missing_file"

    },
    "Loader\0loaded_file\0\0filename\0got_mesh\0"
    "Mesh*\0m\0is_reload\0error_bad_stl\0"
    "error_empty_mesh\0warning_confusing_stl\0"
    "error_missing_file"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Loader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    2,   47,    2, 0x06 /* Public */,
       8,    0,   52,    2, 0x06 /* Public */,
       9,    0,   53,    2, 0x06 /* Public */,
      10,    0,   54,    2, 0x06 /* Public */,
      11,    0,   55,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Bool,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Loader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Loader *_t = static_cast<Loader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loaded_file((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->got_mesh((*reinterpret_cast< Mesh*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->error_bad_stl(); break;
        case 3: _t->error_empty_mesh(); break;
        case 4: _t->warning_confusing_stl(); break;
        case 5: _t->error_missing_file(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Loader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::loaded_file)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Loader::*_t)(Mesh * , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::got_mesh)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Loader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::error_bad_stl)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Loader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::error_empty_mesh)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Loader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::warning_confusing_stl)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Loader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Loader::error_missing_file)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Loader::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Loader.data,
      qt_meta_data_Loader,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Loader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Loader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Loader.stringdata0))
        return static_cast<void*>(const_cast< Loader*>(this));
    return QThread::qt_metacast(_clname);
}

int Loader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Loader::loaded_file(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Loader::got_mesh(Mesh * _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Loader::error_bad_stl()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Loader::error_empty_mesh()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Loader::warning_confusing_stl()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Loader::error_missing_file()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
