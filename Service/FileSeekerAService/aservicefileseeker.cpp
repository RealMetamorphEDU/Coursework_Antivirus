#include "aservicefileseeker.h"
#include "seeker.h"
#include "QEvent"
AServiceFileSeeker::AServiceFileSeeker(QObject *parent): QObject(parent) {
	seeker = new Seeker();
}

AServiceFileSeeker::~AServiceFileSeeker() {

}

void AServiceFileSeeker::findFiles(QString dirpath, QString pattern, bool recursive) {

}
