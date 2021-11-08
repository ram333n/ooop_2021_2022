QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    donotdisturbwindow.cpp \
    inputwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    timer.cpp \
    timersignal.cpp

HEADERS += \
    donotdisturbwindow.h \
    inputwindow.h \
    mainwindow.h \
    timer.h \
    timersignal.h

FORMS += \
    donotdisturbwindow.ui \
    inputwindow.ui \
    mainwindow.ui \
    timersignal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    multimedia.qrc

DISTFILES +=
