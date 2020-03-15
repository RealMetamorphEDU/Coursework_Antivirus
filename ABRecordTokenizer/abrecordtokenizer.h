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
    BListReadable *readable;
    bool reading;
    bool writing;
    int prepareCount;
    int currentCount;
    QThread *thread;

    void stopRead();
public:
    explicit ABRecordTokenizer(QObject *parent = nullptr);

    ~ABRecordTokenizer();
    // Установить файл базы данных
    void setBaseFile(const QString &filename);

    // Подготовить для записи
    bool prepareForWrite(int count);

    // Начать чтение записей, вернёт общее число записей или -1
    int prepareForRead();

    // Идёт процесс чтения, переключение в режим записи невозможно
    bool isReading();

    // Включен режим записи, чтение невозможно
    bool isWriting();

    // Закрывает открытый файл
    void close();
private slots:
    void writeRecord(SignatureRecord *record);
    void readStart();
signals:
    void nextRecord(SignatureRecord *record, int number);
    void readFinished();
    void writeFinished();
};

#endif // ABRECORDTOKENIZER_H
