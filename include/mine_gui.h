#ifndef MINE_GUI_H
#define MINE_GUI_H
#include <QMainWindow>

class MineField;
class QMine;
class MineTimer;
class StatusDialog;

class QLCDNumber;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QAction;
class QMenu;

class MineMainWindow : public QMainWindow {
	Q_OBJECT
public:
	MineMainWindow();
	~MineMainWindow();
	void changeLevel(int level);
	void createMenuBar();
	void setMainWidget();
	void connectMine();
	void createObject();
private slots:
	void restart();
	void low();
	void mid();
	void high();
	void doWin();
	void doLose();
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
  StatusDialog* winDialog;
  StatusDialog* loseDialog;

	QAction* restartAction;
	QAction* lowAction;
	QAction* midAction;
	QAction* highAction;
	QAction* quitAction;
	QMenu* menu;
};

#endif
