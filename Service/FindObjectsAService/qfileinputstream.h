#ifndef QFILEINPUTSTREAM_H
#define QFILEINPUTSTREAM_H

#include <QObject>
#include <QFile>

class QFileInputStream: public QObject, public std::streambuf {
Q_OBJECT
    QFile *file;
public:
    explicit QFileInputStream(QFile *file);

protected:
    int_type pbackfail(int_type) override;
    int_type underflow() override;
    int_type uflow() override;
    std::streamsize xsgetn(char *_Ptr, std::streamsize _Count) override;
    pos_type seekoff(off_type pos, std::ios_base::seekdir direction, std::ios_base::openmode not_used) override;
    pos_type seekpos(pos_type pos, std::ios_base::openmode not_used) override;
};


#endif // QFILEINPUTSTREAM_H
