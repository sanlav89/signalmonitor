QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fftengine.cpp \
    graphbase.cpp \
    graphspectrum.cpp \
    main.cpp \
    myplotpicker.cpp \
    myscaledraw.cpp \
    myzoomer.cpp \
    signalmonitor.cpp

HEADERS += \
    fftengine.h \
    graphbase.h \
    graphspectrum.h \
    myplotpicker.h \
    myscaledraw.h \
    myzoomer.h \
    signalmonitor.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += C:/qwt-6.1.5/include
LIBS += -LC:/qwt-6.1.5/lib -lqwt

