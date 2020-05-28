#ifndef MONITOREDDIRECTORIESMESSAGE_H
#define MONITOREDDIRECTORIESMESSAGE_H
#include "pipemessage.h"
class ASERVICEMESSAGEPIPE_EXPORT MonitoredDirectoriesMessage : public PipeMessage {
    Q_OBJECT
    QStringList dirList;
public:
    explicit MonitoredDirectoriesMessage(const QStringList& dirList = QStringList(), QObject* parent = nullptr);
    bool parseQByteArray(QByteArray& array) override;
    QByteArray toByteArray() override;
    const QStringList& getDirList() const;
};
#endif // MONITOREDDIRECTORIESMESSAGE_H
