QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exitconfirm.cpp \
    main.cpp \
    mainwindow.cpp \
    mcheckbutton.cpp \
    mpushbutton.cpp \
    pausemenu.cpp

HEADERS += \
    exitconfirm.h \
    mainwindow.h \
    mcheckbutton.h \
    mpushbutton.h \
    pausemenu.h

FORMS += \
    exitconfirm.ui \
    mainwindow.ui \
    pausemenu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc \
    sounds.qrc
