#include "snakeMDP.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	qsrand(time(NULL));
	QApplication a(argc, argv);
	snakeMDP w;
	w.show();
	return a.exec();
}
