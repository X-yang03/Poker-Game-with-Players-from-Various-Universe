QT       += core gui
QT       += multimedia
QT       += multimediawidgets
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    AIplayer.cpp \
    Data.cpp \
    card.cpp \
    gameRun.cpp \
    gameStartWidget.cpp \
    help.cpp \
    main.cpp \
    mybutton.cpp \
    playerSelf.cpp \
    scene1Players.cpp \
    scene2Players.cpp \
    scene3Players.cpp \
    scene4Players.cpp \
    sceneChoose.cpp \
    server.cpp \
    welcomescene.cpp \
    widget.cpp

HEADERS += \
    AIplayer.h \
    Data.h \
    card.h \
    gameRun.h \
    gameStartWidget.h \
    help.h \
    mybutton.h \
    playerSelf.h \
    scene1Players.h \
    scene2Players.h \
    scene3Players.h \
    scene4Players.h \
    sceneChoose.h \
    server.h \
    welcomscene.h \
    widget.h

FORMS += \
    server.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    audio.qrc \
    image_resource.qrc
