#ifndef STARTSCANMESSAGE_H
#define STARTSCANMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT StartScanMessage : public PipeMessage {
Q_OBJECT
    QString objectPath;
    bool file; // true if file, false if dir
public:
    explicit StartScanMessage(const QString& objectPath = "", bool file = false, QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QString& getObjectPath() const;
    bool isFile() const;
    bool isDir() const;
};
#endif // STARTSCANMESSAGE_H
