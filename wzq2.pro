QT       += core gui
RC_ICONS = wzq.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aiwin.cpp \
    bigin.cpp \
    forl.cpp \
    help.cpp \
    main.cpp \
    mainwindow.cpp \
    playerwin.cpp \
    thirdchange.cpp

HEADERS += \
    aiwin.h \
    bigin.h \
    forl.h \
    help.h \
    mainwindow.h \
    playerwin.h \
    thirdchange.h

FORMS += \
    aiwin.ui \
    bigin.ui \
    forl.ui \
    help.ui \
    mainwindow.ui \
    playerwin.ui \
    thirdchange.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
