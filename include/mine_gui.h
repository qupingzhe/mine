#ifndef MINE_GUI_H
#define MINE_GUI_H
#include <QMainWindow>

class MineField;
class QMine;
class MineTimer;

class QLCDNumber;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QAction;
class QMenu;

class MineMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MineMainWindow( void );
	~MineMainWindow( void );
	void changeLevel( int level );
	void createMenuBar( void );
	void setMainWidget( void );
	void connectMine( void );
	void createObject( void );
private slots:
	void restart( void );
	void low( void );
	void mid( void );
	void high( void );
	void doWin( void );
	void doLose( void );
private:
	QMine* qmine;

	QWidget* mainWidget;
	MineField* mineField;
	QLCDNumber* timeLCD;
	QLCDNumber* remainingMineLCD;
	QLabel* label;
	QHBoxLayout* statusLayout;
	QVBoxLayout* mainLayout;

	MineTimer* mineTimer;

	QAction* restartAction;
	QAction* lowAction;
	QAction* midAction;
	QAction* highAction;
	QAction* quitAction;
	QMenu* menu;
};

#endif
