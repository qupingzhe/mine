#ifndef Q_MINE_H
#define Q_MINE_H

#include <QObject>

#include "mine.h"

class QMine : public QObject {
	Q_OBJECT
public:
	static MineInterface* lowMine;
	static MineInterface* midMine;
	static MineInterface* highMine;

	QMine();
	~QMine();
	void setLevel(int level);
  //int getCellType(int x, int y );
  //int getColumn();
  //int getRow();
signals:
	//void start();
	void win();
	void lose();
	//void tab();
	void remainingMine(int number);
	void clicked();
  void updateGraph(int** const graph, const int column, const int row);
public slots:
	void explore(int x, int y);
	void mark(int x, int y);
	void restart();
protected:
  void testFlag();
private:
	MineInterface* mine_interface_;
  int** graph_;
  int row_;
  int column_;
};

#endif
