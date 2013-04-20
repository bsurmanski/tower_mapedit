CONFIG += debug
HEADERS += \
        src/mainWindow.hpp \
        src/newMapDialog.hpp \
        src/mainFileMenu.hpp \
        src/mainWindowMenu.hpp \
        src/mainHelpMenu.hpp \
        src/mainMenuBar.hpp \
        src/mainGLWidget.hpp \
        src/toolboxWidget.hpp \
        src/FlowLayout.h 

SOURCES += \
            src/main.cpp \
            src/mainWindow.cpp \
            src/newMapDialog.cpp \
            src/mainFileMenu.cpp \
            src/mainWindowMenu.cpp \
            src/mainHelpMenu.cpp \
            src/mainMenuBar.cpp \
            src/mainGLWidget.cpp \
            src/toolboxWidget.cpp \
            src/FlowLayout.cpp  \
            src/map.c

TARGET = mapedit
QT = core gui opengl
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += GL_GLEXT_PROTOTYPES DEBUG
LIBS += -lglb -L/usr/local/lib -lcw
INCLUDEPATH += /usr/local/include

