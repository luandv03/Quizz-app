QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    examroomdetail.cpp \
    examroomdialog.cpp \
    examroomlist.cpp \
    examroommanagement.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    signin.cpp \
    signup.cpp \
    usermanagement.cpp

HEADERS += \
    examroomdetail.h \
    examroomdialog.h \
    examroomlist.h \
    examroommanagement.h \
    home.h \
    mainwindow.h \
    signin.h \
    signup.h \
    usermanagement.h

FORMS += \
    examroomdetail.ui \
    examroomdialog.ui \
    examroomlist.ui \
    examroommanagement.ui \
    home.ui \
    mainwindow.ui \
    signin.ui \
    signup.ui \
    usermanagement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
