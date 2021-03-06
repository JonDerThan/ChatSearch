QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chartswidget.cpp \
    countpiechart.cpp \
    counttable.cpp \
    daytable.cpp \
    main.cpp \
    mainwindow.cpp \
    phrasecounter.cpp \
    streak.cpp \
    streaktable.cpp \
    whatsappchat.cpp \
    whatsappmessage.cpp

HEADERS += \
    chartswidget.h \
    countpiechart.h \
    counttable.h \
    daytable.h \
    mainwindow.h \
    phrasecounter.h \
    streak.h \
    streaktable.h \
    whatsappchat.h \
    whatsappmessage.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
