QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/confirmations.cpp \
    Sources/gamewidgetmanager.cpp \
    Sources/mainwindow.cpp \
    Sources/map.cpp \
    Sources/mapeditor.cpp \
    Sources/mbutton.cpp \
    Sources/mcheckbutton.cpp \
    Sources/mconfirmation.cpp \
    Sources/mdragcontainer.cpp \
    Sources/mdraggable.cpp \
    Sources/mdraggables.cpp \
    Sources/mdraggableshadow.cpp \
    Sources/mpushbutton.cpp \
    Sources/mslider.cpp \
    Sources/mtab.cpp \
    Sources/pausemenu.cpp \
    Sources/settingsmenu.cpp \
    main.cpp

HEADERS += \
    Headers/confirmations.h \
    Headers/gamewidgetmanager.h \
    Headers/mainwindow.h \
    Headers/map.h \
    Headers/mapeditor.h \
    Headers/mbutton.h \
    Headers/mcheckbutton.h \
    Headers/mconfirmation.h \
    Headers/mdragcontainer.h \
    Headers/mdraggable.h \
    Headers/mdraggables.h \
    Headers/mdraggableshadow.h \
    Headers/mpushbutton.h \
    Headers/mslider.h \
    Headers/mtab.h \
    Headers/pausemenu.h \
    Headers/settingsmenu.h

FORMS += 
    

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/game_pics.qrc \
    Resources/pics.qrc \
    Resources/sounds.qrc
