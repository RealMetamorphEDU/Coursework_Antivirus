#ifndef ASERVICEFILESEEKER_H
#define ASERVICEFILESEEKER_H

#include <QObject>


class AServiceFileSeeker: public QObject {
Q_OBJECT

public:
    explicit AServiceFileSeeker(QObject *parent = nullptr);
    ~AServiceFileSeeker();
public slots:
    void findFiles(QString dirpath, bool recursive);
signals:
    void foundFile(QString filepath);
};

#endif // ASERVICEFILESEEKER_H
