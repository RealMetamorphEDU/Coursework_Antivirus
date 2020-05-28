#ifndef REMOVEDIRECTORYFROMMONITORMESSAGE_H
#define REMOVEDIRECTORYFROMMONITORMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT RemoveDirectoryFromMonitorMessage : public PipeMessage {
    Q_OBJECT
    QString dirPath;
public:
    explicit RemoveDirectoryFromMonitorMessage(const QString& dirPath = "", QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QString& getPath() const;
};
#endif // REMOVEDIRECTORYFROMMONITORMESSAGE_H
