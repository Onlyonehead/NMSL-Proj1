#-------------------------------------------------
#
# Project created by QtCreator 2018-06-21T15:50:01
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LogisticsManagementSystem
TEMPLATE = app

PRECOMPILED_HEADER = stable.h

CONFIG+=resources_big

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    login.cpp \
    systemcenter.cpp \
    forgetpassword.cpp \
    mainwindow.cpp\
    warehouse_a.cpp \
    warehouse_c.cpp \
    store.cpp \
    purchasepage.cpp \
    systempage.cpp \
    garment.cpp \
    provider.cpp \
    warehouse_b.cpp \
    record.cpp \
    providerpage.cpp \
    logistics.cpp \
    personnelpage_1.cpp \
    personnelpage_2.cpp \
    main_tab_sell.cpp \
    main_tab_stock.cpp \
    main_tab_record.cpp \
    main_tab_delivery.cpp \
    sqltool.cpp \
    systemcenter_msg.cpp \
    order.cpp



HEADERS  += \
    login.h \
    systemcenter.h \
    forgetpassword.h \
    mainwindow.h\
    store.h \
    garment.h \
    provider.h \
    record.h \
    logistics.h \
    stable.h \
    sqltool.h \
    order.h



FORMS    += \
    login.ui \
    systemcenter.ui \
    forgetpassword.ui \
    mainwindow.ui


RESOURCES += \
    ../Resources/resources.qrc

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
