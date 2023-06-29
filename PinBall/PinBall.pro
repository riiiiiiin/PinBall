QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Game/Sources/gamemap.cpp \
    Game/Sources/gamewindow.cpp \
    Game/Sources/map.cpp \
    Game/Sources/object.cpp \
    MapEditor/Sources/madaptablelabel.cpp \
    MapEditor/Sources/mapeditor.cpp \
    MapEditor/Sources/mdragcontainer.cpp \
    MapEditor/Sources/mdraggable.cpp \
    MapEditor/Sources/mdraggables.cpp \
    MapEditor/Sources/mdraggableshadow.cpp \
    UI_Base/Sources/mbutton.cpp \
    UI_Base/Sources/mcheckbutton.cpp \
    UI_Base/Sources/mconfirmation.cpp \
    UI_Base/Sources/mpushbutton.cpp \
    UI_Base/Sources/mslider.cpp \
    UI_Base/Sources/mtab.cpp \
    FrameWork/Sources/confirmations.cpp \
    FrameWork/Sources/gamewidgetmanager.cpp \
    FrameWork/Sources/pausemenu.cpp \
    FrameWork/Sources/settingsmenu.cpp \
    mainwindow.cpp \
    main.cpp \


HEADERS += \
    Game/Headers/gamemap.h \
    Game/Headers/gamewindow.h \
    Game/Headers/map.h \
    Game/Headers/object.h \
    MapEditor/Headers/madaptablelabel.h \
    MapEditor/Headers/mapeditor.h \
    MapEditor/Headers/mdragcontainer.h \
    MapEditor/Headers/mdraggable.h \
    MapEditor/Headers/mdraggables.h \
    MapEditor/Headers/mdraggableshadow.h \
    UI_Base/Headers/mbutton.h \
    UI_Base/Headers/mcheckbutton.h \
    UI_Base/Headers/mconfirmation.h \
    UI_Base/Headers/mpushbutton.h \
    UI_Base/Headers/mslider.h \
    UI_Base/Headers/mtab.h \
    FrameWork/Headers/encodedmap.h \
    FrameWork/Headers/confirmations.h \
    FrameWork/Headers/gamewidgetmanager.h \
    FrameWork/Headers/pausemenu.h \
    FrameWork/Headers/settingsmenu.h \
    mainwindow.h

FORMS += 
    

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Game/Resources/Game_pics.qrc \
    MapEditor/Resources/mapeditor_pics.qrc \
    UI_Base/Resources/UI_pics.qrc \
    FrameWork/Resources/FrameWork_pics/FrameWork_pics.qrc \
    FrameWork/Resources/Music&SE/sounds.qrc