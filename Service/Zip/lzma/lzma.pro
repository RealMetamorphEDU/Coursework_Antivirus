TEMPLATE = lib
CONFIG += staticlib c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    7zAlloc.c \
    7zBuf.c \
    7zBuf2.c \
    7zCrc.c \
    7zCrcOpt.c \
    7zDec.c \
    7zFile.c \
    7zIn.c \
    7zStream.c \
    Alloc.c \
    Bcj2.c \
    Bra.c \
    Bra86.c \
    BraIA64.c \
    CpuArch.c \
    Delta.c \
    LzFind.c \
    LzFindMt.c \
    Lzma2Dec.c \
    Lzma2Enc.c \
    Lzma86Dec.c \
    Lzma86Enc.c \
    LzmaDec.c \
    LzmaEnc.c \
    LzmaLib.c \
    MtCoder.c \
    Ppmd7.c \
    Ppmd7Dec.c \
    Ppmd7Enc.c \
    Sha256.c \
    Threads.c \
    Xz.c \
    XzCrc64.c \
    XzDec.c \
    XzEnc.c \
    XzIn.c

HEADERS += \
    7z.h \
    7zAlloc.h \
    7zBuf.h \
    7zCrc.h \
    7zFile.h \
    7zVersion.h \
    Alloc.h \
    Bcj2.h \
    Bra.h \
    CpuArch.h \
    Delta.h \
    LzFind.h \
    LzFindMt.h \
    LzHash.h \
    Lzma2Dec.h \
    Lzma2Enc.h \
    Lzma86.h \
    LzmaDec.h \
    LzmaEnc.h \
    LzmaLib.h \
    MtCoder.h \
    Ppmd.h \
    Ppmd7.h \
    RotateDefs.h \
    Sha256.h \
    Threads.h \
    Types.h \
    Xz.h \
    XzCrc64.h \
    XzEnc.h
