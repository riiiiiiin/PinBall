QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/confirmations.cpp \
    Sources/gamewidgetmanager.cpp \
    Sources/mmainwindow.cpp \
    Sources/gamemap.cpp \
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
    main.cpp \
    Sources/madaptablelabel.cpp \
    Natsume/gamewindow.cpp \
    Natsume/map.cpp \
    Natsume/object.cpp

HEADERS += \
    Headers/confirmations.h \
    Headers/gamewidgetmanager.h \
    Headers/mmainwindow.h \
    Headers/gamemap.h \
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
    Headers/settingsmenu.h \
    Headers/encodedmap.h \
    Headers/madaptablelabel.h \
    Natsume/gamewindow.h \
    Natsume/map.h \
    Natsume/object.h

FORMS += 
    

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/MapEditor_pics/mapeditor_pics.qrc \
    Resources/UI_pics/UI_pics.qrc \
    Resources/Music&SE/sounds.qrc \
    Resources/Game_pics/Game_pics.qrc 