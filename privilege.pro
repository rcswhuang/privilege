#-------------------------------------------------
#
# Project created by QtCreator 2016-09-22T22:21:59
#
#-------------------------------------------------
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = privilege
TEMPLATE = lib
DESTDIR += ../lib
DEFINES += PRIV_DLL

CONFIG += qt warn_off thread exceptions

INCLUDEPATH += \
           ../include
win32{
    #LIBS += ../../lib/licensrv.lib
}
unix {
    #LIBS += -L../../lib -llicensrv
}


SOURCES += \ 
    hprivilegeset.cpp \
    hprivilege.cpp \
    #main.cpp \
    hadduserdlg.cpp \
    hmodifypwddlg.cpp \
    hprivilegehandle.cpp \
    hcheckprividlg.cpp

HEADERS  += \ 
    hprivilegeset.h \
    #hprivilegeapi.h \
    hprivilege.h \
    hadduserdlg.h \
    hmodifypwddlg.h \
    #hprivexport.h \
    hcheckprividlg.h

FORMS += \
    privilegeset.ui \
    adduserdlg.ui \
    modifypwddlg.ui \
    checkprividlg.ui

LIBS += -L../lib -lH5ConfigHelp -ldatafile

unix{
    UI_DIR = temp/ui
    MOC_DIR = tem/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \

}

win32{
    UI_DIR = temp/ui
    MOC_DIR = temp/moc
    OBJECTS_DIR	= temp/obj
    LIBS += \
}
