#ifndef WINE_H
#define WINE_H

#include <string>

#include "mine-def.h"

//#define MAX_SIZE 110

const int dx[]={-1,0,+1,+1,+1,0,-1,-1};
const int dy[]={-1,-1,-1,0,+1,+1,+1,0};

enum Level
{
	LOW,
	MID,
	HIGH
};

enum CellType {
	ERROR = -1,
	BLANK = 0,
	MINE = 13,
	TAB = 18,
	NO_DISCOVERY = 21
};

/*
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
*/

class MineInterface {
public:
  MineInterface() {}
  virtual ~MineInterface() {}
	virtual void explore(int x, int y) = 0;
	virtual void exploreFast(int x, int y) = 0;
	virtual void mark(int x, int y) = 0;

  virtual int getStatus() = 0;
	virtual int getRemainingMine() = 0;
  virtual void copyGraph(int** newGraph, int* column, int* row) = 0;

	virtual void restart() = 0;
  virtual void win() = 0;
  virtual void lose() = 0;
};

class Mine : public MineInterface {
public:
	Mine(int mineNumber=10, int row=10, int column=10);
	~Mine();
  void initialize();

	void explore(int x, int y);
	void exploreFast(int x, int y);
	void mark(int x, int y);

  int getStatus();
	int getRemainingMine();
  void copyGraph(int** newGraph, int* column, int* row);

	void restart();
  void win();
  void lose();

	static bool isInScope( int a, int b ) {
		return ( a >= 0 && a < b );
	}

	//bool isWinned();
	//int getColumn();
	//int getRow();
	//int getCellType(int  x, int y);

protected:
	void buryMine();
	void updateGraph();
	int getNeighborMineNumber(int x, int y);
	int getNeighborTabNumber(int x, int y);
	void bfs(int x, int y);
  void checkGame();

private:
	int** graph_;
	int** visibleGraph_;
	int remainingMine_;
	int mineNumber_;
	int row_;
	int column_;
  int status_;
};

void showMine( Mine &mine );

#endif
