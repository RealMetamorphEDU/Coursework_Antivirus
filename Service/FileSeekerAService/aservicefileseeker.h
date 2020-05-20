#ifndef ASERVICEFILESEEKER_H
#define ASERVICEFILESEEKER_H

#include <QObject>

class Seeker;
class QThread;
typedef void *HANDLE;


class AServiceFileSeeker: public QObject {
Q_OBJECT
	Seeker *seeker;
	HANDLE requestEvent;
	QThread* thread;
	
public:
	explicit AServiceFileSeeker(QObject *parent = nullptr);
	~AServiceFileSeeker();

public slots:
	void findFiles(QString dirpath, QString pattern, bool recursive);
signals:
	void foundFile(QString filepath);
};

#endif // ASERVICEFILESEEKER_H
