QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets


CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullets.cpp \
    enemy.cpp \
    gamedata.cpp \
    main.cpp \
    mainwindow.cpp \
    openglwidget.cpp \
    player.cpp \
    power.cpp \
    starlayers.cpp

HEADERS += \
    bullets.h \
    enemy.h \
    gamedata.h \
    mainwindow.h \
    openglwidget.h \
    player.h \
    power.h \
    starlayers.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
