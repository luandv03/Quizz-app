QT       += core gui
QT += network
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    createexamroom.cpp \
    createquestion.cpp \
    examroomdetail.cpp \
    examroomdialog.cpp \
    examroomlist.cpp \
    examroommanagement.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    profile.cpp \
    signin.cpp \
    signup.cpp \
    tcpconnection.cpp \
    usermanagement.cpp

HEADERS += \
    config.h \
    createexamroom.h \
    createquestion.h \
    examroomdetail.h \
    examroomdialog.h \
    examroomlist.h \
    examroommanagement.h \
    home.h \
    mainwindow.h \
    profile.h \
    signin.h \
    signup.h \
    tcpconnection.h \
    userdata.h \
    usermanagement.h

FORMS += \
    createexamroom.ui \
    createquestion.ui \
    examroomdetail.ui \
    examroomdialog.ui \
    examroomlist.ui \
    examroommanagement.ui \
    home.ui \
    mainwindow.ui \
    profile.ui \
    signin.ui \
    signup.ui \
    usermanagement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
