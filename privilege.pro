#-------------------------------------------------
#
# Project created by QtCreator 2016-09-22T22:21:59
#
#-------------------------------------------------
QT += widgets

TARGET = privilege
TEMPLATE = app
DEFINES += PRIV_DLL

SOURCES += \ 
    hprivilegeset.cpp \
    hprivilege.cpp \
    main.cpp \
    hadduserdlg.cpp \
    hmodifypwddlg.cpp \
    hprivilegehandle.cpp \
    hcheckprividlg.cpp

HEADERS  += \ 
    hprivilegeset.h \
    hprivilegeapi.h \
    hprivilege.h \
    hadduserdlg.h \
    hmodifypwddlg.h \
    hprivexport.h \
    hcheckprividlg.h

FORMS += \
    privilegeset.ui \
    adduserdlg.ui \
    modifypwddlg.ui \
    checkprividlg.ui


