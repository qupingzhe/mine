#ifndef WINE_H
#define WINE_H

#include <string>

#define MAX_SIZE 100

const int dx[]={-1,0,+1,+1,+1,0,-1,-1};
const int dy[]={-1,-1,-1,0,+1,+1,+1,0};

enum Level
{
	LOW,
	MID,
	HIGH
};

enum CellType
{
	ERROR = -1,
	BLANK = 0,
	MINE = 13,
	TAB = 18,
	NO_DISCOVERY = 21
};

class Error
{
public:
	Error( std::string message )
	{
		this->message = message;
	}
	std::string getErrorMessage( void )
	{
		return message;
	}
private:
	std::string message;
};

class ErrorScope : public Error
{
public:
	ErrorScope( std::string message ) : Error( message ) {}
};

class ErrorMine : public Error
{
public:
	ErrorMine( std::string message ) : Error( message ) {}
};

class ErrorTab : public Error
{
public:
	ErrorTab( std::string message ) : Error( message ) {}
};

class Mine
{
public:
	static bool isInScope( int a, int b ) {
		return ( a >= 0 && a < b );
	}

	Mine( int mineNumber=10, int row=10, int column=10 );
	~Mine( void );
	void buryMine( void );
	void updateGraph( void );

	void explore( int x, int y );
	void exploreFast( int x, int y );
	void mark( int x, int y );
	bool isWinned( void );
	void restart( void );

	int getColumn( void );
	int getRow( void );
	int getCellType( int  x, int y );
	int getRemainingMine( void );

	int getNeighborMineNumber( int x, int y );
	int getNeighborTabNumber( int x, int y );
	void bfs( int x, int y );
private:
	int **graph;
	int **visibleGraph;
	int remainingMine;
	int mineNumber;
	int row;
	int column;
};

void showMine( Mine &mine );

#endif
