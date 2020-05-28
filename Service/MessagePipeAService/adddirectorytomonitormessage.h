#ifndef ADDDIRECTORYTOMONITORMESSAGE_H
#define ADDDIRECTORYTOMONITORMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT AddDirectoryToMonitorMessage : public PipeMessage {
Q_OBJECT
    QString dirPath;
public:
    explicit AddDirectoryToMonitorMessage(const QString& dirPath = "", QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QString& getPath() const;
};
#endif // ADDDIRECTORYTOMONITORMESSAGE_H
