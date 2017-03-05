#ifndef MINE_FIELD_H
#define MINE_FIELD_H

#include <QWidget>

class QMine;

class QHBoxLayout;
class QVBoxLayout;
class QLabel;

class MineField : public QWidget
{
	Q_OBJECT
public:
	MineField( QMine* qmine, QWidget* parent = NULL );
	~MineField( void );

	void mousePressEvent( QMouseEvent* event );
	void createCells( void );
	void deleteCells( void );
	void restart( QMine* qmine );
signals:
	void explore( int x, int y );
	void mark( int x, int y );
	void start( void );
	void changeRemainingMine( int );
	void win( void );
	void lose( void );
public slots:
	void updateGraph( QMine* qmine );
private:
	QPixmap* cellImage[30];
	int row;
	int column;
	bool flag;
	QLabel*** cells;
	QHBoxLayout** hlayout;
	QVBoxLayout* mainLayout;
};

#endif
