#ifndef ASERVICEFILESEEKER_H
#define ASERVICEFILESEEKER_H

#include <QObject>

class Seeker;

class AServiceFileSeeker: public QObject {
Q_OBJECT
	Seeker *seeker;
public:
	explicit AServiceFileSeeker(QObject *parent = nullptr);
	~AServiceFileSeeker();

public slots:
	void findFiles(QString dirpath, QString pattern, bool recursive);
signals:
	void foundFile(QString filepath);
};

#endif // ASERVICEFILESEEKER_H
