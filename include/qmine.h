#ifndef Q_MINE_H
#define Q_MINE_H

#include <QObject>

#include "mine.h"

class QMine : public QObject
{
	Q_OBJECT
public:
	static Mine* lowMine;
	static Mine* midMine;
	static Mine* highMine;

	QMine( void );
	~QMine( void );
	void setLevel( int level );
	int getCellType( int x, int y );
	int getColumn( void );
	int getRow( void );
signals:
	void start( void );
	void win( void );
	void lose( void );
	void tab( void );
	void remainingMine( int number );
	void clicked( QMine* );
	void clicked( void );
public slots:
	void explore( int x, int y );
	void mark( int x, int y );
	void restart( void );
private:
	Mine* mine;
};

#endif
