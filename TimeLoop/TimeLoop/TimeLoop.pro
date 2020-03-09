QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    arrcilcularlinkedlist.cpp \
    benchmarkwindow.cpp \
    circularlinkedlist.cpp \
    functs.cpp \
    interactwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    station.cpp \
    table.cpp \
    vectcircularlinkedlist.cpp

HEADERS += \
    arrcilcularlinkedlist.h \
    benchmark.h \
    benchmarkwindow.h \
    circularlinkedlist.h \
    functs.h \
    interactwindow.h \
    mainwindow.h \
    station.h \
    table.h \
    vectcircularlinkedlist.h

FORMS += \
    benchmarkwindow.ui \
    interactwindow.ui \
    mainwindow.ui

OTHER_FILES += \
    $$PWD/resources

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    KUT.txt \
    MCC.txt \
    MMC.txt

copydata.commands = $(COPY_FILE) \"$$shell_path($$PWD\\resources)\" \"$$shell_path($$OUT_PWD)\"
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
