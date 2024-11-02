/****************************************************************************
** Meta object code from reading C++ file 'QRabbitMQ.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../QRabbitMQ.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QRabbitMQ.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QRabbitMQ_t {
    const uint offsetsAndSize[18];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_QRabbitMQ_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_QRabbitMQ_t qt_meta_stringdata_QRabbitMQ = {
    {
QT_MOC_LITERAL(0, 9), // "QRabbitMQ"
QT_MOC_LITERAL(10, 6), // "msgSig"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 3), // "msg"
QT_MOC_LITERAL(22, 5), // "start"
QT_MOC_LITERAL(28, 15), // "clientConnected"
QT_MOC_LITERAL(44, 16), // "exchangeDeclared"
QT_MOC_LITERAL(61, 13), // "queueDeclared"
QT_MOC_LITERAL(75, 15) // "messageReceived"

    },
    "QRabbitMQ\0msgSig\0\0msg\0start\0clientConnected\0"
    "exchangeDeclared\0queueDeclared\0"
    "messageReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QRabbitMQ[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   53,    2, 0x0a,    3 /* Public */,
       5,    0,   54,    2, 0x08,    4 /* Private */,
       6,    0,   55,    2, 0x08,    5 /* Private */,
       7,    0,   56,    2, 0x08,    6 /* Private */,
       8,    0,   57,    2, 0x08,    7 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QRabbitMQ::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QRabbitMQ *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->msgSig((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->start(); break;
        case 2: _t->clientConnected(); break;
        case 3: _t->exchangeDeclared(); break;
        case 4: _t->queueDeclared(); break;
        case 5: _t->messageReceived(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QRabbitMQ::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QRabbitMQ::msgSig)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject QRabbitMQ::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QRabbitMQ.offsetsAndSize,
    qt_meta_data_QRabbitMQ,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_QRabbitMQ_t
, QtPrivate::TypeAndForceComplete<QRabbitMQ, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *QRabbitMQ::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QRabbitMQ::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QRabbitMQ.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QRabbitMQ::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QRabbitMQ::msgSig(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
