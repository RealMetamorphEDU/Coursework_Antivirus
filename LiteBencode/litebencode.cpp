#include "litebencode.h"

LiteBencode::LiteBencode(QFile *file, QObject *parent) : QObject(parent) {
	this->file = file;
	file->setParent(this);
	file->open(QFile::ReadWrite | QFile::Unbuffered);
	if (file->isOpen()) {
		if (file->size() == 0) {
			file->write(this->token);
			file->write("li0ee", 5);
			file->seek(0);
		}
		char data[7]{0};
		file->read(data, 7);
		if (!strcmp(this->token, data))
			baseFile = false;
		else
			baseFile = true;
	} else
		baseFile = false;
}

LiteBencode::~LiteBencode() {
	if (file->isOpen()) {
		file->close();
	}
}

bool LiteBencode::isBaseFile() const {
	return baseFile;
}

BListReadable* LiteBencode::getReadableRoot() {
	if (baseFile) {
		BListReadable *list = new BListReadable(this);
		list->setFileReadable(file, 7);
		return list;
	}
	return nullptr;
}

BListWritable* LiteBencode::getWritableRoot() {
	if (file->isOpen()) {
		file->seek(0);
		file->write(this->token);
		BListWritable *list = new BListWritable(this);
		list->setFileWritable(file);
		return list;
	}
	return nullptr;
}
