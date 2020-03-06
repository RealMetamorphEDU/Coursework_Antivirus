#include "belement.h"

BElement::BElement(QObject *parent) : QObject(parent) {
};


void BListWritable::setFileWritable(QFile *file) {
	if (!opened) {
		this->file = file;
		opened = true;
		closed = false;
		file->write("l", 1);
	}
}

BListWritable::BListWritable(QObject *parent) : BElement(parent) {
	closed = false;
	opened = false;
	inheritOpen = false;
	inheritList = nullptr;
	file = nullptr;
}

BElementType BListWritable::getType() {
	return BElementType::bListWritable;
}

bool BListWritable::writeElement(BElement *element) {
	if (opened && !closed) {
		switch (element->getType()) {
			case BElementType::bListWritable:
				if (inheritOpen && inheritList->closed) {
					inheritOpen = false;
					inheritList = nullptr;
				}
				if (!inheritOpen) {
					BListWritable *list;
					list = dynamic_cast<BListWritable*>(element);
					list->setFileWritable(file);
					inheritOpen = true;
					inheritList = list;
					return true;
				}
				break;
			case BElementType::bInteger:
				if (inheritOpen && inheritList->closed) {
					inheritOpen = false;
					inheritList = nullptr;
				}
				if (!inheritOpen) {
					BInteger *integer;
					integer = dynamic_cast<BInteger*>(element);
					file->write(integer->toBencode());
					return true;
				}
				break;
			case BElementType::bString:
				if (inheritOpen && inheritList->closed) {
					inheritOpen = false;
					inheritList = nullptr;
				}
				if (!inheritOpen) {
					BString *string;
					string = dynamic_cast<BString*>(element);
					file->write(string->toBencode());
					return true;
				}
				break;
			default:
				return false;
		}
	}
	return false;
}

bool BListWritable::closeList() {
	if (opened && !inheritOpen) {
		opened = false;
		closed = true;
		file->write("e", 1);
		return true;
	}
	return false;
}

void BListReadable::setFileReadable(QFile *file, int offset) {
	this->file = file;
	this->offset = offset;
	char start;
	file->seek(offset);
	file->peek(&start, 1);
	if (start == 'l') {
		file->read(&start, 1);
		opened = true;
		closed = false;
	} else
		opened = false;
}

qint64 BListReadable::getOffset() {
	return offset;
}

BListReadable::BListReadable(QObject *parent) : BElement(parent) {
	closed = false;
	opened = false;
	offset = 0;
	file = nullptr;
}

BElementType BListReadable::getType() {
	return BElementType::bList;
}

BElement* BListReadable::nextToken() {
	if (opened && !closed) {
		char start;
		file->peek(&start, 1);
		QByteArray data;
		switch (start) {
			case 'e':
				closed = true;
				return nullptr;
			case 'i':
				file->read(&start, 1);
				file->read(&start, 1);
				while (start != 'e') {
					data.append(start);
					file->read(&start, 1);
				}
				BInteger *integer;
				integer = new BInteger(this);
				integer->setValue(data.toInt());
				return integer;
			case 'l':
				BListReadable *list;
				list = new BListReadable(this);
				list->setFileReadable(file, file->pos());
				return list;
			default:
				file->read(&start, 1);
				while (start != ':') {
					data.append(start);
					file->read(&start, 1);
				}
				int len = data.toInt();
				data.clear();
				data = file->read(len);
				BString *string = new BString(this);
				string->setValue(data);
				return string;
		}
	}
	return nullptr;
}

bool BListReadable::hasNextToken() {
	if (opened && !closed) {
		char start;
		file->peek(&start, 1);
		if (start == 'e') {
			closed = true;
		}
	}
	return !closed;
}

void BListReadable::toFirstToken() {
	if (opened) {
		file->seek(offset + 1);
		closed = false;
	}
}

BString::BString(QObject *parent) : BElement(parent) {
	value = QByteArray(0, '\0');
}

BElementType BString::getType() {
	return BElementType::bString;
}

QByteArray BString::getValue() const {
	return value;
}

void BString::setValue(QByteArray &value) {
	this->value.clear();
	this->value.push_back(value);
}

QByteArray BString::toBencode() const {
	QByteArray result;
	result.append(QByteArray::number(value.size())).append(':').append(value);
	return result;
}

BInteger::BInteger(QObject *parent) : BElement(parent) {
	value = 0;
}

BElementType BInteger::getType() {
	return BElementType::bInteger;
}

int BInteger::getValue() const {
	return value;
}

void BInteger::setValue(int value) {
	this->value = value;
}

QByteArray BInteger::toBencode() const {
	QByteArray result;
	result.append('i').append(QByteArray::number(value)).append('e');
	return result;
}
