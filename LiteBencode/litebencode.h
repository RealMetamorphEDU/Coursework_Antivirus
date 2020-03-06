#ifndef LITEBENCODE_H
#define LITEBENCODE_H


#include <QObject>
#include "LiteBencode_global.h"
#include <QtCore\qfile.h>
#include "belement.h"


class LITEBENCODE_EXPORT LiteBencode: public QObject {
Q_OBJECT
private:
	QFile *file;
	const char token[8] = {'t', 'i', 'm', 'c', 'h', 'u', 'k', 0};
	bool baseFile;
public:
	LiteBencode(QFile *file, QObject *parent = nullptr);

	~LiteBencode();

	bool isBaseFile() const;

	BListReadable* getReadableRoot();
	BListWritable* getWritableRoot();
};

#endif // LITEBENCODE_H
