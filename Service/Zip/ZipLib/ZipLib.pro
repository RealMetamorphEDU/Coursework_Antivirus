TEMPLATE = lib
CONFIG += staticlib c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ZipArchive.cpp \
    ZipArchiveEntry.cpp \
    ZipFile.cpp \
    detail/EndOfCentralDirectoryBlock.cpp \
    detail/ZipCentralDirectoryFileHeader.cpp \
    detail/ZipGenericExtraField.cpp \
    detail/ZipLocalFileHeader.cpp

HEADERS += \
    ZipArchive.h \
    ZipArchiveEntry.h \
    ZipFile.h \
    compression/bzip2/bzip2_decoder.h \
    compression/bzip2/bzip2_decoder_properties.h \
    compression/bzip2/bzip2_encoder.h \
    compression/bzip2/bzip2_encoder_properties.h \
    compression/compression_interface.h \
    compression/deflate/deflate_decoder.h \
    compression/deflate/deflate_decoder_properties.h \
    compression/deflate/deflate_encoder.h \
    compression/deflate/deflate_encoder_properties.h \
    compression/lzma/detail/lzma_alloc.h \
    compression/lzma/detail/lzma_handle.h \
    compression/lzma/detail/lzma_header.h \
    compression/lzma/detail/lzma_in_stream.h \
    compression/lzma/detail/lzma_out_stream.h \
    compression/lzma/lzma_decoder.h \
    compression/lzma/lzma_decoder_properties.h \
    compression/lzma/lzma_encoder.h \
    compression/lzma/lzma_encoder_properties.h \
    compression/store/store_decoder.h \
    compression/store/store_decoder_properties.h \
    compression/store/store_encoder.h \
    compression/store/store_encoder_properties.h \
    detail/EndOfCentralDirectoryBlock.h \
    detail/ZipCentralDirectoryFileHeader.h \
    detail/ZipGenericExtraField.h \
    detail/ZipLocalFileHeader.h \
    methods/Bzip2Method.h \
    methods/DeflateMethod.h \
    methods/ICompressionMethod.h \
    methods/LzmaMethod.h \
    methods/StoreMethod.h \
    methods/ZipMethodResolver.h \
    streams/compression_decoder_stream.h \
    streams/compression_encoder_stream.h \
    streams/crc32stream.h \
    streams/memstream.h \
    streams/nullstream.h \
    streams/serialization.h \
    streams/streambuffs/compression_decoder_streambuf.h \
    streams/streambuffs/compression_encoder_streambuf.h \
    streams/streambuffs/crc32_streambuf.h \
    streams/streambuffs/mem_streambuf.h \
    streams/streambuffs/null_streambuf.h \
    streams/streambuffs/sub_streambuf.h \
    streams/streambuffs/tee_streambuff.h \
    streams/streambuffs/zip_crypto_streambuf.h \
    streams/substream.h \
    streams/teestream.h \
    streams/zip_cryptostream.h \
    utils/enum_utils.h \
    utils/stream_utils.h \
    utils/time_utils.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../zlib/release/ -lzlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../zlib/debug/ -lzlib

INCLUDEPATH += $$PWD/../zlib
DEPENDPATH += $$PWD/../zlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zlib/release/libzlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zlib/debug/libzlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zlib/release/zlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../zlib/debug/zlib.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lzma/release/ -llzma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lzma/debug/ -llzma

INCLUDEPATH += $$PWD/../lzma
DEPENDPATH += $$PWD/../lzma

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lzma/release/liblzma.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lzma/debug/liblzma.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lzma/release/lzma.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lzma/debug/lzma.lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../bzip2/release/ -lbzip2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../bzip2/debug/ -lbzip2

INCLUDEPATH += $$PWD/../bzip2
DEPENDPATH += $$PWD/../bzip2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bzip2/release/libbzip2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bzip2/debug/libbzip2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bzip2/release/bzip2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../bzip2/debug/bzip2.lib
