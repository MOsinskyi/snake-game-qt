QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameaudio.cpp \
    gamefield.cpp \
    gamewindow.cpp \
    main.cpp \
    snake.cpp \
    userfield.cpp

HEADERS += \
    colormanager.h \
    fontmanager.h \
    gameaudio.h \
    gamefield.h \
    gamewindow.h \
    snake.h \
    userfield.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

FORMS +=

RESOURCES += \
    res.qrc
