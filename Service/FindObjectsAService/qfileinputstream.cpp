#include "qfileinputstream.h"

std::basic_streambuf<char>::int_type QFileInputStream::pbackfail(int_type input) {
    char c;
    if (file->seek(file->pos() - 1)) {
        if(file->peek(&c, 1) != 1)
            return traits_type::eof();
        if(static_cast<int_type>(c) != input)
            return traits_type::eof();
        return input;
    }
    return traits_type::eof();
}

std::basic_streambuf<char>::int_type QFileInputStream::underflow() {
    if (file->atEnd())
        return traits_type::eof();
    char c = 0;
    if (file->peek(&c, 1) != 1)
        return traits_type::eof();
    return c;
}

std::basic_streambuf<char>::int_type QFileInputStream::uflow() {
    if (file->atEnd())
        return traits_type::eof();
    char c = 0;
    if (file->read(&c, 1) != 1)
        return traits_type::eof();
    return c;
}

std::streamsize QFileInputStream::xsgetn(char *_Ptr, std::streamsize _Count) {
    return file->read(_Ptr, _Count);
}

std::basic_streambuf<char>::pos_type QFileInputStream::seekoff(off_type pos, std::ios_base::seekdir direction,
                                                               std::ios_base::openmode) {
    switch (direction) {
        default:
        case std::ios_base::beg:
            if (file->seek(pos))
                return file->pos();
            return -1;
        case std::ios_base::cur:
            if (file->seek(file->pos() + pos))
                return file->pos();
            return -1;
        case std::ios_base::end:
            if (file->seek(file->size() + pos))
                return file->pos();
            return -1;
    }
}

std::basic_streambuf<char>::pos_type QFileInputStream::seekpos(pos_type pos, std::ios_base::openmode) {
    if (file->seek(pos))
        return file->pos();
    return -1;
}

QFileInputStream::QFileInputStream(QFile *file): QObject(file) {
    this->file = file;
}
