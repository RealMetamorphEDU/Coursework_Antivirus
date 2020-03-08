#ifndef ABRECORDTOKENIZER_H
#define ABRECORDTOKENIZER_H

#include "ABRecordTokenizer_global.h"
#include <qfile.h>
#include <QObject>

#include "litebencode.h"
#include "signaturerecord.h"

class ABRECORDTOKENIZER_EXPORT ABRecordTokenizer: public QObject {
Q_OBJECT
    QFile *currentFile;
    LiteBencode *liteBencode;
    BListWritable *writable;
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
    bool prepareForWrite(int count);

    // Идёт процесс чтения, переключение в режим записи невозможно
    bool isReading();

    // Включен режим записи, чтение невозможно
    bool isWriting();

    // Начать чтение записей, вернёт общее число записей.
    int readAll();

    // Записать следующую запись, возвращает номер записи
    int writeRecord(SignatureRecord &record);

    // Закрывает открытый файл
    void close();
signals:
    void nextRecord(SignatureRecord *record, int number);
};

#endif // ABRECORDTOKENIZER_H
