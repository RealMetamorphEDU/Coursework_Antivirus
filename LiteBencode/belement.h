#ifndef BELEMENT_H
#define BELEMENT_H

#include <qfile.h>
#include "LiteBencode_global.h"
#include <QObject>

enum class BElementType {
    bList = 0,
    bListWritable,
    bString,
    bInteger
};

class LITEBENCODE_EXPORT BElement: public QObject {
Q_OBJECT
public:
    explicit BElement(QObject *parent);

    virtual BElementType getType() = 0;
};

class LITEBENCODE_EXPORT BListWritable: public BElement {
Q_OBJECT
    bool closed;
    QFile *file;
    bool opened;
    bool inheritOpen;
    BListWritable *inheritList;
public:
    explicit BListWritable(QObject *parent = nullptr);

    BElementType getType() override;

    bool writeElement(BElement *element);
    BListWritable* openList();
    bool closeList();

    void setFileWritable(QFile *file);
};

class LITEBENCODE_EXPORT BListReadable: public BElement {
Q_OBJECT
    QFile *file;
    bool opened;
    bool closed;
    qint64 offset;

    void closing();
public:
    explicit BListReadable(QObject *parent = nullptr);

    BElementType getType() override;

    BElement* nextToken();
    bool hasNextToken();

    void toFirstToken();

    void setFileReadable(QFile *file, int offset);

    qint64 getOffset();
};

class LITEBENCODE_EXPORT BString: public BElement {
Q_OBJECT
    QByteArray value;
public:
    explicit BString(QObject *parent = nullptr);

    BElementType getType() override;

    QByteArray getValue() const;

    void setValue(const QByteArray &value);

    QByteArray toBencode() const;
};

class LITEBENCODE_EXPORT BInteger: public BElement {
Q_OBJECT
    int value;
public:
    explicit BInteger(QObject *parent = nullptr);

    BElementType getType() override;

    int getValue() const;
    void setValue(int value);
    QByteArray toBencode() const;
};

#endif // BELEMENT_H
