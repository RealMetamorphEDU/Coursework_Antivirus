#ifndef ABRECORDTOKENIZER_H
#define ABRECORDTOKENIZER_H

#include "ABRecordTokenizer_global.h"
#include <qfile.h>
#include <QObject>
#include "signaturerecord.h"

class LiteBencode;
class BListWritable;
class BListReadable;

class ABRECORDTOKENIZER_EXPORT ABRecordTokenizer: public QObject {
Q_OBJECT
    QFile *currentFile;
    LiteBencode *liteBencode;
    BListWritable *writable;
    BListReadable *readable;
    bool reading;
    bool writing;
    int prepareCount;
    int currentCount;

public:
    explicit ABRecordTokenizer(QObject *parent = nullptr);

    ~ABRecordTokenizer();
    // Установить файл базы данных
    void setBaseFile(const QString &filename);

    // Подготовить для записи
    bool startWrite(int count);

    // Идёт процесс чтения, переключение в режим записи невозможно
    bool isReading();

    // Включен режим записи, чтение невозможно
    bool isWriting();

    // Начать чтение записей, вернёт общее число записей.
    int startRead();

    // Записать следующую запись, возвращает номер записи
    int writeRecord(const SignatureRecord &record);
    SignatureRecord* nextRecord(int &number);

    // Закрывает открытый файл
    void close();
};

#endif // ABRECORDTOKENIZER_H
