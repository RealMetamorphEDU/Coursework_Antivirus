TEMPLATE = lib
CONFIG += staticlib c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    blocksort.c \
    bzerror.c \
    bzlib.c \
    compress.c \
    crctable.c \
    decompress.c \
    huffman.c \
    randtable.c

HEADERS += \
    bzlib.h \
    bzlib_private.h
