#include <QtGui/QApplication>
#include "simugetscene.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if( MountDB(DB_NAME)==-1 )
	{
		printf("MountDB error!");
		QMessageBox().information(NULL,QString::fromLocal8Bit("����!"),QString::fromLocal8Bit("MountDB����!"),QMessageBox::Ok);
		return 0;
	}

	SimuGetSceneTable w;
	w.show();
	return a.exec();
}
