/****************************************************************************
** Meta object code from reading C++ file 'sslclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/sslclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sslclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SslClient_t {
    QByteArrayData data[21];
    char stringdata[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SslClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SslClient_t qt_meta_stringdata_SslClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "SslClient"
QT_MOC_LITERAL(1, 10, 9), // "wsaalogon"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "status"
QT_MOC_LITERAL(4, 28, 18), // "updateEnabledState"
QT_MOC_LITERAL(5, 47, 13), // "secureConnect"
QT_MOC_LITERAL(6, 61, 18), // "socketStateChanged"
QT_MOC_LITERAL(7, 80, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(8, 109, 5), // "state"
QT_MOC_LITERAL(9, 115, 15), // "socketEncrypted"
QT_MOC_LITERAL(10, 131, 15), // "socketReadyRead"
QT_MOC_LITERAL(11, 147, 18), // "socketFacReadyRead"
QT_MOC_LITERAL(12, 166, 8), // "sendData"
QT_MOC_LITERAL(13, 175, 11), // "sendFacData"
QT_MOC_LITERAL(14, 187, 11), // "sendLastFac"
QT_MOC_LITERAL(15, 199, 9), // "sslErrors"
QT_MOC_LITERAL(16, 209, 16), // "QList<QSslError>"
QT_MOC_LITERAL(17, 226, 6), // "errors"
QT_MOC_LITERAL(18, 233, 22), // "displayCertificateInfo"
QT_MOC_LITERAL(19, 256, 11), // "connectWsfe"
QT_MOC_LITERAL(20, 268, 4) // "wsaa"

    },
    "SslClient\0wsaalogon\0\0status\0"
    "updateEnabledState\0secureConnect\0"
    "socketStateChanged\0QAbstractSocket::SocketState\0"
    "state\0socketEncrypted\0socketReadyRead\0"
    "socketFacReadyRead\0sendData\0sendFacData\0"
    "sendLastFac\0sslErrors\0QList<QSslError>\0"
    "errors\0displayCertificateInfo\0connectWsfe\0"
    "wsaa"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SslClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   82,    2, 0x08 /* Private */,
       5,    0,   83,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    1,   93,    2, 0x08 /* Private */,
      18,    0,   96,    2, 0x08 /* Private */,
      19,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,

       0        // eod
};

void SslClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SslClient *_t = static_cast<SslClient *>(_o);
        switch (_id) {
        case 0: _t->wsaalogon((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateEnabledState(); break;
        case 2: _t->secureConnect(); break;
        case 3: _t->socketStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 4: _t->socketEncrypted(); break;
        case 5: _t->socketReadyRead(); break;
        case 6: _t->socketFacReadyRead(); break;
        case 7: _t->sendData(); break;
        case 8: _t->sendFacData(); break;
        case 9: _t->sendLastFac(); break;
        case 10: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 11: _t->displayCertificateInfo(); break;
        case 12: _t->connectWsfe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SslClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SslClient::wsaalogon)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SslClient::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SslClient.data,
      qt_meta_data_SslClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SslClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SslClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SslClient.stringdata))
        return static_cast<void*>(const_cast< SslClient*>(this));
    return QWidget::qt_metacast(_clname);
}

int SslClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SslClient::wsaalogon(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
