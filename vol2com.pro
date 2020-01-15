QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += \
    QT_DEPRECATED_WARNINGS \
    #QT_NO_DEBUG_OUTPUT

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    "C:\Qt\libs\bass\2.4.15\src" \
    "C:\Qt\libs\basswasapi\2.4.2\c"

win32: {
    contains(QMAKE_TARGET.arch, x86_64): {
        message("x64 build")
        LIBS += \
            "C:\Qt\libs\bass\2.4.15\src\x64\bass.lib" \
            "C:\Qt\libs\basswasapi\2.4.2\c\x64\basswasapi.lib"
    } else {
        message("x32 build")
        LIBS += \
            "C:\Qt\libs\bass\2.4.15\src\bass.lib" \
            "C:\Qt\libs\basswasapi\2.4.2\c\basswasapi.lib"
    }
}

SOURCES += \
    basslib.cpp \
    controller.cpp \
    guihelper.cpp \
    main.cpp \
    mainwindow.cpp \
    serial.cpp \
    tray.cpp

HEADERS += \
    basslib.h \
    capturemethodbase.h \
    constants.h \
    controller.h \
    guihelper.h \
    mainwindow.h \
    serial.h \
    tray.h

TRANSLATIONS += \
    vol2com_ru_RU.ts

RESOURCES += \
    main.qrc \

RC_FILE += \
    resource.rc

DISTFILES += \
    resource.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
