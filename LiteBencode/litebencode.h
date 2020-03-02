#ifndef LITEBENCODE_H
#define LITEBENCODE_H

#include "LiteBencode_global.h"
#include <QtCore\qfile.h>
#include "belement.h"


class LITEBENCODE_EXPORT LiteBencode: public QObject {
Q_OBJECT
	QFile *file;
	const char token[7] = {'t', 'i', 'm', 'c', 'h', 'u', 'k'};
	bool baseFile;
public:
	LiteBencode(QFile *file, QObject *parent = nullptr);

	bool isBaseFile() const;

	static bool validateFile();

	BListReadable* getReadableRoot();
	BListWritable* getWritableRoot();
};

#endif // LITEBENCODE_H
