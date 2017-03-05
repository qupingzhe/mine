#include <QApplication>
#include "mine_gui.h"

int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	MineMainWindow* mine = new MineMainWindow;
	mine->show();
	return app.exec();
}
