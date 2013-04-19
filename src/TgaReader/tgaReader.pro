TARGET = TgaReader
TEMPLATE = lib
CONFIG = qt plugin debug
VERSION = 1.0.0

HEADERS = tgaReader.hpp

SOURCES = tgaReader.cpp

OTHER_FILES = tga.json

TOP_LEVEL = ../..

OBJECTS_DIR = $$TOP_LEVEL/build
MOC_DIR = $$TOP_LEVEL/build
RCC_DIR = $$TOP_LEVEL/build
UI_DIR = $$TOP_LEVEL/build
