QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    examroomdetail.cpp \
    examroomlist.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    signin.cpp \
    signup.cpp

HEADERS += \
    examroomdetail.h \
    examroomlist.h \
    home.h \
    mainwindow.h \
    signin.h \
    signup.h

FORMS += \
    examroomdetail.ui \
    examroomlist.ui \
    home.ui \
    mainwindow.ui \
    signin.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
