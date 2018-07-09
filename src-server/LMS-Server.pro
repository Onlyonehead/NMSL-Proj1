#-------------------------------------------------
#
# Project created by QtCreator 2018-07-06T11:21:18
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LMS-Server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    login.cpp \
    sqltool.cpp \
    TCPConnection.cpp \
    forgetpassword.cpp \
<<<<<<< HEAD
    store.cpp \
    record.cpp
=======
    warehouse.cpp \
    tool.cpp \
    order.cpp \
    myserver.cpp \
    socketthread.cpp \
    processor.cpp
>>>>>>> faaffdc84f655b4ee4ea3631e05215d153568b5a

HEADERS  += \
    login.h \
    sqltool.h \
    TCPConnection.h \
    forgetpassword.h \
<<<<<<< HEAD
    store.h \
    record.h
=======
    warehouse.h \
    tool.h \
    order.h \
    myserver.h \
    socketthread.h \
    processor.h
>>>>>>> faaffdc84f655b4ee4ea3631e05215d153568b5a

win32{
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_MinGW_32bit-Debug/release/ -lSMTPEmail
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_MinGW_32bit-Debug/debug/ -lSMTPEmail
else:unix: LIBS += -L$$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_MinGW_32bit-Debug/ -lSMTPEmail
INCLUDEPATH += $$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_MinGW_32bit-Debug/debug
}

unix{
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_clang_64bit-Debug/release/ -lSMTPEmail.1.0.0
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_clang_64bit-Debug/debug/ -lSMTPEmail.1.0.0
else:unix: LIBS += -L$$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_clang_64bit-Debug/ -lSMTPEmail.1.0.0
INCLUDEPATH += $$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_clang_64bit-Debug
DEPENDPATH += $$PWD/../packages/build-SMTPEmail-Desktop_Qt_5_7_1_clang_64bit-Debug
}
