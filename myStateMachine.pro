TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    hsm/hsm.c \
        main.cpp \
        sm.c \
    unitTests/smTests.cpp

HEADERS += \
    globals.h \
    hsm/hsm.h \
    sm.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/x64/release/ -lCppUTestd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/x64/debug/ -lCppUTestd

INCLUDEPATH += $$PWD/../../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/include
DEPENDPATH += $$PWD/../../../../../../ARSIS-SW/Software/trunk/main/Test/cpputest-3.8/include
