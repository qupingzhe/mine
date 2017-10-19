#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include <QWidget>

#include "mine-def.h"

class QMine;

class QHBoxLayout;
class QVBoxLayout;
class QLabel;

class MineField : public QWidget {
	Q_OBJECT
public:
	MineField(QWidget* parent = NULL);
	~MineField();

	void mousePressEvent(QMouseEvent* event);
	void createCells();
	//void deleteCells();
	void restart();
signals:
	void explore(int x, int y);
	void mark(int x, int y);
	void start();
	void changeRemainingMine(int);
	void win();
	void lose();
public slots:
  void updateGraph(int** const graph, const int column, const int row);
	//void updateGraph(QMine* qmine);
private:
	QPixmap* cellImage[30];
	int row_;
	int column_;
	bool flag;
	//QLabel*** cells;
  QLabel* cells[MAX_SIZE][MAX_SIZE];
	QHBoxLayout* hlayout[MAX_SIZE];
	QVBoxLayout* mainLayout;
};

#endif
