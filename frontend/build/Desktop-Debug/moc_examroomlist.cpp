/****************************************************************************
** Meta object code from reading C++ file 'examroomlist.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../examroomlist.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'examroomlist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSExamRoomListENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSExamRoomListENDCLASS = QtMocHelpers::stringData(
    "ExamRoomList",
    "showExamRoomDetail",
    "",
    "roomId",
    "showUserManagement",
    "showExamRoomManagement",
    "showProfile",
    "logout",
    "on_searchButton_clicked",
    "on_avatarButton_clicked",
    "onReadyRead",
    "handleJoinRoomResponse",
    "handleJoinButtonClicked",
    "onConnected",
    "onDisconnected",
    "showMenuNavigator"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSExamRoomListENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x06,    1 /* Public */,
       4,    0,   95,    2, 0x06,    3 /* Public */,
       5,    0,   96,    2, 0x06,    4 /* Public */,
       6,    0,   97,    2, 0x06,    5 /* Public */,
       7,    0,   98,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,   99,    2, 0x08,    7 /* Private */,
       9,    0,  100,    2, 0x08,    8 /* Private */,
      10,    0,  101,    2, 0x08,    9 /* Private */,
      11,    0,  102,    2, 0x08,   10 /* Private */,
      12,    1,  103,    2, 0x08,   11 /* Private */,
      13,    0,  106,    2, 0x08,   13 /* Private */,
      14,    0,  107,    2, 0x08,   14 /* Private */,
      15,    0,  108,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ExamRoomList::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSExamRoomListENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSExamRoomListENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSExamRoomListENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ExamRoomList, std::true_type>,
        // method 'showExamRoomDetail'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'showUserManagement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showExamRoomManagement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showProfile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'logout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_searchButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_avatarButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleJoinRoomResponse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleJoinButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onConnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDisconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showMenuNavigator'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ExamRoomList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ExamRoomList *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->showExamRoomDetail((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->showUserManagement(); break;
        case 2: _t->showExamRoomManagement(); break;
        case 3: _t->showProfile(); break;
        case 4: _t->logout(); break;
        case 5: _t->on_searchButton_clicked(); break;
        case 6: _t->on_avatarButton_clicked(); break;
        case 7: _t->onReadyRead(); break;
        case 8: _t->handleJoinRoomResponse(); break;
        case 9: _t->handleJoinButtonClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onDisconnected(); break;
        case 12: _t->showMenuNavigator(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ExamRoomList::*)(int );
            if (_t _q_method = &ExamRoomList::showExamRoomDetail; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ExamRoomList::*)();
            if (_t _q_method = &ExamRoomList::showUserManagement; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ExamRoomList::*)();
            if (_t _q_method = &ExamRoomList::showExamRoomManagement; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ExamRoomList::*)();
            if (_t _q_method = &ExamRoomList::showProfile; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ExamRoomList::*)();
            if (_t _q_method = &ExamRoomList::logout; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *ExamRoomList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ExamRoomList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSExamRoomListENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ExamRoomList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ExamRoomList::showExamRoomDetail(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ExamRoomList::showUserManagement()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ExamRoomList::showExamRoomManagement()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ExamRoomList::showProfile()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ExamRoomList::logout()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
